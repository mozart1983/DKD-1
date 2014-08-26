#ifndef SHOOTSCREENMENUWND_H
#define SHOOTSCREENMENUWND_H

#include <QWidget>

namespace Ui {
class ShootScreenMenuWnd;
}

class ShootScreenMenuWnd : public QWidget
{
    Q_OBJECT

public:
    explicit ShootScreenMenuWnd(QWidget *parent = 0);
    ~ShootScreenMenuWnd();

private:
    Ui::ShootScreenMenuWnd *ui;
};

#endif // SHOOTSCREENMENUWND_H
