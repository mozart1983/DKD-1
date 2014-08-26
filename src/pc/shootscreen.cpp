#include "shootscreen.h"
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QImage>
#include <QDebug>
#include <QPainter>
#include <math.h>
#include "shootscreenmenuwnd.h"
#include "shootscreenbuddy.h"

ShootScreen::ShootScreen(QWidget *parent) :
    QWidget(parent),
    buddy(NULL),
    state(SS_INIT),
    shootcursor(QPixmap(":/shootscreen/img/shootscreen/shotscreen_cursor.png"),6,0 )
{
    //铺满整个桌面
    rcClient = QApplication::desktop()->screenGeometry();
    setFixedSize(rcClient.width(),rcClient.height());

    //创建 截屏信息显示 窗口
    CreateBuddy();

    CreateMenuWnd();

    //framless
    setWindowFlags(Qt::FramelessWindowHint);


    //更换光标
    this->setCursor(shootcursor);

    //enable mouse tracking
    this->setMouseTracking(true);

    //截屏
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen){
        originalPixmap = screen->grabWindow(0);
    }
}

void ShootScreen::CreateMenuWnd()
{
    menuwnd = new ShootScreenMenuWnd(this);
    menuwnd->hide();
}

void ShootScreen::mousePressEvent(QMouseEvent * evt)
{
    //如果是左键点击，则绘制矩形
    if( evt->button() == Qt::LeftButton )
    { 
        if( state==SS_INIT )
        {
            state = SS_LBUTTON;
            originalPoint = evt->globalPos();
            buddy->hide();
        }
        else if( state == SS_READY )
        {
            lastpoint = evt->globalPos();
        }
    }
    else //否则，则回滚操作
    {
        if( state == SS_INIT )
        {
            state = SS_EXIT;
            this->close();
            emit evtShootScreenClose();
        }
        else if( state == SS_LBUTTON )
        {
            state = SS_INIT;
            buddy->show();
            this->update();
        }
        else if( state == SS_READY )
        {
            state = SS_INIT;
            UpdateBuddy( evt->globalPos() );
            this->setCursor(shootcursor);
            this->update();
        }
    }
}

void ShootScreen::mouseReleaseEvent(QMouseEvent * evt)
{
    if( evt->button()==Qt::LeftButton && state==SS_LBUTTON )
    {
        state = SS_READY;
    }
    else if( state==SS_LBUTTON )
    {
        state = SS_READY;
    }

}

void ShootScreen::paintEvent(QPaintEvent * /*evt*/)
{
    QPainter painter(this);
    painter.drawPixmap(rcClient, originalPixmap, rcClient);

    if( state == SS_LBUTTON || state == SS_READY)
    {
        //绘制选择区域
        QRectF rt(originalPoint,nowposition);
        painter.setPen(Qt::blue);
        painter.drawRect(rt);

        //还要绘制8个点
        const int width = nowposition.x() - originalPoint.x();
        const int height = nowposition.y() - originalPoint.y();
        painter.drawRect(originalPoint.x()-1,originalPoint.y()-1,2,2);//左上角
        painter.drawRect(originalPoint.x()+width-1,originalPoint.y()-1,2,2);//右上角
        painter.drawRect(originalPoint.x()-1,originalPoint.y()+height-1,2,2);//左下角
        painter.drawRect(originalPoint.x()+width-1,originalPoint.y()+height-1,2,2);//右下角
        painter.drawRect(originalPoint.x()+width/2-1,originalPoint.y()-1,2,2);//上中
        painter.drawRect(originalPoint.x()+width-1,originalPoint.y()+height/2-1,2,2);//右中
        painter.drawRect(originalPoint.x()-1,originalPoint.y()+height/2-1,2,2);//左中
        painter.drawRect(originalPoint.x()+width/2-1,originalPoint.y()+height-1,2,2);//底中

        //绘制区域左上角的 区域大小
        QRect rcText(originalPoint.x(),originalPoint.y()-20,200,20);
        QString strSize;
        strSize.sprintf("%dx%d",abs(width),abs(height));
        painter.drawText(rcText,strSize);
    }
}

void ShootScreen::UpdateBuddy(const QPoint & point)
{
    const int buddy_x = buddy->width();
    const int buddy_y = buddy->height();
    int x = point.x()+20;
    int y = point.y()+20;

    //在桌面右边缘和底部要调整buddy窗口的位置
    if( x+buddy_x > rcClient.width())
    {
        x = point.x() - 20 - buddy_x;
    }
    if( y+buddy_y > rcClient.height() )
    {
        y = point.y() - 20 - buddy_y;
    }

    buddy->show();
    buddy->move(x,y);

    //更新像素RGB值
    QPixmap ptPixmap = originalPixmap.copy(point.x(),point.y(),1,1);
    QImage ptImage = ptPixmap.toImage();
    QRgb rgb = ptImage.pixel(0,0);
    QString strRGB;
    strRGB.sprintf("RGB(%d,%d,%d)",qRed(rgb),qGreen(rgb),qBlue(rgb));
    emit evtUpdateRGB(strRGB);
}

void ShootScreen::mouseMoveEvent(QMouseEvent * event)
{
    QPoint point = event->globalPos();

    if( state == SS_INIT )
    {
        UpdateBuddy( point );
    }
    else if( state == SS_LBUTTON )
    {
        nowposition = event->globalPos();
        this->update();
    }
    else if( state == SS_READY )
    {


        if( point.x()>originalPoint.x() && point.x()<nowposition.x()
                && point.y()>originalPoint.y() && point.y()<nowposition.y() )
        {//区域内
            this->setCursor(Qt::SizeAllCursor);

            //拖动选中区域
            if( event->buttons() & Qt::LeftButton )
            {
                const int x_offset = point.x() - lastpoint.x();
                const int y_offset = point.y() - lastpoint.y();

                QRect rt1(originalPoint,nowposition);

                originalPoint.setX( originalPoint.x()+x_offset );
                originalPoint.setY( originalPoint.y()+y_offset );
                nowposition.setX( nowposition.x()+x_offset );
                nowposition.setY( nowposition.y()+y_offset );

                QRect rt2(originalPoint,nowposition);
                QRect cliprt = rt2.united(rt1);
                cliprt.adjust(-2,-25,2,2);
                this->update(cliprt);

                lastpoint = point;
            }
        }
        //区域垂直边界
        else if(point.x()==originalPoint.x() || point.x()==nowposition.x() )
        {
            this->setCursor(Qt::SizeHorCursor);
        }
        //区域横向边界
        else if(point.y()==originalPoint.y() || point.y()==nowposition.y() )
        {
            this->setCursor(Qt::SizeVerCursor);
        }
        else
        {
            this->setCursor(shootcursor);
        }
    }

}

ShootScreen::~ShootScreen()
{
    if(buddy)
    {
        delete buddy;
        buddy = NULL;
    }
}

void ShootScreen::CreateBuddy()
{
    buddy = new ShootScreenBuddy(this);
    buddy->hide();
    buddy->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    connect(this,SIGNAL(evtUpdateRGB(const QString&)),buddy,SLOT(RGBUpdate(const QString & )));
}
