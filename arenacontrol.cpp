#include "arenacontrol.h"
#include "ui_arenacontrol.h"
#include "controllights.h"
#include "buttons.h"
#include <iostream>
#include <QIntValidator>
#include <QTimer>
#include <QCloseEvent>
#include <QMessageBox>
using namespace std;

ArenaControl::ArenaControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArenaControl),
    screen2(new AudienceScreen()),
    state(WAITING_ON_MATCH),
    team1Ready(false),
    team2Ready(false),
    timerTime(100),
    blinkTime(500),
    blinkDiff(0),
    bBlink(false),
    bCheckInput(false)
{
    ui->setupUi(this);

    connect(ui->startPushButton,SIGNAL(clicked()),ui->lcdNumber,SLOT(start()));
    connect(ui->pausePushButton,SIGNAL(clicked()),ui->lcdNumber,SLOT(pause()));
    connect(ui->prepareButton,SIGNAL(clicked()),ui->timeSetPushButton,SLOT(timeSet()));
    connect(ui->timeSetPushButton,SIGNAL(timeChange(int)),ui->lcdNumber,SLOT(set(int)));

    ui->timeSetPushButton->setLineEdit(ui->timeSetLineEdit);
    ui->lcdNumber->displayTime();
    QValidator *validator = new QIntValidator(1, 5999, this);
    ui->timeSetLineEdit->setValidator(validator);

    usbBoard = new K8055USBBoard(this);

    for(int i = 0; i < 3; i++)
        lightArray[i] = 0;
    lights = new ControlLights(usbBoard, this);
    lights->connectLights(ui->redLightLabel, ui->yellowLightLabel, ui->greenLightLabel);
    connect(ui->lcdNumber,SIGNAL(startCountDown1()),this,SLOT(turnYellowLightsOn()));
    connect(ui->lcdNumber,SIGNAL(startCountDown0()),this,SLOT(turnGreenLightsOn()));

    connect(ui->team1OverridePushButton,SIGNAL(clicked()), this,SLOT(team1ButtonPress()));
    connect(ui->team2OverridePushButton,SIGNAL(clicked()), this,SLOT(team2ButtonPress()));
    ui->startPushButton->setEnabled(false);
    connect(ui->lcdNumber,SIGNAL(timerStart(bool)),this,SLOT(stateToStartCountDown()));
    connect(ui->lcdNumber,SIGNAL(timerPause(bool)),this,SLOT(timerPause()));
    connect(ui->lcdNumber,SIGNAL(timerDone(bool)),this,SLOT(timerDone()));
    connect(ui->lcdNumber,SIGNAL(startCountDown0()),this,SLOT(stateToCountDown()));

    checkInputTimer = new QTimer(this);
    connect(checkInputTimer,SIGNAL(timeout()),this,SLOT(checkInput()));
    connect(ui->prepareButton,SIGNAL(clicked()),this,SLOT(prepareMatch()));
    connect(ui->endPushButton,SIGNAL(clicked()),this,SLOT(stopMatch()));
    connect(ui->lcdNumber,SIGNAL(almostDone()),this,SLOT(almostDone()));
    checkInputTimer->start(timerTime);
    stateToWaitingOnMatch();

    ready = new QSound("/Users/jeremybutler/Workspace/EventControl/sound113.wav",this);

    screen2->show();
    screen2->children();
    connect(ui->lcdNumber,SIGNAL(timeChange(const Timer*)),screen2,SLOT(updateTimer(const Timer*)));
    screen2->updateTimer(ui->lcdNumber);
    connect(screen2,SIGNAL(closed(bool)),ui->actionAudienceWindow,SLOT(toggle()));
    connect(ui->actionAudienceWindow,SIGNAL(triggered()),this,SLOT(audienceWindowActionTriggered()));
    ui->menuBar->setParent(NULL);
}

ArenaControl::~ArenaControl()
{
    delete ui;
    usbBoard->ClearAllDigital();
    usbBoard->CloseDevice();
}

void ArenaControl::team1ButtonPress()
{
    if(state == WAITING_ON_TEAMS)
    {
        if(!team1Ready)
        {
            team1Ready = true;
            ui->statusLabel->setText("Waiting on Team 2");
            ready->play();
        }
        if(team1Ready && team2Ready)
        {
            ui->startPushButton->setEnabled(true);
            ui->statusLabel->setText("Teams Ready. Press 'Start Match' button.");
            bBlink = true;
            bCheckInput = false;
        }
    }
    else if(state == COUNTDOWN)
    {
        ui->statusBar->showMessage("Team 1 Tapped Out", 5000);
        ui->statusLabel->setText("Team 1 Tapped Out");
        ui->lcdNumber->stop();
        bCheckInput = false;
        turnRedLightsOn();
        QSound::play("/Users/jeremybutler/Workspace/EventControl/BUZZER.WAV");
        QTimer::singleShot(5000, this, SLOT(stateToWaitingOnMatch()));
    }
}

void ArenaControl::team2ButtonPress()
{
    if(state == WAITING_ON_TEAMS)
    {
        if(!team2Ready)
        {
            team2Ready = true;
            ui->statusLabel->setText("Waiting on Team 1");
            ready->play();
        }
        if(team1Ready && team2Ready)
        {
            ui->startPushButton->setEnabled(true);
            ui->statusLabel->setText("Teams Ready. Press 'Start Match' button.");
            bBlink = true;
            bCheckInput = false;
        }
    }
    else if(state == COUNTDOWN)
    {
        ui->statusBar->showMessage("Team 2 Tapped Out", 5000);
        ui->statusLabel->setText("Team 2 Tapped Out");
        ui->lcdNumber->stop();
        bCheckInput = false;
        turnRedLightsOn();
        QSound::play("/Users/jeremybutler/Workspace/EventControl/BUZZER.WAV");
        QTimer::singleShot(5000, this, SLOT(stateToWaitingOnMatch()));
    }
}

void ArenaControl::stateToStartCountDown()
{
    checkInputTimer->stop();
    state = START_COUNTDOWN;
    ui->startPushButton->setEnabled(false);
    ui->endPushButton->setEnabled(false);
    ui->timeSetLineEdit->setEnabled(false);
    ui->timeSetPushButton->setEnabled(false);
    ui->lcdNumber->setStyleSheet("color:red");
    bBlink = false;
    bCheckInput = false;
    turnRedLightsOn();
    ui->statusLabel->setText("Match starts in:");
}

void ArenaControl::stateToCountDown()
{
    state = COUNTDOWN;
    bBlink = false;
    bCheckInput = true;
    checkInputTimer->start();
    ui->lcdNumber->setStyleSheet("");
    ui->startPushButton->setEnabled(false);
    ui->pausePushButton->setEnabled(true);
    ui->endPushButton->setEnabled(true);
    ui->statusLabel->setText("Match in Progress");
    ui->statusBar->showMessage("Match in Progress");
}

void ArenaControl::stateToWaitingOnMatch()
{
    state = WAITING_ON_MATCH;
    ui->endPushButton->setEnabled(false);
    ui->pausePushButton->setEnabled(false);
    ui->prepareButton->setEnabled(true);
    ui->timeSetLineEdit->setEnabled(true);
    ui->timeSetPushButton->setEnabled(true);
    bBlink = false;
    bCheckInput = false;
    checkInputTimer->stop();
    QTimer::singleShot(5000, this, SLOT(turnLightsOff()));
    ui->statusLabel->setText("Waiting for Next Match");
    team1Ready = false;
    team2Ready = false;
    ui->startPushButton->setEnabled(false);
}

void ArenaControl::stateToWaitingOnTeams()
{
    state = WAITING_ON_TEAMS;
    team1Ready = false;
    team2Ready = false;
    ui->endPushButton->setEnabled(true);
    ui->pausePushButton->setEnabled(false);
    ui->prepareButton->setEnabled(false);
    ui->timeSetLineEdit->setEnabled(true);
    ui->timeSetPushButton->setEnabled(true);
    bCheckInput = true;
    bBlink = true;
    checkInputTimer->start();
    turnYellowLightsOn();
    ui->startPushButton->setEnabled(false);
    ui->statusLabel->setText("Waiting on Teams");
}

void ArenaControl::timerDone()
{
    ui->statusBar->showMessage("Match Done", 5000);
    ui->lcdNumber->setStyleSheet("");
    screen2->updateTimer(ui->lcdNumber);
    turnRedLightsOn();
    stateToWaitingOnMatch();
}

void ArenaControl::timerPause()
{
    ui->statusBar->showMessage("Match Paused");
    turnYellowLightsOn();
    stateToWaitingOnTeams();
    ui->statusLabel->setText("Match Paused: Waiting on Teams to Ready");
}

void ArenaControl::prepareMatch()
{
    ui->statusBar->clearMessage();
    ui->lcdNumber->reset();
    stateToWaitingOnTeams();
}

void ArenaControl::stopMatch()
{
    ui->lcdNumber->done();
    ui->statusBar->clearMessage();
}

void ArenaControl::turnRedLightsOn()
{
    bool wasRunning = false;
    if (checkInputTimer->isActive())
        wasRunning = true;
    checkInputTimer->stop();
    lights->redLights();
    lightArray[0] = 0;
    lightArray[1] = 0;
    lightArray[2] = 1;
    if(wasRunning)
        checkInputTimer->start();
}

void ArenaControl::turnYellowLightsOn()
{
    bool wasRunning = false;
    if (checkInputTimer->isActive())
        wasRunning = true;
    checkInputTimer->stop();
    lights->yellowLights();
    lightArray[0] = 0;
    lightArray[1] = 1;
    lightArray[2] = 0;
    if(wasRunning)
        checkInputTimer->start();
}

void ArenaControl::turnGreenLightsOn()
{
    bool wasRunning = false;
    if (checkInputTimer->isActive())
        wasRunning = true;
    checkInputTimer->stop();
    lights->greenLights();
    lightArray[0] = 1;
    lightArray[1] = 0;
    lightArray[2] = 0;
    if(wasRunning)
        checkInputTimer->start();
}

void ArenaControl::blinkLights()
{
    blinkDiff += timerTime;
    if(blinkDiff > blinkTime)
    {
        lights->blinkLights(lightArray);
        blinkDiff = 0;
    }
}

void ArenaControl::turnLightsOn(const int _lights[])
{
    bool wasRunning = false;
    if (checkInputTimer->isActive())
        wasRunning = true;

    checkInputTimer->stop();
    lights->turnLightsOn(_lights);
    lightArray[0] = _lights[0];
    lightArray[1] = _lights[1];
    lightArray[2] = _lights[2];

    if(wasRunning)
        checkInputTimer->start();
}

void ArenaControl::turnLightsOff()
{
    bool wasRunning = false;
    if (checkInputTimer->isActive())
        wasRunning = true;

    checkInputTimer->stop();
    lights->clearLights();

    if(wasRunning)
        checkInputTimer->start();
}

void ArenaControl::almostDone()
{
    turnYellowLightsOn();
    ui->lcdNumber->setStyleSheet("color:yellow");
    screen2->updateTimer(ui->lcdNumber);
}

void ArenaControl::checkInput()
{
    bool wasRunning = false;
    if (checkInputTimer->isActive())
        wasRunning = true;

    checkInputTimer->stop();

    if(bBlink)
        blinkLights();

    if(bCheckInput)
    {
        if (usbBoard->ReadDigitalChannel(1))
            team1ButtonPress();
    }
    if(bCheckInput)
    {
        if (usbBoard->ReadDigitalChannel(2))
            team2ButtonPress();
    }
    usbBoard->ReadAllDigital();

    if(wasRunning)
        checkInputTimer->start();

    //cout << "Checking Input" << endl;
}

void ArenaControl::audienceWindowActionTriggered()
{
    if(!ui->actionAudienceWindow->isChecked()){
        screen2->hide();
    }
    else
    {
        screen2->show();
    }
}
