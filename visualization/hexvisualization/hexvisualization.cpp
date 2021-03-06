/*
 *    Created by Sergey Popov
 *    snip89@mail.ru
 */

#include "hexvisualization.h"
#include "ui_abstracttextvisualization.h"

HexVisualization::HexVisualization(QWidget *parent) :
    AbstractTextVisualization(parent)
{
    setSettings(settings);

    name = "Hex";
}

void HexVisualization::activity(bool status)
{
    isActive = status;

    if(!isActive)
    {
        //ui->verticalScrollBar->setValue(0);
        //viewer->clear();
    }
}

void HexVisualization::getTextDocument(qint64 fromRecord, qint64 toRecord, QTextDocument &document)
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

        QString resultLine = QString::number(i) + ": ";

        foreach(char nextHex, record.byteRecord)
        {
            QString hexed = QString::number((quint8)nextHex, 16);
            hexed = hexed.toUpper();
            if(hexed.size() == 1)
                hexed.insert(0, '0');

            resultLine += hexed + " ";
        }

        result += resultLine + "\n";
    }

    document.setPlainText(result);
}

void HexVisualization::update(IProject *project, ILog *log, QList<Format*> formats)
{
    if(settings.value("Hex visualization/Gui/LineWrapMode").value<bool>())
        viewer->setLineWrapMode(QTextEdit::WidgetWidth);
    else
        viewer->setLineWrapMode(QTextEdit::NoWrap);

    viewer->setLineColor(settings.value("Hex visualization/Appearance/Colors and Fonts/Cursor_line_color").value<QColor>());
    viewer->setLineFontColor(settings.value("Hex visualization/Appearance/Colors and Fonts/Cursor_line_font_color").value<QColor>());

    viewer->setTextColor(settings.value("Hex visualization/Appearance/Colors and Fonts/Main_text_foreground").value<QColor>());

    QPalette p = viewer->palette();
    p.setColor(QPalette::Base, settings.value("Hex visualization/Appearance/Colors and Fonts/Main_text_background").value<QColor>());
    viewer->setPalette(p);

    viewer->setCurrentFont(settings.value("Hex visualization/Appearance/Colors and Fonts/Font").value<QFont>());

    currentProject = project;
    currentLog = log;

    topLinePos = settings.value("Hidden/Core/Current_pos").value<int>();
    currentLine = topLinePos;
    //topLinePos = 0;

    viewer->clear();

    updatePage();
}

void HexVisualization::update(QList<Format *> formats)
{
    topLinePos = settings.value("Hidden/Core/Current_pos").value<int>();
    currentLine = topLinePos;

    this->formats = formats;

    if(settings.value("Hex visualization/Gui/LineWrapMode").value<bool>())
        viewer->setLineWrapMode(QTextEdit::WidgetWidth);
    else
        viewer->setLineWrapMode(QTextEdit::NoWrap);    
    
    viewer->setLineColor(settings.value("Hex visualization/Appearance/Colors and Fonts/Cursor_line_color").value<QColor>());
    viewer->setLineFontColor(settings.value("Hex visualization/Appearance/Colors and Fonts/Cursor_line_font_color").value<QColor>());

    viewer->setTextColor(settings.value("Hex visualization/Appearance/Colors and Fonts/Main_text_foreground").value<QColor>());

    QPalette p = viewer->palette();
    p.setColor(QPalette::Base, settings.value("Hex visualization/Appearance/Colors and Fonts/Main_text_background").value<QColor>());
    viewer->setPalette(p);

    viewer->setCurrentFont(settings.value("Hex visualization/Appearance/Colors and Fonts/Font").value<QFont>());

    int cursorMoving = currentLine - topLinePos;

    viewer->clear();

    updatePage(cursorMoving);
}

void HexVisualization::searchNext(QString str)
{
    if(!viewer->find(str))
    {
        int pos = topLinePos + linesOnPage(decrement);

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

                QString resultLine = QString::number(pos) + ": ";

                foreach(char nextHex, record.byteRecord)
                {
                    QString hexed = QString::number((quint8)nextHex, 16);
                    hexed = hexed.toUpper();
                    if(hexed.size() == 1)
                        hexed.insert(0, '0');

                    resultLine += hexed + " ";
                }

                if(resultLine.contains(str))
                {
                    topLinePos = pos;
                    updatePage();

                    viewer->find(str);

                    return;
                }

                pos ++;
            }
        }
    }
}

void HexVisualization::searchPrevious(QString str)
{
    if(!viewer->find(str, QTextDocument::FindBackward))
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

                QString resultLine = QString::number(pos) + ": ";

                foreach(char nextHex, record.byteRecord)
                {
                    QString hexed = QString::number((quint8)nextHex, 16);
                    hexed = hexed.toUpper();
                    if(hexed.size() == 1)
                        hexed.insert(0, '0');

                    resultLine += hexed + " ";
                }

                if(resultLine.contains(str))
                {
                    topLinePos = pos;
                    updatePage();

                    viewer->find(str);

                    return;
                }

                pos --;
            }
        }
    }
}

QWidget *HexVisualization::getWidget()
{
    return this;
}

void HexVisualization::fromLine(qint64 line)
{
//    topLinePos = line;
//    updatePage();
    ui->verticalScrollBar->setValue(line);
}

HexVisualization::~HexVisualization()
{
    // delete colorsAndFontsSettings;
}

void HexVisualization::setSettings(QSettings &someSettings)
{
    if(!someSettings.contains("Defaults/Hex visualization/Appearance/Colors and Fonts/Cursor_line_color"))
        someSettings.setValue("Defaults/Hex visualization/Appearance/Colors and Fonts/Cursor_line_color", QColor(Qt::yellow).lighter(160));

    if(!someSettings.contains("Hex visualization/Appearance/Colors and Fonts/Cursor_line_color"))
        someSettings.setValue("Hex visualization/Appearance/Colors and Fonts/Cursor_line_color", QColor(Qt::yellow).lighter(160));

    if(!someSettings.contains("Defaults/Hex visualization/Appearance/Colors and Fonts/Cursor_line_font_color"))
        someSettings.setValue("Defaults/Hex visualization/Appearance/Colors and Fonts/Cursor_line_font_color", QColor(Qt::black));

    if(!someSettings.contains("Hex visualization/Appearance/Colors and Fonts/Cursor_line_font_color"))
        someSettings.setValue("Hex visualization/Appearance/Colors and Fonts/Cursor_line_font_color", QColor(Qt::black));

    if(!someSettings.contains("Defaults/Hex visualization/Appearance/Colors and Fonts/Main_text_background"))
        someSettings.setValue("Defaults/Hex visualization/Appearance/Colors and Fonts/Main_text_background", QColor(Qt::white));

    if(!someSettings.contains("Hex visualization/Appearance/Colors and Fonts/Main_text_background"))
        someSettings.setValue("Hex visualization/Appearance/Colors and Fonts/Main_text_background", QColor(Qt::white));

    if(!someSettings.contains("Defaults/Hex visualization/Appearance/Colors and Fonts/Main_text_foreground"))
        someSettings.setValue("Defaults/Hex visualization/Appearance/Colors and Fonts/Main_text_foreground", QColor(Qt::black));

    if(!someSettings.contains("Hex visualization/Appearance/Colors and Fonts/Main_text_foreground"))
        someSettings.setValue("Hex visualization/Appearance/Colors and Fonts/Main_text_foreground", QColor(Qt::black));

    if(!someSettings.contains("Defaults/Hex visualization/Appearance/Colors and Fonts/Font"))
        someSettings.setValue("Defaults/Hex visualization/Appearance/Colors and Fonts/Font", QFont());

    if(!someSettings.contains("Hex visualization/Appearance/Colors and Fonts/Font"))
        someSettings.setValue("Hex visualization/Appearance/Colors and Fonts/Font", QFont());

    if(!someSettings.contains("Hex visualization/Gui/Increment"))
        someSettings.setValue("Hex visualization/Gui/Increment", 1);

    if(!someSettings.contains("Defaults/Hex visualization/Gui/Increment"))
        someSettings.setValue("Defaults/Hex visualization/Gui/Increment", 1);

    if(!someSettings.contains("Hex visualization/Gui/LineWrapMode"))
        someSettings.setValue("Hex visualization/Gui/LineWrapMode", 0);

    if(!someSettings.contains("Defaults/Hex visualization/Gui/LineWrapMode"))
        someSettings.setValue("Defaults/Hex visualization/Gui/LineWrapMode", 0);
}

void HexVisualization::updatePage()
{
    currentLog->seek(topLinePos);
    viewer->clear();
    int recordsCount = linesOnPage(decrement);

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

    qint64 posInBinPage = 0;
    for(int i = 0; i < recordsCount; i ++)
    {
        qint64 readedSize = 0;
        Record record;
        int infoSize = 0;
        SimpleEventInfo *info = currentProject->info(infoSize);

        StaticRecordsReader::readRecord(binPage, binPageSize, posInBinPage, readedSize, record, info);
        posInBinPage += readedSize;

        QString resultLine = QString::number(topLinePos + i) + ": ";

        foreach(char nextHex, record.byteRecord)
        {
            QString hexed = QString::number((quint8)nextHex, 16);
            hexed = hexed.toUpper();
            if(hexed.size() == 1)
                hexed.insert(0, '0');

            resultLine += hexed + " ";
        }

        viewer->append(resultLine);
    }

    ui->verticalScrollBar->setPageStep(recordsCount);
    ui->verticalScrollBar->setMaximum(currentLog->size() - recordsCount);

    if(direction == Up)
        viewer->moveCursor(QTextCursor::Start);
    else if(direction == Down)
    {
        viewer->moveCursor(QTextCursor::End);
        viewer->moveCursor(QTextCursor::StartOfBlock);
    }

    ui->horizontalScrollBar->setMinimum(viewer->horizontalScrollBar()->minimum());
    ui->horizontalScrollBar->setMaximum(viewer->horizontalScrollBar()->maximum());

    if(viewer->document()->size().height() > viewer->viewport()->height())
    {
        decrement ++;
        updatePage();
    }
    /*else
    {
        decrement = 0;
    }*/

    settings.setValue("Hidden/Core/Current_pos", topLinePos);
}

void HexVisualization::updatePage(int cursorMoving)
{
    updatePage();

    if(direction == Up)
    {
        for(int i = 0; i < cursorMoving; i++)
        {
            viewer->moveCursor(QTextCursor::NextBlock);
        }

    }

    else if(direction == Down)
    {
        for(int i = linesOnPage(decrement) - 1; i > cursorMoving; i --)
        {
            viewer->moveCursor(QTextCursor::PreviousBlock);
        }
    }
}
