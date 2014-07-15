#include "startstopbutton.h"

StartStopButton::StartStopButton(QWidget *parent) :
    QPushButton(parent),
    startState(true)
{
    connect(this,SIGNAL(clicked()),this,SLOT(buttonClick()));
}

void StartStopButton::buttonClick(){

    if(startState)
        emit startClick();
    else
        emit stopClick();

    changeState();

}

void StartStopButton::changeState()
{
    startState = (startState) ? false : true;
    if(startState)
        this->setText("Start Match");
    else
        this->setText("Pause Match");
}

void StartStopButton::changeState(bool start)
{
    if(start)
    {
        this->setText("Start Match");
        startState = true;
    }
    else
    {
        this->setText("Pause Match");
        startState = false;
    }
}
