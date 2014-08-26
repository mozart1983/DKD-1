#include "shootscreenbuddy.h"
#include "ui_shootscreenbuddy.h"


ShootScreenBuddy::ShootScreenBuddy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShootScreenBuddy)
{
    ui->setupUi(this); 
}

ShootScreenBuddy::~ShootScreenBuddy()
{
    delete ui;
}


void ShootScreenBuddy::RGBUpdate(const QString & strRGB)
{
   ui->labelRGB->setText(strRGB);
}
