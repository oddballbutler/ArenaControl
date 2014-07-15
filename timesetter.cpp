#include "timesetter.h"
#include <QShortcut>

TimeSetter::TimeSetter(QWidget *parent) :
    QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(timeSet()));
    return;
}

void TimeSetter::timeSet(){
    emit timeChange(timeSetLineEdit->text().toInt());
}

void TimeSetter::setLineEdit(QLineEdit * lineEdit)
{
    timeSetLineEdit = lineEdit;
    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_Return), timeSetLineEdit);
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(timeSet()));
}
