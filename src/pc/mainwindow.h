#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QString>
#include <QFrame>
#include <map>

class TitleBar;
class CenterWidget;
class BottomWidget;
class SkinMgr;
class HostInfWnd;
class P2PChatWnd;

class DKDFrame : public QFrame
{
    Q_OBJECT

public:
    explicit DKDFrame(QFrame *parent = 0);
    ~DKDFrame();

    QString m_strMainSkin;
protected:
    void paintEvent(QPaintEvent *);
    virtual void closeEvent(QCloseEvent * event);
private:
    TitleBar * m_titlebar;
    CenterWidget * m_centerWgt;
    BottomWidget * m_bottomWgt;
    SkinMgr * m_skinmgr;
    HostInfWnd * m_hostinfwnd;
    std::map<QString,QWidget*> m_mapChatWnd;
signals:
    void SigSkinChangeBroadCast(const QString &);
private slots:
    void CloseEvtHandler();
    void SkinMgrHandler();
    void OnSkinChange(const QString &);
    void OnShowHostInf();
    void OnNewSessionLanuch(const QString &);
    void OnChatWndClose(const QString &);
};

extern DKDFrame * theMainWnd;
#endif // MAINWINDOW_H
