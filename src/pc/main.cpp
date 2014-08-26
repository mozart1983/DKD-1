#include "mainwindow.h"
#include <QApplication>

DKDFrame * theMainWnd = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    theMainWnd = new DKDFrame();
    theMainWnd->show();

    return a.exec();
}
