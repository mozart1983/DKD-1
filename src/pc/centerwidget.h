#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H
#include "defs.h"
#include <QWidget>


class QListWidget;
class QLineEdit;
class QPushButton;
class QListWidgetItem;
class DKDSearchEdit;

class CenterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CenterWidget(QWidget *parent = 0);

private:
    DKDSearchEdit * m_editSearch;
    QPushButton * m_btnUsers;
    QPushButton * m_btnGroups;
    QPushButton * m_btnChatRecord;
    QListWidget * m_richlist;


    void UpdateTabs(int item);
    void InitUsersListWidget(const vector<HOSTINFO> &);
    void InitChatRecordsListWidget();
    void InitGroupsListWidget();

    void UpdateHostInfos();
signals:
    void evtNewSession(const QString & );
private slots:
    void OnClickBtnUsers();
    void OnClickBtnGroups();
    void OnClickBtnChatRecords();
    void OnNewChatSession(QListWidgetItem*);
    void OnSearching(const QString & );
    void OnSearchStop();
};

#endif // CENTERWIDGET_H
