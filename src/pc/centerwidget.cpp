#include "centerwidget.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollBar>
#include "userslistitem.h"
#include "defs.h"
#include <QMessageBox>
#include "dkdsearchedit.h"
#include <QDebug>
#include <string>
using std::string;

//define here,extern
vector<HOSTINFO> theHosts;
vector<GROUPINFO> theGroups;

CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent)
{
    //搜索好友部件
    m_editSearch = new DKDSearchEdit(this);
    m_editSearch->Init();


    //3个"tab"按钮
    m_btnUsers = new QPushButton(this);
    m_btnGroups = new QPushButton(this);
    m_btnChatRecord = new QPushButton(this);
    m_btnUsers->setFixedHeight(m_btnUsers->width()/3);
    m_btnGroups->setFixedHeight(m_btnGroups->width()/3);
    m_btnChatRecord->setFixedHeight(m_btnChatRecord->width()/3);
    UpdateTabs(0);

    m_richlist = new QListWidget(this);
    m_richlist->setFrameShape(QFrame::NoFrame);
    QString myss = QString(
                           "QListWidget::item:selected {background-color:rgb(252,235,171);}"
                           "QListWidget::item:hover:!selected {background-color:rgb(252,240,193);}"
                           "QListWidget::scrollbar {background-color:rgb(252,235,171);}"
                           );
    m_richlist->setStyleSheet(myss);
    m_richlist->verticalScrollBar()->setStyleSheet(
                "QScrollBar:vertical {width: 10px;background:rgb(255,255,255)}"

                "QScrollBar::handle:vertical{max-height: 20px;border-radius:4px;background:rgb(195,199,200);}"
                "QScrollBar::handle:vertical::hover{background:rgb(109,111,111);}"
                );

    m_richlist->setMouseTracking(true);
    m_richlist->setAutoScroll(true);


    //***************************
    //layout
    QHBoxLayout * tabs_layout = new QHBoxLayout();
    tabs_layout->addWidget(m_btnUsers);
    tabs_layout->addWidget(m_btnGroups);
    tabs_layout->addWidget(m_btnChatRecord);
    tabs_layout->setSpacing(0);
    tabs_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(m_editSearch);
    main_layout->addLayout(tabs_layout);
    main_layout->addWidget(m_richlist);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(1, 20, 1, 0);


    UpdateHostInfos();
    InitUsersListWidget(theHosts);

    connect(m_btnUsers,SIGNAL(clicked()),this,SLOT(OnClickBtnUsers()));
    connect(m_btnGroups,SIGNAL(clicked()),this,SLOT(OnClickBtnGroups()));
    connect(m_btnChatRecord,SIGNAL(clicked()),this,SLOT(OnClickBtnChatRecords()));
    connect(m_richlist,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(OnNewChatSession(QListWidgetItem*)));
    connect(m_editSearch,SIGNAL(textEdited(QString)),this,SLOT(OnSearching(const QString&)));
    connect(m_editSearch,SIGNAL(sigSearchStop()),this,SLOT(OnSearchStop()));
}

void CenterWidget::OnSearchStop()
{
    UpdateTabs(0);
    InitUsersListWidget(theHosts);
}

void CenterWidget::UpdateTabs(int item /*slected item*/ )
{
    m_btnUsers->setStyleSheet(
                "QPushButton:hover:!pressed { background-image: url(:/centerwidget/img/centerwidget/users_hot.png);border-style: outset;"
                  "border-width: 1px;border-radius: 0px; border-color: gray; }"

                  "QPushButton:hover:pressed { background-image: url(:/centerwidget/img/centerwidget/users_hot.png);border-style: outset;"
                  "border-width: 1px;border-radius: 0px; border-color: rgb(0,155,144); }"

                  "QPushButton { background-image: url(:/centerwidget/img/centerwidget/users_normal.png);border-style: outset;"
                  "border-width: 0px;border-radius: 0px; border-color: beige; }"
                             );
    m_btnGroups->setStyleSheet(
                "QPushButton:hover:!pressed { background-image: url(:/centerwidget/img/centerwidget/group_hot.png);border-style: outset;"
                  "border-width: 1px;border-radius: 0px; border-color:gray ; }"

                  "QPushButton:hover:pressed { background-image: url(:/centerwidget/img/centerwidget/group_hot.png);border-style: outset;"
                  "border-width: 1px;border-radius: 0px; border-color: rgb(0,155,144); }"

                  "QPushButton { background-image: url(:/centerwidget/img/centerwidget/group_normal.png);border-style: outset;"
                  "border-width: 0px;border-radius: 0px; border-color: beige; }"
                             );
    m_btnChatRecord->setStyleSheet(
                "QPushButton:hover:!pressed { background-image: url(:/centerwidget/img/centerwidget/chatrecord_hot.png);border-style: outset;"
                  "border-width: 1px;border-radius: 0px; border-color: gray; }"

                  "QPushButton:hover:pressed { background-image: url(:/centerwidget/img/centerwidget/chatrecord_hot.png);border-style: outset;"
                  "border-width: 1px;border-radius: 0px; border-color: rgb(0,155,144); }"

                  "QPushButton { background-image: url(:/centerwidget/img/centerwidget/chatrecord_normal.png);border-style: outset;"
                  "border-width: 0px;border-radius: 0px; border-color: beige; }"
                             );


    if( 0==item ){
        m_btnUsers->setStyleSheet(
                    "QPushButton { background-image: url(:/centerwidget/img/centerwidget/users_hot.png);border-style: outset;"
                    "border-width: 0px;border-radius: 0px; border-color: beige; }"
                               );
    }else if(1==item){
        m_btnGroups->setStyleSheet(
                    "QPushButton { background-image: url(:/centerwidget/img/centerwidget/group_hot.png);border-style: outset;"
                    "border-width: 0px;border-radius: 0px; border-color: beige; }"
                               );
    }else{
        m_btnChatRecord->setStyleSheet(
                    "QPushButton { background-image: url(:/centerwidget/img/centerwidget/chatrecord_hot.png);border-style: outset;"
                    "border-width: 0px;border-radius: 0px; border-color: beige; }"
                               );
    }

}

void CenterWidget::OnClickBtnUsers()
{
    UpdateTabs(0);
    InitUsersListWidget(theHosts);
}

void CenterWidget::OnClickBtnGroups()
{
    UpdateTabs(1);
    InitGroupsListWidget();
}

void CenterWidget::OnClickBtnChatRecords()
{
    UpdateTabs(2);
    InitChatRecordsListWidget();
}
void CenterWidget::InitChatRecordsListWidget()
{
    m_richlist->clear();

    string strFile(":/centerwidget/img/centerwidget/group_logo16.ico");
    ChatRecordsListItem * myitem = new ChatRecordsListItem(strFile.c_str(),"研发部", m_richlist);
    QListWidgetItem * Item = new QListWidgetItem();
    m_richlist->addItem(Item);
    Item->setSizeHint(myitem->sizeHint());
    m_richlist->setItemWidget(Item,myitem);

    myitem = new ChatRecordsListItem(":/TitleBar/img/titlebar/ms32.png","敏敏", m_richlist);
    Item = new QListWidgetItem();
    m_richlist->addItem(Item);
    Item->setSizeHint(myitem->sizeHint());
    m_richlist->setItemWidget(Item,myitem);
}

void CenterWidget::InitGroupsListWidget()
{
    m_richlist->clear();

    string strFile(":/centerwidget/img/centerwidget/group_logo16.ico");
    GroupsListItem * myitem = new GroupsListItem(strFile.c_str(),"研发部", m_richlist);
    QListWidgetItem * Item = new QListWidgetItem();
    m_richlist->addItem(Item);
    Item->setSizeHint(myitem->sizeHint());
    m_richlist->setItemWidget(Item,myitem);

    myitem = new GroupsListItem(strFile.c_str(),"销售部", m_richlist);
    Item = new QListWidgetItem();
    m_richlist->addItem(Item);
    Item->setSizeHint(myitem->sizeHint());
    m_richlist->setItemWidget(Item,myitem);
}
void CenterWidget::UpdateHostInfos()
{
    HOSTINFO item;
    item.OS = MS_WIN8;
    item.strAccount = "zm";
    item.strFriendlyName = "敏敏";
    item.strHostName = "zm-pc";
    item.ips.push_back("192.168.2.31");
    theHosts.push_back(item);
    item.OS = LINUX;
    item.strAccount = "paj";
    item.strFriendlyName = "";
    item.strHostName = "paj-pc";
    item.ips.clear();
    item.ips.push_back("192.168.2.11");
    theHosts.push_back(item);

    item.OS = LINUX;
    item.strAccount = "chj";
    item.strFriendlyName = "caohongjian";
    item.strHostName = "chj-pc";
    item.ips.clear();
    item.ips.push_back("192.168.2.121");
    item.ips.push_back("232.11.2.71");
    theHosts.push_back(item);

}

void CenterWidget::InitUsersListWidget(const vector<HOSTINFO> & hosts)
{
    m_richlist->clear();

    for(unsigned int i=0;i!=hosts.size();++i){
        string strUser = hosts[i].strFriendlyName;
        string strFile;

        if(strUser=="")   strUser = hosts[i].strAccount;

        if(hosts[i].OS == LINUX )   strFile = ":/TitleBar/img/titlebar/linux32.png";
        else            strFile = ":/TitleBar/img/titlebar/ms32.png";

        UsersListItem * myitem = new UsersListItem(strFile.c_str(),strUser.c_str(),hosts[i].ips[0].c_str(), m_richlist);
        QListWidgetItem * Item = new QListWidgetItem();
        //Item->setData(Qt::UserRole,);
        m_richlist->addItem(Item);
        Item->setSizeHint(myitem->sizeHint());
        m_richlist->setItemWidget(Item,myitem);
    }

}

void CenterWidget::OnSearching(const QString & str)
{
    if(str.isEmpty()){
        UpdateTabs(0);
        InitUsersListWidget(theHosts);
    }


    std::vector<HOSTINFO>  results;

    //******************************
    //search for 'str'
    for(unsigned int i=0; i<theHosts.size();++i){
        const HOSTINFO & hi = theHosts[i];
        QString qsFriendlyname(hi.strFriendlyName.c_str());
        QString qsHost(hi.strHostName.c_str());
        QString qsAccount(hi.strAccount.c_str());

        if(qsFriendlyname.contains(str,Qt::CaseInsensitive)||
                qsHost.contains(str,Qt::CaseInsensitive)||
                qsAccount.contains(str,Qt::CaseInsensitive)
                )
        {
            results.push_back(hi);
            continue;
        }


        for(unsigned int j=0; j<hi.ips.size();++j){
            QString qsIP(hi.ips[j].c_str());
            if(qsIP.contains(str,Qt::CaseInsensitive)){
                results.push_back(hi);
                break;
            }
        }
    }

    //update ui
    UpdateTabs(0);
    InitUsersListWidget(results);
}

void CenterWidget::OnNewChatSession(QListWidgetItem* item)
{
    QString strItemName;


    //...........................................
    //获取list item相关联的name
    UsersListItem * myitem = dynamic_cast<UsersListItem*>(m_richlist->itemWidget(item));
    if( myitem )
    {
        strItemName = myitem->GetItemName();
    }
    else
    {
        GroupsListItem * myitem = dynamic_cast<GroupsListItem*>(m_richlist->itemWidget(item));
        if( myitem )
        {
           strItemName = myitem->GetItemName();
        }
        else
        {
            ChatRecordsListItem * myitem = dynamic_cast<ChatRecordsListItem*>(m_richlist->itemWidget(item));
            if( myitem )
            {
                strItemName = myitem->GetItemName();
            }
        }
    }

    emit evtNewSession(strItemName);
}
