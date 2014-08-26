#include "mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QPainter>
#include <QBitmap>
#include <QMessageBox>
#include "titlebar.h"
#include "centerwidget.h"
#include "bottomwidget.h"
#include "skinmgr.h"
#include "hostinfwnd.h"
#include "p2pchatwnd.h"
#include "defs.h"

extern vector<HOSTINFO> theHosts;
extern vector<GROUPINFO> theGroups;

bool findhost(const QString & itemname,HOSTINFO & host)
{
    for(unsigned int i=0;i<theHosts.size();++i)
    {
        const HOSTINFO & item = theHosts[i];
        if( itemname == item.strFriendlyName.c_str()
                || itemname == item.strAccount.c_str() )
        {
            host = item;
            return true;
        }
    }

    return false;
}

bool findGroup(const QString & itemname,GROUPINFO & group)
{
    for(unsigned int i=0;i<theGroups.size();++i)
    {
        const GROUPINFO & item = theGroups[i];
        if( itemname == item.strCreater.c_str() )
        {
            group = item;
            return true;
        }
    }

    return false;
}

DKDFrame::DKDFrame(QFrame * parent) :
    QFrame(parent)
{
    setMinimumSize(260, 600);

    m_strMainSkin = ":/skin/img/skin/5_big.jpg";


    //without system titlebar
    setWindowFlags(Qt::FramelessWindowHint);

    //place window
    QRect deskRect = QApplication::desktop()->availableGeometry();
    this->move(deskRect.right()-280,30);


    //new subclass widgets
    m_titlebar = new TitleBar(this);
    m_centerWgt = new CenterWidget(this);
    m_bottomWgt = new BottomWidget(this);
    m_skinmgr = new SkinMgr(this);
    m_hostinfwnd = new HostInfWnd(this);


    //layout
    QVBoxLayout * pMainLayout = new QVBoxLayout(this);
    pMainLayout->addWidget(m_titlebar,0,Qt::AlignTop);
    pMainLayout->addWidget(m_centerWgt);
    pMainLayout->addWidget(m_bottomWgt,0,Qt::AlignBottom);
    pMainLayout->setSpacing(0);
    pMainLayout->setContentsMargins(0,0,0,0);

    //qss
    OnSkinChange(m_strMainSkin);

    //signal handler
    connect(m_titlebar,SIGNAL(evtClose()),this,SLOT(CloseEvtHandler()));
    connect(m_titlebar,SIGNAL(evtMinWnd()),this,SLOT(showMinimized()));
    connect(m_titlebar,SIGNAL(evtSkinMgr()),this,SLOT(SkinMgrHandler()));
    connect(m_skinmgr,SIGNAL(SigSkinChange(const QString &)),this,SLOT(OnSkinChange(const QString&)));
    connect(m_titlebar,SIGNAL(evtShowHostInf()),this,SLOT(OnShowHostInf()));
    connect(m_centerWgt,SIGNAL(evtNewSession(const QString&)),this,SLOT(OnNewSessionLanuch(const QString&)));

}

DKDFrame::~DKDFrame()
{
    //关闭所有聊天窗口
    for(std::map<QString,QWidget*>::iterator it = m_mapChatWnd.begin(); it!=m_mapChatWnd.end();++it)
    {
        delete it->second;
    }
    m_mapChatWnd.clear();
}

void DKDFrame::OnShowHostInf()
{
    m_hostinfwnd->show();
}

void DKDFrame::OnSkinChange(const QString & skinfile)
{
    QString objname = "mainframe";
    setObjectName(objname);
    QString myss = QString("QWidget#%1 {background-image:url(%2);}").arg(objname).arg(skinfile);
    setStyleSheet(myss);

    m_strMainSkin = skinfile;

    emit SigSkinChangeBroadCast(skinfile);
}

void DKDFrame::OnNewSessionLanuch(const QString & itemname)
{
    if( m_mapChatWnd.find(itemname)!=m_mapChatWnd.end() )  //已经存在对应的聊天窗口则激活它
    {
        QApplication::setActiveWindow( m_mapChatWnd[itemname] );
        return;
    }

    //不存在则创建
    P2PChatWnd * wnd = new P2PChatWnd();
    m_mapChatWnd[itemname] = wnd;
    wnd->show();
    wnd->setWindowTitle(itemname);
    HOSTINFO hi;
    if(findhost(itemname,hi))
        wnd->SetPeerHostInf(hi);


    connect(wnd,SIGNAL(evtCloseChatWnd(const QString&)),this,SLOT(OnChatWndClose(QString)));
}
void DKDFrame::OnChatWndClose(const QString & peername)
{
    std::map<QString,QWidget *>::iterator it;
    it = m_mapChatWnd.find(peername);
    if( it!=m_mapChatWnd.end() )
    {
        delete it->second;
        m_mapChatWnd.erase(it);
    }

}

void DKDFrame::SkinMgrHandler()
{
    m_skinmgr->show();
}

void DKDFrame::closeEvent(QCloseEvent * /*event*/)
{
    qApp->quit();
}

void DKDFrame::CloseEvtHandler()
{
    qApp->quit();
}

void DKDFrame::paintEvent(QPaintEvent *)
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
