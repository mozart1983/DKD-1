#ifndef P2PCHATWND_H
#define P2PCHATWND_H
#include <QPushButton>
#include <QFrame>
#include "defs.h"

namespace Ui {
class P2PChatWnd;
}


#define P2PCHAT_TITLEBAR_HEIGHT 60
#define P2PCHAT_BOTTOMBAR_HEIGHT 30
class ShootScreen;

class P2PChatWnd : public QFrame
{
    Q_OBJECT

public:
    explicit P2PChatWnd(QFrame *parent = 0);
    ~P2PChatWnd();

    void SetPeerHostInf(const HOSTINFO &);
private:
    Ui::P2PChatWnd *ui;
    bool is_move;
    QPoint press_point;//鼠标按下去的点
    HOSTINFO _peerhost;
    ShootScreen * ShootScreenWgt;

    void ChangeHTMLSend2View();
    void InsertTalker(const QString & tag);
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent * event);
signals:
    void evtCloseChatWnd(const QString&);
public slots:
    void OnSkinChange(const QString &);
    void OnCloseWnd();
private slots:
    void OnStorBtn();
    void SendMsg();
    void OnFontChanged();
    void OnColorChanged();
    void OnSendImg();
    void OnAdjustWidgets();
    void OnShootScreen();
    void OnShootScreenClose();
};

#endif // P2PCHATWND_H
