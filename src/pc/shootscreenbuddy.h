#ifndef SHOOTSCREENBUDDY_H
#define SHOOTSCREENBUDDY_H

#include <QWidget>

namespace Ui {
class ShootScreenBuddy;
}

class ShootScreenBuddy : public QWidget
{
    Q_OBJECT

public:
    explicit ShootScreenBuddy(QWidget *parent = 0);
    ~ShootScreenBuddy();

private:
    Ui::ShootScreenBuddy *ui;

private slots:
    void RGBUpdate(const QString &);
};

#endif // SHOOTSCREENBUDDY_H
