#include "p2pchatwnd.h"
#include "ui_p2pchatwnd.h"
#include "mainwindow.h"
#include <QPainter>
#include <QBitmap>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QColorDialog>
#include <QTextDocumentFragment>
#include <QFontDialog>
#include <QDebug>
#include <math.h>
#include "dkdmovablewidget.h"
#include "shootscreen.h"
void P2PChatWnd::OnAdjustWidgets()
{
    int width = ui->chattoolbar->width();
    QPoint posChatbar = ui->chattoolbar->pos();

    //调整消息显示部件
    ui->textEditShow->resize(width,abs(ui->textEditShow->y()-posChatbar.y()));

    //调整发送消息部件
    int bottom = this->height() - P2PCHAT_BOTTOMBAR_HEIGHT;
    int newtop = posChatbar.y()+ui->chattoolbar->height();
    ui->textEdit->move(ui->textEdit->x(),newtop);
    ui->textEdit->resize(width,abs(bottom-newtop));
}

P2PChatWnd::P2PChatWnd(QFrame *parent) :
    QFrame(parent),
    ui(new Ui::P2PChatWnd),
    is_move(false),
    ShootScreenWgt(NULL)
{
    ui->setupUi(this);

    //总是捕捉mousemove消息
    this->setMouseTracking(true);

    //去掉 系统标题栏
    setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);


    //聊天窗口居中
    this->move(  (QApplication::desktop()->width()- width())/2,
                       (QApplication::desktop()->height() - height())/2 - 20 );

    //更新背景图片
    OnSkinChange(theMainWnd->m_strMainSkin);

    //加载关闭按钮，最小化最大化按钮图片
    ui->btnclose->loadPixmap("://img/sysButton/close_button");
    ui->btnStore->loadPixmap("://img/sysButton/max_button");
    ui->btnMin->loadPixmap("://img/sysButton/min_button");


    this->setLayout(ui->gridLayout);

    //*****************************************************


    //*****************************************
    //signal handler
    connect(theMainWnd,SIGNAL(SigSkinChangeBroadCast(const QString &)),this,SLOT(OnSkinChange(const QString &)));
    connect(ui->btnclose,SIGNAL(clicked()),this,SLOT(OnCloseWnd()));
    connect(ui->btnStore,SIGNAL(clicked()),this,SLOT(OnStorBtn()));
    connect(ui->btnMin,SIGNAL(clicked()),this,SLOT(showMinimized()));
    connect(ui->pushButton_canel,SIGNAL(clicked()),this,SLOT(OnCloseWnd()));
    //发送按钮 点击处理
    connect(ui->pushButton_send,SIGNAL(clicked()),this,SLOT(SendMsg()));
    //更改字体
    connect(ui->btnFont,SIGNAL(clicked()),this,SLOT(OnFontChanged()));
    //更改颜色
    connect(ui->btnColor,SIGNAL(clicked()),this,SLOT(OnColorChanged()));
    //发送图片
    connect(ui->btnPicture,SIGNAL(clicked()),this,SLOT(OnSendImg()));
    //调整chatbar
    connect(ui->chattoolbar,SIGNAL(sigChatbarMoving()),this,SLOT(OnAdjustWidgets()));
    connect(ui->btnScreenCapture,SIGNAL(clicked()),this,SLOT(OnShootScreen()));
}

void P2PChatWnd::OnShootScreen()
{
    //内存在析构里面释放
    if( !ShootScreenWgt )
    {
        ShootScreenWgt = new ShootScreen();
        ShootScreenWgt->show();
        //退出截屏时，释放内存
        connect(ShootScreenWgt,SIGNAL(evtShootScreenClose()),this,SLOT(OnShootScreenClose()));
    }
}


void P2PChatWnd::OnShootScreenClose()
{
    //内存在析构里面释放
    if( ShootScreenWgt )
    {
        delete ShootScreenWgt;
        ShootScreenWgt = NULL;
    }
}


void P2PChatWnd::OnSendImg()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"),"pic/",tr("Images(*.bmp *.ico *.png *.jpg)"));
    if( file.isNull() )
    {
        return;
    }
    QTextDocumentFragment fragment;
    fragment = QTextDocumentFragment::fromHtml( QString("<img src='%1'>").arg(file) );
    ui->textEdit->textCursor().insertFragment(fragment);
    ui->textEdit->setVisible(true);
}

void P2PChatWnd::OnColorChanged()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Select Color", QColorDialog::DontUseNativeDialog);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
}

void P2PChatWnd::OnFontChanged()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,ui->textEdit->font(),this);
    if(ok){
        ui->textEdit->setFont(font);
    }
}


void P2PChatWnd::ChangeHTMLSend2View()
{
    //strikeout , underline，经测试toHtml方法不会添加这两个属性
    bool underline = false;
    bool strikeout = false;
    strikeout = ui->textEdit->currentFont().strikeOut();
    underline = ui->textEdit->currentFont().underline();

    const QString & src = ui->textEdit->toHtml();
    QString strView = ui->textEditShow->toPlainText();
    if( strView.isEmpty() ){
        strView =
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                "p, li { white-space: pre-wrap; }"
                "</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">"
                "</body></html>";
    }
    else{
        strView = ui->textEditShow->toHtml();
    }

    //获取所有段落
    int start = src.indexOf("<p",0);
    int end = src.lastIndexOf("</body>");
    QString txt = src.mid(start,end-start);

    //更改行缩进
    const QString strTag = "text-indent:" ;
    int pos = 0;
    for(;;)
    {
        pos = txt.indexOf(strTag,pos+1);
        if( pos!=-1)
             txt.replace(pos+strTag.length(),1,'9');
        else
            break;
    }

    //获取发送框的字体和颜色信息！
    pos = src.indexOf("<body",0);
    int styleend = src.indexOf(">",pos+1);
    QString fontinf("<span ");
    fontinf += src.mid(pos+strlen("<body"),styleend-pos-4);
    if(underline)
        fontinf.insert(fontinf.length()-2,"text-decoration: underline;");
    if(strikeout)
        fontinf.insert(fontinf.length()-2,"text-decoration: line-through;");

    //插入字体信息到段落
    int tail=0;
    tail = txt.indexOf(">",0);
    for(; tail!=-1;)
    {
         txt.insert(tail+1,fontinf);
         tail = txt.indexOf("</p>",tail+1);
         txt.insert(tail,"</span>");
         tail = txt.indexOf(">",tail+strlen("</span></p>")+1);
    }

    int despos = strView.lastIndexOf("</body>");
    strView.insert(despos,txt);

    ui->textEditShow->setHtml(strView);
}

void P2PChatWnd::InsertTalker(const QString & tag)
{
    QString strView = ui->textEditShow->toPlainText();
    if( strView.isEmpty() ){
        strView =
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                "p, li { white-space: pre-wrap; }"
                "</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">"
                "</body></html>";
    }
    else{
        strView = ui->textEditShow->toHtml();
    }

    QString p = QString("<p style=\" margin-top:5px; margin-bottom:5px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:#072cff;\">%1</span></p>").arg(tag);
    int despos = strView.lastIndexOf("</body>");
    strView.insert(despos,p);

    ui->textEditShow->setHtml(strView);
}

void P2PChatWnd::SendMsg()
{
    if( ui->textEdit->toPlainText().isEmpty() )
        return;

    //添加 说话人的tag
    InsertTalker("paj 2014-2-4\n");

    //添加自己的要发送的信息
    ChangeHTMLSend2View();

    //将显示消息的编辑框滚动到底部
    QTextCursor cursor =  ui->textEditShow->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEditShow->setTextCursor(cursor);

    //清空发送窗口
    ui->textEdit->clear();

    //设置焦点
    ui->textEdit->setFocus(Qt::OtherFocusReason);
}

void P2PChatWnd::SetPeerHostInf(const HOSTINFO & hi)
{
    _peerhost = hi;

    //更新到UI
    ui->labeltitle->setText(hi.strFriendlyName.empty()?hi.strAccount.c_str():hi.strFriendlyName.c_str());
    ui->label_aliasname->setText(hi.strFriendlyName.c_str());
    ui->label_account->setText(hi.strAccount.c_str());
    QString oss[] = {
      "win8", "win7","windows VISTA","windows XP","windows server 2003","windows server 2008",
        "linux","unix",  };
    ui->label_os->setText(oss[hi.OS]);
    QString ips;
    for(unsigned int i=0;i<hi.ips.size();++i)
    {
        ips += hi.ips[i].c_str();
        ips += "\n\n";
    }
    ui->label_ips->setText(ips);
}

void P2PChatWnd::mouseDoubleClickEvent(QMouseEvent * event)
{
    if( event->y()<P2PCHAT_TITLEBAR_HEIGHT )
        setWindowState(windowState() ^ Qt::WindowMaximized);
}

void P2PChatWnd::OnStorBtn()
{
    setWindowState(windowState() ^ Qt::WindowMaximized);
}

void P2PChatWnd::mousePressEvent(QMouseEvent *e)
{
    press_point = e->pos();
    is_move = true;
}

void P2PChatWnd::mouseMoveEvent(QMouseEvent *e)
{
    if((e->buttons() == Qt::LeftButton) && is_move)
    {
        QPoint old_point = pos();
        old_point.setX(old_point.x() + e->x() - press_point.x());
        old_point.setY(old_point.y() + e->y() - press_point.y());
        move(old_point);
    }
}

void P2PChatWnd::mouseReleaseEvent(QMouseEvent *)
{
    if(is_move)
    {
        is_move = false;
    }
}


P2PChatWnd::~P2PChatWnd()
{
    delete ui;

    if(ShootScreenWgt)
    {
        delete ShootScreenWgt;
        ShootScreenWgt = NULL;
    }
}
void P2PChatWnd::OnCloseWnd()
{
    close();
    emit evtCloseChatWnd(this->windowTitle());
}

void P2PChatWnd::OnSkinChange(const QString & skinfile)
{
    QString objname = "p2pchatwnd";
    setObjectName(objname);
    QString myss = QString("QFrame#%1 {border-image:url(%2)}").arg(objname).arg(skinfile);
    setStyleSheet(myss);
}
void P2PChatWnd::paintEvent(QPaintEvent *)
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
