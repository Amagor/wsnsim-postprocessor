#include "mainsettings.h"
#include "ui_mainsettings.h"

MainSettings::MainSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainSettings)
{
    ui->setupUi(this);

    settingsFrameWidget = new QStackedWidget(this);
    ui->settingsFrameLayout->addWidget(settingsFrameWidget);

    createItems();

    emptySettings = new EmptySettings();

    localizationSettings = new LocalizationSettings();
    localizationSettings->showCurrentSettings();

    generalGuiSettings = new GeneralGuiSettings();
    generalGuiSettings->showCurrentSettings();

    generalCoreSettings = new GeneralCoreSettings();
    generalCoreSettings->showCurrentSettings();

    initConnections();

//    initSettingsTree();

    // addChildSettings(settings, 0, "");

    // connect(ui->settingsTree, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(activatedItem(QTreeWidgetItem*, int)));
    // connect(ui->settingsTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(activatedItem(QTreeWidgetItem*, int)));
    // connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonClicked(QAbstractButton*)));
}

MainSettings::~MainSettings()
{
    deleteItems();

    delete settingsFrameWidget;
    delete ui;

    delete emptySettings;
    delete localizationSettings;
    delete generalCoreSettings;
    delete generalGuiSettings;
}

void MainSettings::createItems()
{
    generalItem = new QTreeWidgetItem(ui->settingsTree);
    generalCoreItem = new QTreeWidgetItem(generalItem);
    generalGuiItem = new QTreeWidgetItem(generalItem);

    generalItem->setText(0, tr("General"));
    generalCoreItem->setText(0, tr("Core"));
    generalGuiItem->setText(0, tr("Gui"));

    hexVisualizationItem = new QTreeWidgetItem(ui->settingsTree);
    hexVisualizationColorsAndFontsItem = new QTreeWidgetItem(hexVisualizationItem);

    hexVisualizationItem->setText(0, tr("Hex visualization"));
    hexVisualizationColorsAndFontsItem->setText(0, tr("Colors and Fonts"));

    textVisualizationItem = new QTreeWidgetItem(ui->settingsTree);
    textVisualizationColorsAndFontsItem = new QTreeWidgetItem(textVisualizationItem);

    textVisualizationItem->setText(0, tr("Text visualization"));
    textVisualizationColorsAndFontsItem->setText(0, tr("Colors and Fonts"));

    localizationItem = new QTreeWidgetItem(ui->settingsTree);
    languageItem = new QTreeWidgetItem(localizationItem);

    localizationItem->setText(0, tr("Localization"));
    languageItem->setText(0, tr("Language"));
}

void MainSettings::initConnections()
{
    connect(ui->settingsTree, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(activatedItem(QTreeWidgetItem*, int)));
    connect(ui->settingsTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(activatedItem(QTreeWidgetItem*, int)));
}

void MainSettings::deleteItems()
{
    delete generalCoreItem;
    delete generalGuiItem;

    delete generalItem;

    delete hexVisualizationColorsAndFontsItem;
    delete hexVisualizationItem;

    delete textVisualizationColorsAndFontsItem;
    delete textVisualizationItem;

    delete languageItem;
    delete localizationItem;
}

void MainSettings::showEmptySettings(QString name)
{
    emptySettings->setSettingsName(name);
    if(!settingsFrameWidget->isAncestorOf(emptySettings))
        settingsFrameWidget->addWidget(emptySettings);

    settingsFrameWidget->setCurrentWidget(emptySettings);
}

/*void MainSettings::addChildSettings(QSettings &settings, QTreeWidgetItem *parent, QString group)
{
    QTreeWidgetItem *item;

    settings.beginGroup(group);

    foreach(QString group, settings.childGroups())
    {
        if(group != tr("Defaults") && group != tr("Hidden") && group != "SYSTEM")
        {
            
            if(parent)
            {
                item = new QTreeWidgetItem(parent);
            }
            else
            {
                item = new QTreeWidgetItem(ui->settingsTree);
            }

            item->setText(0, group);
            addChildSettings(settings, item, group);

        }
    }

    settings.endGroup();
}*/

void MainSettings::activatedItem(QTreeWidgetItem *item, int column)
{
    if(item == generalItem)
    {
    }

    else if(item == generalCoreItem)
    {

    }

    else if(item == generalGuiItem)
    {

    }

    else if(item == hexVisualizationItem)
    {

    }

    else if(item == hexVisualizationColorsAndFontsItem)
    {

    }

    else if(item == textVisualizationItem)
    {

    }

    else if(item == textVisualizationColorsAndFontsItem)
    {

    }

    else if(item == localizationItem)
    {

    }

    else if(item == languageItem)
    {

    }
}

/*void MainSettings::buttonClicked(QAbstractButton *button)
{
    if(button->text() == tr("OK"))
        emit settingsApplied();

    else if(button->text() == tr("Cancel"))
        emit settingsCanceled();
}*/
