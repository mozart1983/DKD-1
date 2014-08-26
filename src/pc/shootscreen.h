#ifndef SHOOTSCREEN_H
#define SHOOTSCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QRect>
#include <QPoint>
#include <QCursor>
class QLabel;
class ShootScreenBuddy;
class ShootScreenMenuWnd;

enum SS_STATE{
      SS_EXIT, //退出截屏
      SS_INIT,    //buddy窗口随鼠标游动
      SS_LBUTTON,  //绘制选中区域
      SS_READY //已经选中状态
     };
class ShootScreen : public QWidget
{
    Q_OBJECT
public:
    explicit ShootScreen(QWidget *parent = 0);
    ~ShootScreen();

private:
    QPixmap originalPixmap;
    ShootScreenBuddy * buddy;
    ShootScreenMenuWnd * menuwnd;
    SS_STATE state;
    QRect rcClient;
    QPoint originalPoint;//左键点击的位置
    QPoint nowposition; //拖动区域的右下角
    QCursor shootcursor;
    QPoint lastpoint;

    void CreateBuddy();
    void CreateMenuWnd();
    void UpdateBuddy(const QPoint & );
protected:
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
signals:
    void evtUpdateRGB(const QString &);
    void evtShootScreenClose();
public slots:

};

#endif // SHOOTSCREEN_H
