#ifndef TIMESETTER_H
#define TIMESETTER_H

#include <QPushButton>
#include <QLineEdit>

class TimeSetter : public QPushButton
{
    Q_OBJECT
public:
    explicit TimeSetter(QWidget *parent = 0);
    void setLineEdit(QLineEdit * lineEdit);

signals:
    void timeChange(int);

public slots:
    void timeSet();
private:
    QLineEdit * timeSetLineEdit;
};

#endif // TIMESETTER_H
