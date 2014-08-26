#ifndef DKDMOVABLEWIDGET_H
#define DKDMOVABLEWIDGET_H

#include <QWidget>

class DKDMovableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKDMovableWidget(QWidget *parent = 0);

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent*);
private:
    QPoint m_offset;
signals:
    void sigChatbarMoving();
public slots:

};

#endif // DKDMOVABLEWIDGET_H
