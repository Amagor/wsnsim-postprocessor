#ifndef REALTIMETABLEVISUALIZATION_H
#define REALTIMETABLEVISUALIZATION_H

#include "irealtimevisualization.h"
#include "abstractrealtimetablevisualization.h"
#include "records.h"
#include "staticrecordsreader.h"
#include "udpsocketadapter.h"
#include "staticvisualizationtools.h"
#include "columnsselectiondialog.h"

class RealTimeTableVisualization : public IRealTimeVisualization, protected AbstractRealTimeTableVisualization
{
public:
    explicit RealTimeTableVisualization(QWidget *parent = 0);

    // interface methods

    /*virtual*/ void stop();
    /*virtual*/ void update(IProject *project, UdpSocketAdapter *socketAdapter,  QList<Format*> formats);
    /*virtual*/ void update();
    /*virtual*/ void searchNext(QString str);
    /*virtual*/ void searchPrevious(QString str);
    /*virtual*/ QWidget *getWidget();

    /*virtual*/ void addRecord(QByteArray byteRecord);

    virtual ~RealTimeTableVisualization();
private:

    int itemSearchedIndex;

    QStringList argumentsNames;
};

#endif // REALTIMETABLEVISUALIZATION_H
