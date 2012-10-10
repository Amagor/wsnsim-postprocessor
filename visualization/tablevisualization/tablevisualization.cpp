#include "tablevisualization.h"

TableVisualization::TableVisualization(QWidget *parent)
    : AbstractTableVisualization(parent)
{
    firstTime = true;
}

void TableVisualization::activity(bool status)
{
    isActive = status;
}

void TableVisualization::update(IProject *project, ILog *log)
{
    if(!firstTime)
        delete currentEventLog;
    else
        firstTime = false;

    currentProject = project;
    currentLog = log;

    disconnect(ui->toolBoxComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(selectedEventChanged(QString)));
    initEventSelector();
    connect(ui->toolBoxComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(selectedEventChanged(QString)));

    topLinePos = 0;

    currentEvent = ui->toolBoxComboBox->currentText();
    currentEventLog = StaticFromLogSelector::selectFromLog(currentLog, currentProject, "tablev.templog", ui->toolBoxComboBox->currentIndex());

    updatePage();
}

void TableVisualization::update()
{
    updatePage();
}

QWidget *TableVisualization::getWidget()
{
    return this;
}

void TableVisualization::fromLine(qint64 line)
{
}

void TableVisualization::updatePage()
{
    int size = 0;
    SimpleEventInfo *info = currentProject->info(size);

    for(int i = 0; i < size; i++)
    {
        if(info[i].type == currentEvent)
        {
            int argsCount = info[i].argsCount;

            viewer->setColumnCount(argsCount + 1);

            QStringList header;
            header.append("vTime");

            SimpleArgInfo *argsInfo = info[i].argsInfo;
            for(int j = 0; j < argsCount; j++)
            {
                header.append(*argsInfo[j].name);
            }

            viewer->setHorizontalHeaderLabels(header);
        }
    }

    currentEventLog->seek(topLinePos);

    int recordsCount = linesOnPage(0);

    qint64 binPageSize = 0;
    char *binPage = currentEventLog->read(recordsCount, binPageSize);

    QList<QStringList> resultLines;

    qint64 posInBinPage = 0;
    for(int i = 0; i < recordsCount; i ++)
    {
        QStringList resultLine;

        qint64 readedSize = 0;
        Record record;
        int infoSize = 0;
        SimpleEventInfo *info = currentProject->info(infoSize);

        StaticRecordsReader::readRecord(binPage, binPageSize, posInBinPage, readedSize, record, info);
        posInBinPage += readedSize;

        resultLine.append(QString::number(record.vTime));

        for(int j = 0; j < info[record.eventID].argsCount; j ++)
        {
            if(info[record.eventID].argsInfo[j].type == BYTE_ARRAY_TYPE)
            {
                foreach(char nextHex, record.other[j].toByteArray())
                {
                    QString hexed = QString::number(nextHex, 16);
                    hexed = hexed.toUpper();
                    if(hexed.size() == 1)
                        hexed.insert(0, '0');

                    resultLine.append(hexed);
                }
            }
            else
                resultLine.append(record.other[j].toString());
        }

        resultLines.append(resultLine);
    }

    //viewer->setRowCount(1);
    //viewer->setItem(0,0,new QTableWidgetItem(resultLines.at(0).at(0)));

    viewer->setRowCount(recordsCount);

    for(int i = 0; i < resultLines.size(); i ++)
    {
        for(int j = 0; j < resultLines.at(i).size(); j ++)
        {
            viewer->setItem(i, j, new QTableWidgetItem(resultLines.at(i).at(j)));
            viewer->resizeRowToContents(i);
        }
    }

    ui->horizontalScrollBar->setMinimum(viewer->horizontalScrollBar()->minimum());
    ui->horizontalScrollBar->setMaximum(viewer->horizontalScrollBar()->maximum());
}

void TableVisualization::updatePage(int cursorMoving)
{
    updatePage();
}

TableVisualization::~TableVisualization()
{
    if(!firstTime)
        delete currentEventLog;
}

void TableVisualization::setSettings(QSettings &someSettings)
{
}

void TableVisualization::initEventSelector()
{
    ui->toolBoxComboBox->clear();

    int size = 0;
    SimpleEventInfo *info = currentProject->info(size);

    for(int i = 0; i < size; i ++)
    {
        ui->toolBoxComboBox->addItem(*info[i].type);
    }
}