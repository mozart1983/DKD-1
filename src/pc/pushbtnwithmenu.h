#ifndef PUSHBTNWITHMENU_H
#define PUSHBTNWITHMENU_H

#include <QPushButton>

class QAction;
class PushbtnWithMenu : public QPushButton
{
    Q_OBJECT
public:
    explicit PushbtnWithMenu(QWidget *parent = 0);
private:
    QAction * actionEnter;
    QAction * actionCtrlEnter;
protected:
    virtual void	mouseReleaseEvent(QMouseEvent * e);

signals:

public slots:
    void OnEnter(bool);
    void OnCtrlEnter(bool);
};

#endif // PUSHBTNWITHMENU_H
