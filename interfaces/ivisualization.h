/*
 * ivisualization.h
 *
 *  Created on: May 8, 2012
 *      Author: Sergey Popov (snip89@mail.ru)
 */

#ifndef IVISUALIZATION_H_
#define IVISUALIZATION_H_

#include <QtGui/QWidget>
#include <QString>
#include <QTextDocument>

#include "ilog.h"
#include "iproject.h"
#include "formatParams.h"

class IVisualization
{
public:
    // virtual IVisualizationSettings *visualizationSettings(QString name) = 0;

    virtual void activity(bool status) = 0;
    virtual void update(IProject *project, ILog *log, QList<Format*> formats) = 0;
    virtual void update(QList<Format*> formats) = 0;
    virtual void searchNext(QString str) = 0;
    virtual void searchPrevious(QString str) = 0;
    virtual QWidget *getWidget() = 0;
    virtual void fromLine(qint64 line) = 0;
    virtual void getTextDocument(qint64 fromRecord, qint64 toRecord, QTextDocument &document) = 0;
    virtual ~IVisualization() { }
};

#endif /* IVISUALIZATION_H_ */
