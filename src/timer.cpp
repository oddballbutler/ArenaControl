#include "timer.h"
#include <iostream>
#include <QSound>
using namespace std;

Timer::Timer(QWidget *parent) :
    QLCDNumber(parent),
    seconds(120),
    currentSeconds(seconds),
    timer(new QTimer(this))
{
    return;
}

void Timer::countDown()
{
    if(currentSeconds > 0)
        currentSeconds--;
    displayTime();
    emit timeChange(this);

    if(currentSeconds < 11)
        emit almostDone();

    switch (currentSeconds)
    {
    case 10:
        QSound::play(":/resources/10.wav");
        break;
    case 9:
        QSound::play(":/resources/9.wav");
        break;
    case 8:
        QSound::play(":/resources/8.wav");
        break;
    case 7:
        QSound::play(":/resources/7.wav");
        break;
    case 6:
        QSound::play(":/resources/6.wav");
        break;
    case 5:
        QSound::play(":/resources/5.wav");
        break;
    case 4:
        QSound::play(":/resources/4.wav");
        break;
    case 3:
        QSound::play(":/resources/3.wav");
        break;
    case 2:
        QSound::play(":/resources/2.wav");
        break;
    case 1:
        QSound::play(":/resources/1.wav");
        break;
    }

    if(currentSeconds == 0)
    {
        QSound::play(":/resources/BUZZER.WAV");
        timer.stop();
        emit timerDone(true);
        return;
    }
}

void Timer::displayTime()
{
    int min = currentSeconds / 60;
    QString minString = QString::number(min);

    int sec = currentSeconds % 60;
    QString secString = QString::number(sec);
    if(sec < 10)
        secString.prepend("0");

    QString text = minString + ":" + secString;
    display(text);
}

void Timer::set(int _seconds)
{
    if(_seconds >= 0)
    {
        seconds = _seconds;
        currentSeconds = seconds;
        displayTime();
    }

    emit timerSet();
    emit timeChange(this);
}

void Timer::pause()
{
    timer.stop();
    emit timerPause(true);
}

void Timer::start()
{
    timer.start(1000);
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(countDown()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(startCountDown()));
    tempSeconds = currentSeconds;
    currentSeconds = 3;
    QSound::play(":/resources/beep-6.wav");
    displayTime();
    emit timerStart(true);
    emit timeChange(this);
}

void Timer::reset()
{
    set(seconds);
}

void Timer::done()
{
    timer.stop();
    emit timerDone(true);
}

void Timer::stop()
{
    timer.stop();
}

void Timer::startCountDown()
{
    currentSeconds--;
    displayTime();
    emit timeChange(this);
    if(currentSeconds == 0)
    {
        QSound::play(":/resources/beep-7.wav");
        startCountDownFinished();
        return;
    }
    else if(currentSeconds == 1)
    {
        emit startCountDown1();
    }
    QSound::play(":/resources/beep-6.wav");
}

void Timer::startCountDownFinished()
{
    currentSeconds = tempSeconds;
    displayTime();
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(startCountDown()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(countDown()));
    emit startCountDown0();
    emit timeChange(this);
}

int Timer::getCurrentSeconds() const
{
    return currentSeconds;
}
