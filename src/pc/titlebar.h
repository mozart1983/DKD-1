#ifndef TITLEBAR_H
#define TITLEBAR_H
#include <QPushButton>
#include <QWidget>
#include "push_button.h"

class QLabel;

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);

private:
    QLabel * m_labTitle;
    PushButton * m_btnClose;
    PushButton * m_btnMin;
    PushButton * m_btnSkin;
    QPushButton * m_btnPicture;
    QLabel * m_labUser;
    bool is_move;
    QPoint press_point;//鼠标按下去的点

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void evtClose();
    void evtMinWnd();
    void evtSkinMgr();
    void evtShowHostInf();
};

#endif // TITLEBAR_H
