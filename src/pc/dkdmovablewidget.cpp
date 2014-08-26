#include "dkdmovablewidget.h"
#include <QPoint>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>

DKDMovableWidget::DKDMovableWidget(QWidget *parent) :
    QWidget(parent)
{
}

void DKDMovableWidget::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void DKDMovableWidget::mousePressEvent(QMouseEvent* event)
{
    if (isWindow())
        m_offset = event->globalPos() - this->pos();
    else
        m_offset = event->pos();
}

void DKDMovableWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (isWindow())
        move(event->globalPos() - m_offset);
    else
    {
        int y = ( mapToParent(event->pos() - m_offset) ).y();
        const int top = 120;
        const int bottom = parentWidget()->height()-90;

        if( y < top )
            y = top;
        else if( y>bottom )
            y = bottom;
        move(1,y);

        emit(sigChatbarMoving());
    }
}

void DKDMovableWidget::mouseReleaseEvent(QMouseEvent* )
{
    m_offset = QPoint();
}
