#ifndef CONTROLLIGHTS_H
#define CONTROLLIGHTS_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include "k8055usbboard.h"

class ControlLights : public QObject
{
    Q_OBJECT
public:
    explicit ControlLights(K8055USBBoard *_usbBoard, QWidget *parent = 0);

signals:

public slots:
    void yellowLights();
    void greenLights();
    void redLights();
    void turnLightsOn(const int _lights[]);
    void clearLights();
    void allLights();
    void blinkLights(const int _lights[]);
    //void sequenceLights(const int _lights[], int msec);

private slots:
    //void sequenceLights();
    void updateLights();

public:
    void connectLights(QLabel *_redLight, QLabel *_yellowLight, QLabel *_greenLight);
    bool redLightsOn();
    bool yellowLightsOn();
    bool greenLightsOn();

private:
    QLabel *redLight;
    QLabel *yellowLight;
    QLabel *greenLight;
    K8055USBBoard *usbBoard;
    int lights [3];
    int tempLights[3];
    QTimer *timer;

};

#endif // CONTROLLIGHTS_H
