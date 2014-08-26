#include "pushbtnwithmenu.h"
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QAction>

PushbtnWithMenu::PushbtnWithMenu(QWidget *parent) :
    QPushButton(parent)
{
    actionEnter = new QAction(this);
    actionEnter->setText(tr("enter"));
    actionCtrlEnter = new QAction(this);
    actionCtrlEnter->setText(tr("ctrl+enter"));
    actionEnter->setCheckable(true);
    actionCtrlEnter->setCheckable(true);

    actionEnter->setChecked(true);

    connect(actionEnter,SIGNAL(triggered(bool)),this,SLOT(OnEnter(bool)));
    connect(actionCtrlEnter,SIGNAL(triggered(bool)),this,SLOT(OnCtrlEnter(bool)));
}
void PushbtnWithMenu::mouseReleaseEvent(QMouseEvent * e)
{
    if( e->x() < (size().width()-20) )
    {

    }
    else
    {
         QMenu sendmenu(this);
         sendmenu.addAction(actionEnter);
         sendmenu.addAction(actionCtrlEnter);
         sendmenu.exec(QCursor::pos());
    }

    QPushButton::mouseReleaseEvent(e);
}

void PushbtnWithMenu::OnEnter(bool b)
{
    if(b)
        qDebug() << "choose enter";
    else
        qDebug() << "cancel enter";


}

void PushbtnWithMenu::OnCtrlEnter(bool b)
{
    if(b)
        qDebug() << "choose ctrl enter";
    else
        qDebug() << "cancel ctrl enter";
}

