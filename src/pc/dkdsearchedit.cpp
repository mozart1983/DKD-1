#include "dkdsearchedit.h"
#include <QWidget>
#include <QString>
#include <QEvent>
DKDSearchEdit::DKDSearchEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setToolTip("输入IP/昵称/登录名/主机名");
    setFixedHeight(25);

    connect(this,SIGNAL(textChanged(QString)),this,SLOT(OnTextChanged(QString)));
}

void DKDSearchEdit::Init()
{
     this->setStyleSheet(
            "  QLineEdit {background-image:url(:/centerwidget/img/centerwidget/20x20_search.png);"
                              "color: gray;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: gray;"
                              "background-position: center right;"
                              "background-repeat: no-repeat;"
                              "background-origin: content; }"
            );


    setText("搜索好友...");
    setCursorPosition(0);
    setClearButtonEnabled(false);
    setFocus();
}

void DKDSearchEdit::Searching()
{
    this->setStyleSheet(
        "  QLineEdit {    selection-background-color: rgb(216,209,107);"
                          "background-color: white;"
                          "border-style: outset;"
                          "border-width: 1px;"
                          "border-color: gray;"
                          "padding-left: 2px;"
                          "text-align: left;"
                          "background-position: center right;"
                          "background-repeat: no-repeat;"
                          "background-origin: content; }"
        );

    if(this->text() == "搜索好友...")
    {
        this->clear();
    }

    setClearButtonEnabled(true);
}


void DKDSearchEdit::focusOutEvent(QFocusEvent * e)
{
    if( this->text() == "")
    {
        this->Init();
    }
    QLineEdit::focusOutEvent(e);

    setFocus();
}

void DKDSearchEdit::mousePressEvent(QMouseEvent * e)
{
    this->Searching();
    QLineEdit::mousePressEvent(e);
}



bool DKDSearchEdit::event(QEvent *e)
{
    if(e->type() == QEvent::KeyPress)
    {
       this->Searching();
    }
    return QLineEdit::event(e);
}

void DKDSearchEdit::OnTextChanged(const QString & text)
{
    if(text.isEmpty())
        emit sigSearchStop();
}
