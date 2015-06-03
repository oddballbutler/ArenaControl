#ifndef ARENACONTROL_H
#define ARENACONTROL_H

#include <QMainWindow>
#include <QSound>
#include "k8055usbboard.h"
#include "controllights.h"
#include "audiencescreen.h"
#include "controlboardinterface.h"

namespace Ui {
    class ArenaControl;
}

enum EventState{
    WAITING_ON_MATCH,
    WAITING_ON_TEAMS,
    COUNTDOWN,
    START_COUNTDOWN
};

class ArenaControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArenaControl(QWidget *parent = 0);
    ~ArenaControl();

public slots:
    void team1ButtonPress();
    void team2ButtonPress();
    void stateToStartCountDown();
    void stateToWaitingOnTeams();
    void stateToWaitingOnMatch();
    void stateToCountDown();

private slots:
    void audienceWindowActionTriggered();
    void checkInput();
    void timerDone();
    void timerPause();
    void prepareMatch();
    void stopMatch();
    void almostDone();
    void turnRedLightsOn();
    void turnYellowLightsOn();
    void turnGreenLightsOn();
    void turnLightsOff();
    void blinkLights();
    void turnLightsOn(const int _lights[]);
    void updateTeam1Name();
    void updateTeam2Name();

private:
    Ui::ArenaControl *ui;
    AudienceScreen *screen2;
    ControlBoardInterface *controlBoard;
    K8055USBBoard *usbBoard;
    EventState state;
    bool team1Ready;
    bool team2Ready;
    QTimer *checkInputTimer;
    ControlLights * lights;
    int lightArray [3];
    QSound *ready;
    bool bBlink;
    bool bCheckInput;
    int timerTime;
    int blinkTime;
    int blinkDiff;

};

#endif // ARENACONTROL_H
