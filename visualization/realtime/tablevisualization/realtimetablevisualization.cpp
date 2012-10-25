#include "realtimetablevisualization.h"

RealTimeTableVisualization::RealTimeTableVisualization(QWidget *parent) :
    AbstractRealTimeTableVisualization(parent)
{
    recordsLimit = 1000;
    //recordsLimit = settings.value("RealTime/Text Visualization/Gui/RecordsLimit").value<quint64>();
}

void RealTimeTableVisualization::stop()
{
    disconnect(currentSocketAdapter, SIGNAL(dataRecieved(QByteArray)), this, SLOT(addRecord(QByteArray)));
}

void RealTimeTableVisualization::update(IProject *project, UdpSocketAdapter *socketAdapter)
{
    viewer->clear();
    viewer->setRowCount( 0);

    eventTypes.clear();
    recordsCount = 0;

    currentProject = project;
    currentSocketAdapter = socketAdapter;

    int size = 0;
    SimpleEventInfo *info = currentProject->info(size);

    for(int i = 0; i < size; i++)
    {
        int argsCount = info[i].argsCount;

        SimpleArgInfo *argsInfo = info[i].argsInfo;
        for(int j = 0; j < argsCount; j++)
        {
            if(!eventTypes.contains(*argsInfo[j].name))
                eventTypes.append(*argsInfo[j].name);
        }
    }

    eventTypes.sort();

    eventTypes.insert(0, "event");
    eventTypes.insert(0, "time");

    viewer->setColumnCount(eventTypes.size());
    viewer->setHorizontalHeaderLabels(eventTypes);

    connect(currentSocketAdapter, SIGNAL(dataRecieved(QByteArray)), this, SLOT(addRecord(QByteArray)));
}

void RealTimeTableVisualization::update()
{
    /*if(settings.value("Text visualization/Gui/LineWrapMode").value<bool>())
        viewer->setLineWrapMode(QTextEdit::WidgetWidth);
    else
        viewer->setLineWrapMode(QTextEdit::NoWrap);

    viewer->setLineColor(settings.value("Text visualization/Appearance/Colors and Fonts/Cursor_line_color").value<QColor>());
    viewer->setLineFontColor(settings.value("Text visualization/Appearance/Colors and Fonts/Cursor_line_font_color").value<QColor>());

    viewer->setTextColor(settings.value("Text visualization/Appearance/Colors and Fonts/Main_text_foreground").value<QColor>());

    QPalette p = viewer->palette();
    p.setColor(QPalette::Base, settings.value("Text visualization/Appearance/Colors and Fonts/Main_text_background").value<QColor>());
    viewer->setPalette(p);

    viewer->setCurrentFont(settings.value("Text visualization/Appearance/Colors and Fonts/Font").value<QFont>());

    QString temp = viewer->toPlainText();
    viewer->clear();
    viewer->setText(temp);*/
}

QWidget *RealTimeTableVisualization::getWidget()
{
    return this;
}

void RealTimeTableVisualization::addRecord(QByteArray byteRecord)
{
    if(recordsCount < recordsLimit)
    {
        viewer->setRowCount(recordsCount + 1);

        qint64 readedSize = 0;
        Record record;
        int infoSize = 0;
        SimpleEventInfo *info = currentProject->info(infoSize);

        StaticRecordsReader::readRecord(byteRecord.data(), byteRecord.size(), 0, readedSize, record, info);

        for(int k = 0; k < eventTypes.size(); k ++)
        {
            if(k == 0)
            {
                viewer->setItem(recordsCount, k, new QTableWidgetItem(QString::number(record.time)));
            }
            else if(k == 1)
            {
                viewer->setItem(recordsCount, k, new QTableWidgetItem(*info[record.eventID].type));
            }
            else
            {
                bool wasEvent = false;
                for(int j = 0; j < info[record.eventID].argsCount; j ++)
                {
                    if(eventTypes[k] == info[record.eventID].argsInfo[j].name)
                    {
                        wasEvent = true;

                        if(info[record.eventID].argsInfo[j].type == BYTE_ARRAY_TYPE)
                        {
                            QString hexed_string = "";
                            foreach(quint8 nextHex, record.other[j].value<QByteArray>())
                            {
                                QString hexed = QString::number(nextHex, 16);
                                hexed = hexed.toUpper();
                                if(hexed.size() == 1)
                                    hexed.insert(0, '0');

                                hexed_string += hexed + " ";
                            }

                            hexed_string.chop(1);

                            //resultLine.append(hexed_string);
                            viewer->setItem(recordsCount, k, new QTableWidgetItem(hexed_string));
                        }
                        else
                            //resultLine.append(record.other[j].toString());
                            viewer->setItem(recordsCount, k, new QTableWidgetItem(record.other[j].toString()));
                    }
                }

                if(!wasEvent)
                    //resultLine.append("");
                    viewer->setItem(recordsCount, k, new QTableWidgetItem(""));

            }
        }

        viewer->setRowHeight(recordsCount, 20);

        QStringList header;

        for(int i = 0; i < recordsCount + 1; i ++)
        {
            header.append(QString::number(i));
        }

        viewer->setVerticalHeaderLabels(header);
        //viewer->setCurrentCell(currentRow, currentColumn);

        recordsCount ++;
    }

    /*if(recordsCount < recordsLimit)
    {
        qint64 readedSize = 0;
        Record record;
        int infoSize = 0;
        SimpleEventInfo *info = currentProject->info(infoSize);

        StaticRecordsReader::readRecord(byteRecord.data(), byteRecord.size(), 0, readedSize, record, info);

        QString resultLine = QString::number(recordsCount) + ": ";
        resultLine += "time: " + QString::number(record.time) + "; ";
        resultLine += "event: " + *info[record.eventID].type + "; ";

        for(int j = 0; j < info[record.eventID].argsCount; j ++)
        {
            if(info[record.eventID].argsInfo[j].type == BYTE_ARRAY_TYPE)
            {
                resultLine += *info[record.eventID].argsInfo[j].name + ": ";

                foreach(quint8 nextHex, record.other[j].value<QByteArray>())
                {
                    QString hexed = QString::number(nextHex, 16);
                    hexed = hexed.toUpper();
                    if(hexed.size() == 1)
                        hexed.insert(0, '0');

                    resultLine += hexed + " ";
                }

                resultLine += "; ";
            }
            else
                resultLine += *info[record.eventID].argsInfo[j].name + ": " + record.other[j].toString() + "; ";
        }

        viewer->append(resultLine);

        recordsCount ++;
    }
    else
    {
        viewer->clear();
        recordsCount = 0;
    }*/
}

RealTimeTableVisualization::~RealTimeTableVisualization()
{
}