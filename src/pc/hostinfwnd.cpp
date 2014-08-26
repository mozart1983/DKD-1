#include "hostinfwnd.h"
#include "push_button.h"
#include "mainwindow.h"
#include <QGridLayout>
#include <QSize>
#include <QBitmap>

HostInfWnd::HostInfWnd(QFrame *parent) :
    QFrame(parent),
    is_move(false)
{
    this->resize(300, 280);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    //placement
    QWidget* parent_widget = this->parentWidget();
    QPoint parent_point = parent_widget->pos();
    this->move(parent_point.x()-this->size().width()-10,parent_point.y()+50);

    //关闭按钮
    m_btnClose = new PushButton(this);
    m_btnClose->loadPixmap("://img/sysButton/close_button.png");

    //标题
    m_labTitle = new QLabel(this);
    m_labTitle->setText("<font color=\"white\">主机信息</font>");


    QFont ft;
    ft.setPointSize(12);

    m_labFriendlyName = new QLabel(this);
    m_labFriendlyName->setText("备注:");
    m_labFriendlyName->setToolTip("备注会显示在别人的在线列表中，如果没有设置备注将会显示主机信息");
    m_labFriendlyName->setFont(ft);
    m_editFriendname = new QLineEdit(this);
    m_editFriendname->setToolTip("备注会显示在别人的在线列表中，如果没有设置备注将会显示主机信息");
    m_editFriendname->setStyleSheet(
                "QLineEdit {color:blue; background: transparent;border-style: outset;border-width: 1px;border-color: rgb(0,155,144); }"
                                );
    m_labOS = new QLabel(this);
    m_labOS->setText("操作系统:");
    m_labOS->setFont(ft);
    m_labLoginUser = new QLabel(this);
    m_labLoginUser->setText("登陆用户:");
    m_labLoginUser->setFont(ft);
    m_labHostName = new QLabel(this);
    m_labHostName->setText("主机名:");
    m_labHostName->setFont(ft);
    m_labIPs = new QLabel(this);
    m_labIPs->setText("主机地址:");
    m_labIPs->setFont(ft);
    m_labOS_value = new QLabel(this);
    m_labOS_value->setText("win7 64b");
    m_labOS_value->setFont(ft);
    m_labOS_value->setStyleSheet("color:blue;");
    m_labLoginUser_value = new QLabel(this);
    m_labLoginUser_value->setText("paj");
    m_labLoginUser_value->setFont(ft);
    m_labLoginUser_value->setStyleSheet("color:blue;");
    m_labHostName_value = new QLabel(this);
    m_labHostName_value->setText("paj-PC");
    m_labHostName_value->setFont(ft);
    m_labHostName_value->setStyleSheet("color:blue;");
    m_labIPs_value = new QLabel(this);
    m_labIPs_value->setText("192.168.0.1");
    m_labIPs_value->setFont(ft);
    m_labIPs_value->setStyleSheet("color:blue;");

    //............................................................................
    //layout
    QHBoxLayout * title_layout = new QHBoxLayout();
    title_layout->addWidget(m_labTitle, 0, Qt::AlignTop);
    title_layout->addStretch();
    title_layout->addWidget(m_btnClose, 0, Qt::AlignTop);
    title_layout->setSpacing(5);
    title_layout->setContentsMargins(5, 2, 2, 0);

    QGridLayout * center_layout = new QGridLayout();
    center_layout->addWidget(m_labFriendlyName, 0, 0,Qt::AlignRight);
    center_layout->addWidget(m_editFriendname, 0, 1,Qt::AlignLeft);
    center_layout->addWidget(m_labOS, 1, 0,Qt::AlignRight);
    center_layout->addWidget(m_labOS_value, 1, 1,Qt::AlignLeft);
    center_layout->addWidget(m_labLoginUser, 2, 0,Qt::AlignRight);
    center_layout->addWidget(m_labLoginUser_value, 2, 1,Qt::AlignLeft);
    center_layout->addWidget(m_labHostName, 3, 0,Qt::AlignRight);
    center_layout->addWidget(m_labHostName_value, 3, 1,Qt::AlignLeft);
    center_layout->addWidget(m_labIPs, 4, 0,Qt::AlignRight);
    center_layout->addWidget(m_labIPs_value, 4, 1,Qt::AlignLeft);
    center_layout->setSpacing(14);
    center_layout->setContentsMargins(0, 30, 50, 0);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addLayout(title_layout);
    main_layout->addLayout(center_layout);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    //signal handler
    connect(parent_widget,SIGNAL(SigSkinChangeBroadCast(const QString &)),this,SLOT(OnSkinChange(const QString &)));
    connect(m_btnClose,SIGNAL(clicked()),this,SLOT(close()));
}

void HostInfWnd::OnSkinChange(const QString & skinfile)
{
    QString objname = "hostinfwnd";
    setObjectName(objname);
    QString myss = QString("QFrame#%1 {background-image:url(%2);border:1px solid gray}").arg(objname).arg(skinfile);
    setStyleSheet(myss);
}
void HostInfWnd::paintEvent(QPaintEvent *)
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

    //空白客户区
    QRect clientRt(rc);
    clientRt.setTop(30);
    clientRt.setLeft(1);
    clientRt.setRight(rc.width()-2);
    clientRt.setBottom(rc.height()-10);
    painter2.fillRect(clientRt,QColor(244,244,244));
}
void HostInfWnd::mousePressEvent(QMouseEvent *e)
{
    press_point = e->pos();
    is_move = true;
}

void HostInfWnd::mouseMoveEvent(QMouseEvent *e)
{
    if((e->buttons() == Qt::LeftButton) && is_move)
    {
        QPoint _point = this->pos();
        _point.setX(_point.x() + e->x() - press_point.x());
        _point.setY(_point.y() + e->y() - press_point.y());
        this->move(_point);
    }
}

void HostInfWnd::mouseReleaseEvent(QMouseEvent *)
{
    if(is_move)
    {
        is_move = false;
    }
}
