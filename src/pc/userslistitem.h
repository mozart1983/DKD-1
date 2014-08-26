#ifndef USERSLISTITEM_H
#define USERSLISTITEM_H

#include <QWidget>
class QLabel;
class QString;

class DKDListItemProtocol
{
public:
    virtual QString GetItemName()const=0;
protected:
    QString m_name;//对于好友列表项来说，是备注名或者主机登陆账户，组列表是组名，文件传输列表是文件名称

};

class UsersListItem : public QWidget,public DKDListItemProtocol
{
    Q_OBJECT
public:
    explicit UsersListItem(const QString & strHeaderPicFile,
                           const QString & strUser,
                           const QString & strIP,
                           QWidget *parent = 0);

    virtual QSize	sizeHint() const   {       return QSize(100,48);   }
    virtual QString GetItemName()const    {       return m_name;   }

private:
    QLabel * m_labAddress;
    QLabel * m_labHeaderPic;
    QLabel * m_labUser;

signals:

public slots:

};


class GroupsListItem : public QWidget,public DKDListItemProtocol
{
    Q_OBJECT
public:
    explicit GroupsListItem(const QString & strPicFile,
                           const QString & strName,
                           QWidget *parent = 0);

    virtual QSize	sizeHint() const  {     return QSize(100,28);  }
    virtual QString GetItemName()const    {       return m_name;   }
private:

    QLabel * m_labPic;
    QLabel * m_labName;

signals:

public slots:

};

typedef GroupsListItem ChatRecordsListItem;

#endif // USERSLISTITEM_H
