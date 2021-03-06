#include "tablevisualization.h"

TableVisualization::TableVisualization(QWidget *parent)
    : AbstractTableVisualization(parent)
{
    setSettings(settings);

    itemSearchedIndex = 0;
}

void TableVisualization::activity(bool status)
{
    isActive = status;
}

void TableVisualization::update(IProject *project, ILog *log, QList<Format*> formats)
{
    this->formats = formats;

    currentProject = project;
    currentLog = log;

    topLinePos = settings.value("Hidden/Core/Current_pos").value<int>();
    currentRow = 0;
    currentColumn = 0;

    viewer->clear();
    viewer->setRowCount(0);

    argumentsNames.clear();

    QStringList argumentsNamesFull = settings.value("Hidden/Gui/Project/Columns_names").value<QStringList>();
    QStringList argumentsState = settings.value("Hidden/Gui/Project/Columns_state").value<QStringList>();

    argumentsNames = argumentsNamesFull;

    viewer->setColumnCount(argumentsNames.size());
    viewer->setHorizontalHeaderLabels(argumentsNames);

    for(int i = 0; i < argumentsNames.size(); i ++)
    {
        if(argumentsState[i] == "true")
            viewer->setColumnHidden(i, false);
        else
            viewer->setColumnHidden(i, true);
    }

    updatePage();
}

void TableVisualization::update(QList<Format *> formats)
{
    topLinePos = settings.value("Hidden/Core/Current_pos").value<int>();

    this->formats = formats;

    viewer->clear();
    viewer->setRowCount(0);

    argumentsNames.clear();

    QStringList argumentsNamesFull = settings.value("Hidden/Gui/Project/Columns_names").value<QStringList>();
    QStringList argumentsState = settings.value("Hidden/Gui/Project/Columns_state").value<QStringList>();

    argumentsNames = argumentsNamesFull;

    viewer->setColumnCount(argumentsNames.size());
    viewer->setHorizontalHeaderLabels(argumentsNames);

    for(int i = 0; i < argumentsNames.size(); i ++)
    {
        if(argumentsState[i] == "true")
            viewer->setColumnHidden(i, false);
        else
            viewer->setColumnHidden(i, true);
    }

    updatePage();
}

void TableVisualization::searchNext(QString str)
{
    QList<QTableWidgetItem*> items = viewer->findItems(str, Qt::MatchContains | Qt::MatchCaseSensitive);

    if(items.size() == 0)
        return;

    if(!items[itemSearchedIndex]->isSelected())
    {
        viewer->setCurrentItem(items[itemSearchedIndex]);
        //items[itemSearchedIndex]->setSelected(true);
    }
    else
    {
        if(itemSearchedIndex + 1 < items.size())
        {
            itemSearchedIndex ++;
            searchNext(str);
        }
        else
        {
            int pos = topLinePos + linesOnPage();

            if(pos < currentLog->size())
            {
                currentLog->seek(pos);

                while(pos < currentLog->size())
                {
                    qint64 binPageSize = 0;
                    char *binPage = currentLog->read(1, binPageSize);
                    qint64 posInBinPage = 0;

                    qint64 readedSize = 0;
                    Record record;
                    int infoSize = 0;
                    SimpleEventInfo *info = currentProject->info(infoSize);

                    StaticRecordsReader::readRecord(binPage, binPageSize, posInBinPage, readedSize, record, info);
                    posInBinPage += readedSize;

                    QString resultLine = QString::number(record.time);

                    if(resultLine.contains(str))
                    {
                        topLinePos = pos;
                        updatePage();

                        itemSearchedIndex = 0;
                        searchNext(str);
                        return;
                    }

                    resultLine = *info[record.eventID].type;
                    if(resultLine.contains(str))
                    {
                        topLinePos = pos;
                        updatePage();

                        itemSearchedIndex = 0;
                        searchNext(str);
                        return;
                    }

                    for(int j = 0; j < info[record.eventID].argsCount; j ++)
                    {
                        resultLine = StaticVisualizationTools::updateValue(record.eventID,
                                    j,
                                    record.other[j],
                                    info[record.eventID].argsInfo[j].type,
                                                  formats);

                        if(resultLine.contains(str))
                        {
                            topLinePos = pos;
                            updatePage();

                            itemSearchedIndex = 0;
                            searchNext(str);
                            return;
                        }
                    }

                    pos ++;
                }
            }
        }
    }
}

void TableVisualization::searchPrevious(QString str)
{
    QList<QTableWidgetItem*> items = viewer->findItems(str, Qt::MatchContains | Qt::MatchCaseSensitive);

    if(items.size() == 0)
        return;

    if(!items[itemSearchedIndex]->isSelected())
    {
        viewer->setCurrentItem(items[itemSearchedIndex]);
        //items[itemSearchedIndex]->setSelected(true);
    }
    else
    {
        if(itemSearchedIndex - 1 >= 0)
        {
            itemSearchedIndex --;
            searchNext(str);
        }
        else
        {
            int pos = topLinePos - 1;
            if(pos >= 0)
            {
                while(pos >= 0)
                {
                    currentLog->seek(pos);

                    qint64 binPageSize = 0;
                    char *binPage = currentLog->read(1, binPageSize);
                    qint64 posInBinPage = 0;

                    qint64 readedSize = 0;
                    Record record;
                    int infoSize = 0;
                    SimpleEventInfo *info = currentProject->info(infoSize);

                    StaticRecordsReader::readRecord(binPage, binPageSize, posInBinPage, readedSize, record, info);
                    posInBinPage += readedSize;

                    QString resultLine = QString::number(record.time);

                    if(resultLine.contains(str))
                    {
                        topLinePos = pos;
                        updatePage();

                        itemSearchedIndex = 0;
                        searchNext(str);
                        return;
                    }

                    resultLine = *info[record.eventID].type;
                    if(resultLine.contains(str))
                    {
                        topLinePos = pos;
                        updatePage();

                        itemSearchedIndex = 0;
                        searchNext(str);
                        return;
                    }

                    for(int j = 0; j < info[record.eventID].argsCount; j ++)
                    {
                        resultLine = StaticVisualizationTools::updateValue(record.eventID,
                                    j,
                                    record.other[j],
                                    info[record.eventID].argsInfo[j].type,
                                                  formats);

                        if(resultLine.contains(str))
                        {
                            topLinePos = pos;
                            updatePage();

                            itemSearchedIndex = 0;
                            searchNext(str);
                            return;
                        }
                    }

                    pos --;
                }
            }
        }
    }
}

QWidget *TableVisualization::getWidget()
{
    return this;
}

void TableVisualization::fromLine(qint64 line)
{
    ui->verticalScrollBar->setValue(line);
}

void TableVisualization::updatePage()
{
    currentLog->seek(topLinePos);

    int recordsCount = linesOnPage();

    while(topLinePos > 0 && recordsCount > currentLog->size() - topLinePos)
    {
        topLinePos --;
        currentLog->seek(topLinePos);
    }

    if(topLinePos == 0 && recordsCount > currentLog->size())
    {
        recordsCount = currentLog->size();
    }

    qint64 binPageSize = 0;
    char *binPage = currentLog->read(recordsCount, binPageSize);

    viewer->setRowCount(recordsCount);

    qint64 posInBinPage = 0;
    for(int i = 0; i < recordsCount; i ++)
    {
        qint64 readedSize = 0;
        Record record;
        int infoSize = 0;
        SimpleEventInfo *info = currentProject->info(infoSize);

        StaticRecordsReader::readRecord(binPage, binPageSize, posInBinPage, readedSize, record, info);
        posInBinPage += readedSize;

        for(int k = 0; k < argumentsNames.size(); k ++)
        {
            if(k == 0)
            {
                viewer->setItem(i, k, new QTableWidgetItem(QString::number(record.time)));
            }
            else if(k == 1)
            {
                viewer->setItem(i, k, new QTableWidgetItem(*info[record.eventID].type));
            }
            else
            {
                bool wasEvent = false;
                for(int j = 0; j < info[record.eventID].argsCount; j ++)
                {
                    if(argumentsNames[k] == info[record.eventID].argsInfo[j].name)
                    {
                        wasEvent = true;

                        viewer->setItem(i, k, new QTableWidgetItem(
                                            StaticVisualizationTools::updateValue(record.eventID,
                                                        j,
                                                        record.other[j],
                                                        info[record.eventID].argsInfo[j].type,
                                                                                  formats)
                                                        ));
                    }
                }

                if(!wasEvent)
                    //resultLine.append("");
                    viewer->setItem(i, k, new QTableWidgetItem(""));

            }
        }

        viewer->setRowHeight(i, 20);
    }

    ui->verticalScrollBar->setPageStep(recordsCount);
    ui->verticalScrollBar->setMaximum(currentLog->size() - recordsCount);

    QStringList header;
    for(int i = topLinePos; i < topLinePos + recordsCount; i ++)
    {
        header.append(QString::number(i));
    }

    viewer->setVerticalHeaderLabels(header);
    viewer->setCurrentCell(currentRow, currentColumn);

    ui->horizontalScrollBar->setMinimum(viewer->horizontalScrollBar()->minimum());
    ui->horizontalScrollBar->setMaximum(viewer->horizontalScrollBar()->maximum());

    viewer->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    settings.setValue("Hidden/Core/Current_pos", topLinePos);
}

void TableVisualization::updatePage(int cursorMoving)
{
    updatePage();
}

void TableVisualization::getTextDocument(qint64 fromRecord, qint64 toRecord, QTextDocument &document)
{
    if(toRecord > currentLog->size())
        return;

    QString result;

    currentLog->seek(fromRecord);

    qint64 recordsCount = toRecord - fromRecord + 1;

    qint64 binPageSize = 0;
    char *binPage = currentLog->read(recordsCount, binPageSize);

    qint64 posInBinPage = 0;
    for(int i = fromRecord; i <= toRecord; i ++)
    {
        qint64 readedSize = 0;
        Record record;
        int infoSize = 0;
        SimpleEventInfo *info = currentProject->info(infoSize);

        StaticRecordsReader::readRecord(binPage, binPageSize, posInBinPage, readedSize, record, info);
        posInBinPage += readedSize;

        result += QString::number(i) + ": ";

        QStringList argumentsState = settings.value("Hidden/Gui/Project/Columns_state").value<QStringList>();

        for(int k = 0; k < argumentsNames.size(); k ++)
        {
            if(argumentsState[k] == "true")
            {
                if(k == 0)
                {
                    result += argumentsNames[k] + ": " + QString::number(record.time) + "; ";
                }
                else if(k == 1)
                {
                    result += argumentsNames[k] + ": " + *info[record.eventID].type + "; ";
                }
                else
                {
                    bool wasEvent = false;
                    for(int j = 0; j < info[record.eventID].argsCount; j ++)
                    {
                        if(argumentsNames[k] == info[record.eventID].argsInfo[j].name)
                        {
                            wasEvent = true;

                            result += argumentsNames[k] + ": " + StaticVisualizationTools::updateValue(record.eventID,
                                                                                                       j,
                                                                                                       record.other[j],
                                                                                                       info[record.eventID].argsInfo[j].type,
                                                                                                       formats) + "; ";
                        }
                    }

                    if(!wasEvent)
                        result += argumentsNames[k] + ": -//- ; ";

                }
            }
        }

        result += "\n";
    }

    document.setPlainText(result);
}

TableVisualization::~TableVisualization()
{
}

void TableVisualization::setSettings(QSettings &someSettings)
{
    if(!someSettings.contains("Defaults/Table visualization/Gui/Increment"))
        someSettings.setValue("Defaults/Table visualization/Gui/Increment", 1);

    if(!someSettings.contains("Table visualization/Gui/Increment"))
        someSettings.setValue("Table visualization/Gui/Increment", 1);
}
