#ifndef STARTSTOPBUTTON_H
#define STARTSTOPBUTTON_H

#include <QPushButton>

class StartStopButton : public QPushButton
{
    Q_OBJECT
public:
    explicit StartStopButton(QWidget *parent = 0);
    enum State{
        START,
        STOP
    };

signals:
    void startClick();
    void stopClick();

public slots:
    void buttonClick();
    void changeState();
    void changeState(bool start);


private:
    bool startState;
};

#endif // STARTSTOPBUTTON_H
