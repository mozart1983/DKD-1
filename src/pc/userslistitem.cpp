#include "userslistitem.h"
#include <QLabel>
#include <QHBoxLayout>

/*
 * layout:
 *
 *  icon(small)    |icon(bigger)|  label1
 *                 |            |  label2
 *
 */

UsersListItem::UsersListItem(const QString & strHeaderPicFile,
                             const QString & strUser,
                             const QString & strIP,
                             QWidget *parent ) :
      QWidget(parent)
{
    m_name = strUser;

    m_labHeaderPic = new QLabel(this);
    m_labUser = new QLabel(this);
    m_labAddress = new QLabel(this);

    m_labHeaderPic->setFixedSize(32,32);
    QString myss = QString("QLabel {  background-image: url(%1);}").arg(strHeaderPicFile);
    m_labHeaderPic->setStyleSheet(myss);

    m_labUser->setText(strUser);
    m_labAddress->setText(strIP);
    m_labAddress->setStyleSheet("QLabel {color:rgb(109,125,74)}");

    QVBoxLayout * vlay = new QVBoxLayout();
    vlay->addWidget(m_labUser);
    vlay->addStretch();
    vlay->addWidget(m_labAddress);
    vlay->setContentsMargins(0,0,0,0);

    QHBoxLayout * lay = new QHBoxLayout(this);
    lay->addWidget(m_labHeaderPic);
    lay->addLayout(vlay);
    lay->addSpacing(2);
    lay->setContentsMargins(4,8,0,8);
}

GroupsListItem::GroupsListItem(const QString & strPicFile,
                               const QString & strName,
                               QWidget *parent):
      QWidget(parent)
{

    m_name = strName;

    m_labPic = new QLabel(this);
    m_labName = new QLabel(this);

    m_labPic->setFixedSize(16,16);
    QString myss = QString("QLabel {  background-image: url(%1);}").arg(strPicFile);
    m_labPic->setStyleSheet(myss);

    m_labName->setText(strName);


    QHBoxLayout * lay = new QHBoxLayout(this);
    lay->addWidget(m_labPic);
    lay->addWidget(m_labName);
    lay->addSpacing(2);
    lay->setContentsMargins(4,6,0,6);

}

