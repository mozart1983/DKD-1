#ifndef SKINMGR_H
#define SKINMGR_H

#include <QLabel>
#include <QFrame>
#include <QPushButton>

class PushButton;

class SkinMgr : public QFrame
{
    Q_OBJECT
public:
    explicit SkinMgr(QFrame *parent = 0);
private:
    PushButton * m_btnClose; //关闭按钮
    QLabel * m_labTitle; //标题
    QPushButton * m_btnSkin[10];
    bool is_move;
    QPoint press_point;//鼠标按下去的点

protected:
    virtual void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:
    void SigSkinChange(const QString &);
public slots:
    void OnSkinChange();
    void OnSkinChange0();
    void OnSkinChange1();
    void OnSkinChange2();
    void OnSkinChange3();
    void OnSkinChange4();
    void OnSkinChange5();
    void OnSkinChange6();
    void OnSkinChange7();
    void OnSkinChange8();
    void OnSkinChange9();
};

#endif // SKINMGR_H
