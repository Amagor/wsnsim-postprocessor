######################################################################
# Automatically generated by qmake (2.01a) Sat Oct 13 11:29:02 2012
######################################################################

QT += core gui xml
INCLUDEPATH += ../libs/projectData
TEMPLATE = app
TARGET = 
DEPENDPATH += . \
              core \
              interfaces \
              shared \
              ui \
              core/include \
              shared/include \
              visualization/abstract \
              visualization/hexvisualization \
              visualization/tablevisualization \
              visualization/textvisualization \
              visualization/tools \
              visualization/abstract/include \
              visualization/hexvisualization/include \
              visualization/tablevisualization/include \
              visualization/textvisualization/include \
              visualization/tools/include
INCLUDEPATH += . \
               core/include \
               interfaces \
               shared/include \
               ui \
               visualization/textvisualization/include \
               visualization/abstract/include \
               visualization/tools/include \
               visualization/hexvisualization/include \
               visualization/tablevisualization/include

# Input
HEADERS += interfaces/ilog.h \
           interfaces/iproject.h \
           interfaces/ivisualization.h \
           ui/ui_hexappearancecolorsandfontssettings.h \
           ui/ui_tablevisualization.h \
           core/include/abstractfilter.h \
           core/include/booleanoperators.h \
           core/include/filter.h \
           core/include/filtrationwidget.h \
           core/include/generalcoresettings.h \
           core/include/generalguisettings.h \
           core/include/gotolinedialog.h \
           core/include/localizationsettings.h \
           core/include/log.h \
           core/include/logindex.h \
           core/include/loginfo.h \
           core/include/logselectdialog.h \
           core/include/mainsettings.h \
           core/include/mainwindow.h \
           core/include/ostools.h \
           core/include/project.h \
           core/include/sniffercoresettings.h \
           core/include/snifferguisettings.h \
           core/include/staticlogfilter.h \
           core/include/staticlogreader.h \
           core/include/staticlogwriter.h \
           shared/include/emptysettings.h \
           shared/include/logdatatypes.h \
           shared/include/records.h \
           shared/include/simpleeventinfo.h \
           shared/include/staticfromlogselector.h \
           shared/include/staticrecordsreader.h \
           visualization/abstract/include/abstracttablevisualization.h \
           visualization/abstract/include/abstracttextappearancecolorsandfontssettings.h \
           visualization/abstract/include/abstracttextguisettings.h \
           visualization/abstract/include/abstracttextvisualization.h \
           visualization/hexvisualization/include/hexappearancecolorsandfontssettings.h \
           visualization/hexvisualization/include/hexguisettings.h \
           visualization/hexvisualization/include/hexvisualization.h \
           visualization/tablevisualization/include/tableguisettings.h \
           visualization/tablevisualization/include/tablevisualization.h \
           visualization/textvisualization/include/textappearancecolorsandfontssettings.h \
           visualization/textvisualization/include/textguisettings.h \
           visualization/textvisualization/include/textvisualization.h \
           visualization/tools/include/tableviewer.h \
           visualization/tools/include/viewer.h
FORMS += ui/abstracttablevisualization.ui \
         ui/abstracttextappearancecolorsandfontssettings.ui \
         ui/abstracttextguisettings.ui \
         ui/abstracttextvisualization.ui \
         ui/emptysettings.ui \
         ui/filtrationwidget.ui \
         ui/generalcoresettings.ui \
         ui/generalguisettings.ui \
         ui/gotolinedialog.ui \
         ui/localizationsettings.ui \
         ui/logselectdialog.ui \
         ui/mainsettings.ui \
         ui/mainwindow.ui \
         ui/sniffercoresettings.ui \
         ui/snifferguisettings.ui \
         ui/tableguisettings.ui
SOURCES += core/filter.cpp \
           core/filtrationwidget.cpp \
           core/generalcoresettings.cpp \
           core/generalguisettings.cpp \
           core/gotolinedialog.cpp \
           core/localizationsettings.cpp \
           core/log.cpp \
           core/logindex.cpp \
           core/logselectdialog.cpp \
           core/main.cpp \
           core/mainsettings.cpp \
           core/mainwindow.cpp \
           core/ostools.cpp \
           core/project.cpp \
           core/sniffercoresettings.cpp \
           core/snifferguisettings.cpp \
           core/staticlogfilter.cpp \
           core/staticlogreader.cpp \
           core/staticlogwriter.cpp \
           shared/emptysettings.cpp \
           shared/staticfromlogselector.cpp \
           shared/staticrecordsreader.cpp \
           visualization/abstract/abstracttablevisualization.cpp \
           visualization/abstract/abstracttextappearancecolorsandfontssettings.cpp \
           visualization/abstract/abstracttextguisettings.cpp \
           visualization/abstract/abstracttextvisualization.cpp \
           visualization/hexvisualization/hexappearancecolorsandfontssettings.cpp \
           visualization/hexvisualization/hexguisettings.cpp \
           visualization/hexvisualization/hexvisualization.cpp \
           visualization/tablevisualization/tableguisettings.cpp \
           visualization/tablevisualization/tablevisualization.cpp \
           visualization/textvisualization/textappearancecolorsandfontssettings.cpp \
           visualization/textvisualization/textguisettings.cpp \
           visualization/textvisualization/textvisualization.cpp \
           visualization/tools/tableviewer.cpp \
           visualization/tools/viewer.cpp
TRANSLATIONS += resources/localization/qt_ru.ts resources/localization/postprocessor_ru.ts \
    resources/localization/qt_en.ts resources/localization/postprocessor_en.ts
include(../wsnsim.pri)
tr.commands = lrelease $$_PRO_FILE_
QMAKE_EXTRA_TARGETS += tr
POST_TARGETDEPS += tr

RESOURCES += \
    resources/postprocessor.qrc
