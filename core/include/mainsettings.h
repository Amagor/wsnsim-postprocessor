/*
 *    Created by Sergey Popov
 *    snip89@mail.ru
 */

#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QDebug>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QString>
#include <QList>
#include <QStackedWidget>
#include <QAbstractButton>
#include <QPluginLoader> 
#include <QErrorMessage>
#include <QDialog>

#include "emptysettings.h"
#include "generalcoresettings.h"
#include "generalguisettings.h"
#include "localizationsettings.h"
#include "hexappearancecolorsandfontssettings.h"
#include "textappearancecolorsandfontssettings.h"
#include "hexguisettings.h"
#include "textguisettings.h"
#include "tableguisettings.h"
#include "staticcoreutils.h"
#include "clientsettings.h"

namespace Ui {
    class MainSettings;
}

class MainSettings : public QDialog
{
    Q_OBJECT

public:
    QStackedWidget *settingsFrameWidget;

    MainSettings(QWidget *parent = 0);
    ~MainSettings();

private:
    QSettings settings;

    // tree widgets
    QTreeWidgetItem *generalItem;
    QTreeWidgetItem *generalCoreItem;
    QTreeWidgetItem *generalGuiItem;
    QTreeWidgetItem *hexVisualizationItem;
    QTreeWidgetItem *hexVisualizationColorsAndFontsItem;
    QTreeWidgetItem *hexVisualizationGuiItem;
    QTreeWidgetItem *textVisualizationItem;
    QTreeWidgetItem *textVisualizationColorsAndFontsItem;
    QTreeWidgetItem *textVisualizationGuiItem;
    QTreeWidgetItem *tableVisualizationItem;
    QTreeWidgetItem *tableVisualizationGuiItem;
    QTreeWidgetItem *localizationItem;
    QTreeWidgetItem *languageItem;
    QTreeWidgetItem *realTimeItem;
    QTreeWidgetItem *clientsItem;

    QList<QTreeWidgetItem*> clientsItems;

    //settings widgets
    EmptySettings *emptySettings;
    LocalizationSettings *localizationSettings;
    GeneralGuiSettings *generalGuiSettings;
    GeneralCoreSettings *generalCoreSettings;
    HexAppearanceColorsAndFontsSettings *hexColorsAndFontsSettings;
    TextAppearanceColorsAndFontsSettings *textColorsAndFontsSettings;
    HexGuiSettings *hexGuiSettings;
    TextGuiSettings *textGuiSettings;
    TableGuiSettings *tableGuiSettings;

    QList<ClientSettings*> clientsSettings;

    QErrorMessage errorMessager;

    Ui::MainSettings *ui;

    void createItems();

    void initConnections();

    void deleteItems();

    void showEmptySettings(QString name);

    void createClientsItems();
    void deleteClientsItems();

    void createClientsSettings();
    void deleteClientsSettings();

signals:

    void settingsApplied();

private slots:
    void activatedItem(QTreeWidgetItem *item, int column);
    void buttonClicked(QAbstractButton *button);

    void dialogIsAccepted();
    void dialogIsRejected();
};

#endif // MAINSETTINGS_H
