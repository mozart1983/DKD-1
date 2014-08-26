#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QFrame>
class QPushButton;

class BottomWidget : public QFrame
{
    Q_OBJECT
public:
    explicit BottomWidget(QFrame *parent = 0);

private:
    QPushButton * m_btnSetup;
    QPushButton * m_btnFileRecords;
    QPushButton * m_btnContact;
    QPushButton * m_btnFresh;


signals:

public slots:
    void OnBtnClickAbout();
};

#endif // BOTTOMWIDGET_H
