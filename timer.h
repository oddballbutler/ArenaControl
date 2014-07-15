#ifndef TIMER_H
#define TIMER_H

#include <QLCDNumber>
#include <QTimer>

class Timer : public QLCDNumber
{
    Q_OBJECT
public:
    explicit Timer(QWidget *parent = 0);
    int getCurrentSeconds() const;

signals:
    void timerDone(bool);
    void timerStart(bool);
    void timerPause(bool);
    void timerSet();
    void startCountDown1();
    void startCountDown0();
    void almostDone();
    void timeChange(const Timer *n);

public slots:
    void pause();
    void start();
    void stop();
    void set(int _seconds);
    void reset();
    void displayTime();
    void done();


private slots:
    void countDown();
    void startCountDown();

private:
    int seconds;
    int currentSeconds;
    int tempSeconds;
    QTimer timer;

    void startCountDownFinished();

};

#endif // TIMER_H
