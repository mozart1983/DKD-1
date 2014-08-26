#include "shootscreenmenuwnd.h"
#include "ui_shootscreenmenuwnd.h"

ShootScreenMenuWnd::ShootScreenMenuWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShootScreenMenuWnd)
{
    ui->setupUi(this);
}

ShootScreenMenuWnd::~ShootScreenMenuWnd()
{
    delete ui;
}
