#ifndef BUTTONS_H
#define BUTTONS_H

#include <QObject>

class Buttons : public QObject
{
    Q_OBJECT
public:
    explicit Buttons(QObject *parent = 0);

signals:
    void team1ButtonPressed();
    void team2ButtonPressed();

public slots:
    void pressTeam1Button();
    void pressTeam2Button();
};

#endif // BUTTONS_H
