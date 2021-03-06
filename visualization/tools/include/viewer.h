/*
 *    Created by Sergey Popov
 *    snip89@mail.ru
 */

#ifndef VIEWER_H
#define VIEWER_H

#include <QTextEdit>
#include <QList>
#include <QColor>
#include <QObject>
#include <QKeyEvent>
#include <QTextCursor>
#include <QSettings>
#include <QVariant>
#include <QString>
#include <QFont>
#include <QDebug>

#define VIEWER_PADDING_KOEFF 10

class Viewer : public QTextEdit
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);

    void setLineColor(QColor color);
    void setLineFontColor(QColor color);
    void setInvisible(bool logical);

    virtual ~Viewer();

private slots:
    void highlightCurrentLine();

private:
    QColor lineColor;
    QColor lineFontColor;

    bool invisible;
};

#endif // VIEWER_H
