#include "bottomwidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

BottomWidget::BottomWidget(QFrame *parent) :
    QFrame(parent)
{
    setFixedHeight(50);

    m_btnSetup = new QPushButton(this);
    m_btnFileRecords = new QPushButton(this);
    m_btnContact = new QPushButton(this);
    m_btnFresh = new QPushButton(this);

    m_btnSetup->setStyleSheet(
                "QPushButton:hover:!pressed { background-image: url(:/bottombar/img/bottombar/settings.png);border-style: outset;"
                 "border-width: 1px;border-radius: 2px; border-color: green; }"

                 "QPushButton:hover:pressed { background-image: url(:/bottombar/img/bottombar/settings.png);border-style: outset;"
                 "border-width: 1px;border-radius: 2px; border-color: red; }"

                 "QPushButton { background-image: url(:/bottombar/img/bottombar/settings.png);"
                 "background-position: center;"
                 "background-repeat: no-repeat;"
                 "background-origin: content;    }"
                                );
    m_btnSetup->setFixedSize(35,35);
    m_btnSetup->setToolTip("设置");
    m_btnSetup->setFocusPolicy(Qt::NoFocus);
    m_btnSetup->setFlat(true);


    m_btnFileRecords->setStyleSheet(
                "QPushButton:hover:!pressed { background-image: url(:/bottombar/img/bottombar/files.png);border-style: outset;"
                 "border-width: 1px;border-radius: 2px; border-color: green; }"

                 "QPushButton:hover:pressed { background-image: url(:/bottombar/img/bottombar/files.png);border-style: outset;"
                 "border-width: 1px;border-radius: 2px; border-color: red; }"

                 "QPushButton { background-image: url(:/bottombar/img/bottombar/files.png);"
                 "background-position: center;"
                 "background-repeat: no-repeat;"
                 "background-origin: content;    }"
                                );
    m_btnFileRecords->setFixedSize(22,22);
    m_btnFileRecords->setToolTip("查看文件传输记录");
    m_btnFileRecords->setFocusPolicy(Qt::NoFocus);
    m_btnFileRecords->setFlat(true);


    m_btnContact->setStyleSheet(
                "QPushButton:hover:!pressed { background-image: url(:/bottombar/img/bottombar/about.png);border-style: outset;"
                 "border-width: 1px;border-radius: 2px; border-color: green; }"

                 "QPushButton:hover:pressed { background-image: url(:/bottombar/img/bottombar/about.png);border-style: outset;"
                 "border-width: 1px;border-radius: 2px; border-color: red; }"

                 "QPushButton { background-image: url(:/bottombar/img/bottombar/about.png);"
                "background-position: center;"
                "background-repeat: no-repeat;"
                "background-origin: content;    }"
                                );
    m_btnContact->setFixedSize(22,22);
    m_btnContact->setToolTip("软件说明");
    m_btnContact->setFocusPolicy(Qt::NoFocus);
    m_btnContact->setFlat(true);


    m_btnFresh->setStyleSheet(
                "QPushButton:hover:!pressed { background-image: url(:/bottombar/img/bottombar/fresh.png);border-style: outset;"
                 "border-width: 1px;border-radius: 2px; border-color: green; }"

                 "QPushButton:hover:pressed { background-image: url(:/bottombar/img/bottombar/fresh.png);border-style: outset;"
                 "border-width: 1px;border-radius: 2px; border-color: red; }"

                 "QPushButton { background-image: url(:/bottombar/img/bottombar/fresh.png);"
                "background-position: center;"
                "background-repeat: no-repeat;"
                "background-origin: content;    }"
                                );
    m_btnFresh->setFixedSize(22,22);
    m_btnFresh->setToolTip("刷新好友列表");
    m_btnFresh->setFocusPolicy(Qt::NoFocus);
    m_btnFresh->setFlat(true);


    QHBoxLayout * mainlayout = new QHBoxLayout(this);
    mainlayout->addStretch(1);
    mainlayout->addWidget(m_btnSetup,0,Qt::AlignBottom);
    mainlayout->addStretch(2);
    mainlayout->addWidget(m_btnFresh,0,Qt::AlignBottom);
    mainlayout->addStretch(1);
    mainlayout->addWidget(m_btnFileRecords,0,Qt::AlignBottom);
    mainlayout->addStretch(1);
    mainlayout->addWidget(m_btnContact,0,Qt::AlignBottom);
    mainlayout->addStretch(5);
    mainlayout->setContentsMargins(1, 10, 25, 5);


    setObjectName("bottombar");
    setStyleSheet("QFrame#bottombar {background-image:url(:/bottombar/img/bottombar/mask.png)}");


    connect(m_btnContact,SIGNAL(clicked()),this,SLOT(OnBtnClickAbout()));
}

void BottomWidget::OnBtnClickAbout()
{
    QMessageBox msgBox(this);
    msgBox.setText("bug提交/建议：598082720@qq.com");
    msgBox.exec();
}
