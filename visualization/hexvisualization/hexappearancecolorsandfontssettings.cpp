#include "hexappearancecolorsandfontssettings.h"

HexAppearanceColorsAndFontsSettings::HexAppearanceColorsAndFontsSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HexAppearanceColorsAndFontsSettings)
{
    ui->setupUi(this);
}

void HexAppearanceColorsAndFontsSettings::showCurrentSettings()
{
}

void HexAppearanceColorsAndFontsSettings::applySettings()
{
}

QWidget *HexAppearanceColorsAndFontsSettings::getWidget()
{
    return this;
}

HexAppearanceColorsAndFontsSettings::~HexAppearanceColorsAndFontsSettings()
{
    delete ui;
}