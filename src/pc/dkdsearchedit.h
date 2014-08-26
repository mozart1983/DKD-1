#ifndef DKDSEARCHEDIT_H
#define DKDSEARCHEDIT_H

#include <QLineEdit>


class DKDSearchEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit DKDSearchEdit(QWidget *parent = 0);


    void Init();
    void Searching();

    //virtual void focusInEvent(QFocusEvent * e);
    virtual void focusOutEvent(QFocusEvent * e);
    virtual void mousePressEvent(QMouseEvent * e);
   // virtual void keyPressEvent(QMouseEvent * e);
    bool event(QEvent *e);
signals:
    void sigSearchStop();
public slots:
    void OnTextChanged(const QString & text);
};

#endif // DKDSEARCHEDIT_H
