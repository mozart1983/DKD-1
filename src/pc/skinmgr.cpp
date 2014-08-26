#include "skinmgr.h"
#include <QtGui>
#include <QHBoxLayout>
#include <QGridLayout>
#include "mainwindow.h"
#include "push_button.h"

SkinMgr::SkinMgr(QFrame *parent) :
    QFrame(parent)
{
    this->resize(300, 180);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    //placement
    QWidget* parent_widget = this->parentWidget();
    QPoint parent_point = parent_widget->pos();
    this->move(parent_point.x()-this->size().width()-10,parent_point.y()+50);

    //关闭按钮
    m_btnClose = new PushButton();
    m_btnClose->loadPixmap("://img/sysButton/close_button.png");

    //标签
    m_labTitle = new QLabel();
    m_labTitle->setText("更换皮肤");
    m_labTitle->setStyleSheet("color:white;");

    //皮肤按钮
    QString stritem;
    for(unsigned int i=0;i<sizeof(m_btnSkin)/sizeof(m_btnSkin[0]);++i)
    {
        stritem = QString("QPushButton:hover:!pressed { background-image: url(:/skin/img/skin/%1.jpg);border-style: outset;"
                          "border-width: 2px;border-radius: 1px; border-color: rgb(0,155,144); }"

                          "QPushButton:hover:pressed { background-image: url(:/skin/img/skin/%2.jpg);border-style: outset;"
                          "border-width: 2px;border-radius: 1px; border-color: gray; }"

                          "QPushButton { background-image: url(:/skin/img/skin/%3.jpg);border-style: outset;"
                          "border-width: 2px;border-radius: 1px; border-color: beige; }"
                          ).arg(i).arg(i).arg(i);
        m_btnSkin[i] = new QPushButton(this);
        m_btnSkin[i]->setStyleSheet(stritem);
        m_btnSkin[i]->setFixedSize(60,60);
    }
    connect(m_btnSkin[0],SIGNAL(clicked()),this,SLOT(OnSkinChange0()));
    connect(m_btnSkin[1],SIGNAL(clicked()),this,SLOT(OnSkinChange1()));
    connect(m_btnSkin[2],SIGNAL(clicked()),this,SLOT(OnSkinChange2()));
    connect(m_btnSkin[3],SIGNAL(clicked()),this,SLOT(OnSkinChange3()));
    connect(m_btnSkin[4],SIGNAL(clicked()),this,SLOT(OnSkinChange4()));
    connect(m_btnSkin[5],SIGNAL(clicked()),this,SLOT(OnSkinChange5()));
    connect(m_btnSkin[6],SIGNAL(clicked()),this,SLOT(OnSkinChange6()));
    connect(m_btnSkin[7],SIGNAL(clicked()),this,SLOT(OnSkinChange7()));
    connect(m_btnSkin[8],SIGNAL(clicked()),this,SLOT(OnSkinChange8()));
    connect(m_btnSkin[9],SIGNAL(clicked()),this,SLOT(OnSkinChange9()));


    //style sheet
    OnSkinChange();

    //............................................................................
    //layout
    QGridLayout * center_layout = new QGridLayout();
    center_layout->addWidget(m_btnSkin[0], 0, 0);
    center_layout->addWidget(m_btnSkin[1], 0, 1);
    center_layout->addWidget(m_btnSkin[2], 0, 2);
    center_layout->addWidget(m_btnSkin[3], 0, 3);
    center_layout->addWidget(m_btnSkin[4], 0, 4);
    center_layout->addWidget(m_btnSkin[5], 1, 0);
    center_layout->addWidget(m_btnSkin[6], 1, 1);
    center_layout->addWidget(m_btnSkin[7], 1, 2);
    center_layout->addWidget(m_btnSkin[8], 1, 3);
    center_layout->addWidget(m_btnSkin[9], 1, 4);
    center_layout->setSpacing(1);
    center_layout->setContentsMargins(0, 10, 0, 0);

    QHBoxLayout * title_layout = new QHBoxLayout();
    title_layout->addWidget(m_labTitle, 0, Qt::AlignTop);
    title_layout->addStretch();
    title_layout->addWidget(m_btnClose, 0, Qt::AlignTop);
    title_layout->setSpacing(5);
    title_layout->setContentsMargins(5, 2, 2, 0);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addLayout(title_layout);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->addLayout(center_layout);
    main_layout->setContentsMargins(0, 0, 0, 0);


    is_move = false;

    //signal handler
    connect(m_btnClose,SIGNAL(clicked()),this,SLOT(close()));
}

void SkinMgr::OnSkinChange()
{
    QWidget* parent_widget = this->parentWidget();
    DKDFrame * frame  = dynamic_cast<DKDFrame *>(parent_widget);
    QString objname = "skinmgr";
    setObjectName(objname);
    QString myss = QString("QFrame#%1 {background-image:url(%2);border:1px solid gray}").arg(objname).arg(frame->m_strMainSkin);
    setStyleSheet(myss);
}

void SkinMgr::paintEvent(QPaintEvent *)
{
    //生成一张位图
    QBitmap objBitmap(size());
    //QPainter用于在位图上绘画
    QPainter painter(&objBitmap);
    //填充位图矩形框(用白色填充)
    painter.fillRect(rect(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    //在位图上画圆角矩形(用黑色填充)
    painter.drawRoundedRect(this->rect(),5,5);
    //使用setmask过滤即可
    setMask(objBitmap);


    //绘制边框
    QRect rc = this->rect();
    QPainter painter2(this);
    painter2.setPen(Qt::gray);
    painter2.setBackgroundMode(Qt::TransparentMode);
    painter2.drawRoundedRect(this->rect(),5,5);
    painter2.drawLine(rc.right(),rc.top(),rc.right(),rc.bottom());
    painter2.drawLine(rc.left(),rc.bottom(),rc.right(),rc.bottom());
    painter2.drawLine(rc.left(),rc.top(),rc.left(),rc.bottom());
    painter2.drawLine(rc.left(),rc.top(),rc.right(),rc.top());
}

void SkinMgr::OnSkinChange0()
{
    emit SigSkinChange(":/skin/img/skin/0_big.jpg");
    OnSkinChange();
}
void SkinMgr::OnSkinChange1()
{
    emit SigSkinChange(":/skin/img/skin/1_big.jpg");
    OnSkinChange();
}
void SkinMgr::OnSkinChange2()
{
    emit SigSkinChange(":/skin/img/skin/2_big.jpg");
    OnSkinChange();
}
void SkinMgr::OnSkinChange3()
{
    emit SigSkinChange(":/skin/img/skin/3_big.jpg");
    OnSkinChange();
}
void SkinMgr::OnSkinChange4()
{
    emit SigSkinChange(":/skin/img/skin/4_big.jpg");
    OnSkinChange();
}
void SkinMgr::OnSkinChange5()
{
    emit SigSkinChange(":/skin/img/skin/5_big.jpg");
    OnSkinChange();
}
void SkinMgr::OnSkinChange6()
{
    emit SigSkinChange(":/skin/img/skin/6_big.jpg");
    OnSkinChange();
}
void SkinMgr::OnSkinChange7()
{
    emit SigSkinChange(":/skin/img/skin/7_big.jpg");
    OnSkinChange();
}
void SkinMgr::OnSkinChange8()
{
    emit SigSkinChange(":/skin/img/skin/8_big.jpg");
    OnSkinChange();
}

void SkinMgr::OnSkinChange9()
{
    emit SigSkinChange(":/skin/img/skin/9_big.jpg");
    OnSkinChange();
}
void SkinMgr::mousePressEvent(QMouseEvent *e)
{
    press_point = e->pos();
    is_move = true;
}

void SkinMgr::mouseMoveEvent(QMouseEvent *e)
{
    if((e->buttons() == Qt::LeftButton) && is_move)
    {
        QPoint _point = this->pos();
        _point.setX(_point.x() + e->x() - press_point.x());
        _point.setY(_point.y() + e->y() - press_point.y());
        this->move(_point);
    }
}

void SkinMgr::mouseReleaseEvent(QMouseEvent *)
{
    if(is_move)
    {
        is_move = false;
    }
}



