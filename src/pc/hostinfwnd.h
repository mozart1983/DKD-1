#ifndef HOSTINFWND_H
#define HOSTINFWND_H

#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
class PushButton;

class HostInfWnd : public QFrame
{
    Q_OBJECT
public:
    explicit HostInfWnd(QFrame *parent = 0);
private:
    PushButton * m_btnClose; //关闭按钮
    QLabel * m_labTitle; //标题

    QLabel * m_labFriendlyName;
    QLabel * m_labOS;
    QLabel * m_labLoginUser;
    QLabel * m_labHostName;
    QLabel * m_labIPs;

    QLabel * m_labOS_value;
    QLabel * m_labLoginUser_value;
    QLabel * m_labHostName_value;
    QLabel * m_labIPs_value;

    QLineEdit * m_editFriendname;
    bool is_move;
    QPoint press_point;//鼠标按下去的点

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:
    void OnSkinChange(const QString &);
};
#endif // HOSTINFWND_H
