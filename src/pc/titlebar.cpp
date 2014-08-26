#include "titlebar.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent)
{
    //title label
    m_labTitle = new QLabel(tr("DKD v0.1"));
    m_labTitle->setStyleSheet("color:white;");
    m_labTitle->setContentsMargins(5,5,0,0);

    //skin manager & close & min buttons
    m_btnClose = new PushButton();
    m_btnMin = new PushButton();
    m_btnSkin = new PushButton();
    //load images
    m_btnClose->loadPixmap("://img/sysButton/close_button.png");
    m_btnMin->loadPixmap("://img/sysButton/min_button");
    m_btnSkin->loadPixmap("://img/sysButton/skin_button");

    m_btnPicture = new QPushButton(this);
    m_btnPicture->setStyleSheet(
                "QPushButton:hover:!pressed { background-image: url(:/TitleBar/UserHeader_MS);border-style: outset;"
                 "border-width: 1px;border-radius: 2px; border-color: green; }"

                "QPushButton:hover:pressed { border-image: url(:/TitleBar/UserHeader_MS);border-style: outset;"
                "border-width: 1px;border-radius: 2px; border-color: red; }"

                "QPushButton { background-image: url(:/TitleBar/UserHeader_MS);border-style: outset;"
                "border-width: 0px;border-radius: 2px; border-color: white; "
                "background-position: center left;"
                "background-repeat: no-repeat;"
                "background-origin: padding;   }"
                                );
    m_btnPicture->setFixedSize(49,49);
    m_btnPicture->setFocusPolicy(Qt::NoFocus);

    m_labUser = new QLabel(this);
    m_labUser->setStyleSheet("color:white;font:bold;font-size:14px");
    m_labUser->setText("paj at paj-PC");


    //.....................................................................
    //layout
    QHBoxLayout * titlebar_layout = new QHBoxLayout();
    titlebar_layout->addWidget(m_labTitle,0,Qt::AlignTop);
    titlebar_layout->addStretch();
    titlebar_layout->addWidget(m_btnSkin,0,Qt::AlignTop|Qt::AlignRight);
    titlebar_layout->addWidget(m_btnMin,0,Qt::AlignTop|Qt::AlignRight);
    titlebar_layout->addWidget(m_btnClose,0,Qt::AlignTop|Qt::AlignRight);
    titlebar_layout->setSpacing(0);
    titlebar_layout->setContentsMargins(0, 2, 3, 0);

    QHBoxLayout * userinf_layout = new QHBoxLayout();
    userinf_layout->addWidget(m_btnPicture,0,Qt::AlignBottom);
    userinf_layout->addWidget(m_labUser);
    userinf_layout->setSpacing(0);
    userinf_layout->setContentsMargins(10, 30, 0, 0);
    m_labUser->setContentsMargins(10,10,0,0);

    QVBoxLayout * main_layout = new QVBoxLayout(this);
    main_layout->addLayout(titlebar_layout);
    main_layout->addLayout(userinf_layout);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);


    setFixedHeight(100);

    is_move = false;

    //event handler
    connect(m_btnClose, SIGNAL(clicked()), this, SIGNAL(evtClose()) );
    connect(m_btnMin, SIGNAL(clicked()), this, SIGNAL(evtMinWnd()) );
    connect(m_btnSkin, SIGNAL(clicked()), this, SIGNAL(evtSkinMgr()) );
    connect(m_btnPicture,SIGNAL(clicked()),this,SIGNAL(evtShowHostInf()));
}

void TitleBar::mousePressEvent(QMouseEvent *e)
{
    press_point = e->pos();
    is_move = true;
}

void TitleBar::mouseMoveEvent(QMouseEvent *e)
{
    if((e->buttons() == Qt::LeftButton) && is_move)
    {
        QWidget* parent_widget = this->parentWidget();
        QPoint parent_point = parent_widget->pos();
        parent_point.setX(parent_point.x() + e->x() - press_point.x());
        parent_point.setY(parent_point.y() + e->y() - press_point.y());
        parent_widget->move(parent_point);
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *)
{
    if(is_move)
    {
        is_move = false;
    }
}



