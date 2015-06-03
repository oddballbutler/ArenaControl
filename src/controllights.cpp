#include "controllights.h"

ControlLights::ControlLights(K8055USBBoard *_usbBoard, QWidget *parent) :
    QObject(parent),
    usbBoard(_usbBoard),
    timer(new QTimer(this))
{
}

void ControlLights::yellowLights()
{
    lights[0] = 0;
    lights[1] = 1;
    lights[2] = 0;
    updateLights();
}

void ControlLights::greenLights()
{
    lights[0] = 1;
    lights[1] = 0;
    lights[2] = 0;
    updateLights();
}

void ControlLights::redLights()
{
    lights[0] = 0;
    lights[1] = 0;
    lights[2] = 1;
    updateLights();
}

void ControlLights::allLights()
{
    lights[0] = 1;
    lights[1] = 1;
    lights[2] = 1;
    updateLights();
}

void ControlLights::turnLightsOn(const int _lights[])
{
    lights[0] = _lights[0];
    lights[1] = _lights[1];
    lights[2] = _lights[2];
    updateLights();
}

void ControlLights::blinkLights(const int _lights[])
{
    if(_lights[0])
        lights[0] = !lights[0];
    if(_lights[1])
        lights[1] = !lights[1];
    if(_lights[2])
        lights[2] = !lights[2];
    updateLights();
}

void ControlLights::connectLights(QLabel *_redLight, QLabel *_yellowLight, QLabel *_greenLight)
{
    redLight = _redLight;
    yellowLight = _yellowLight;
    greenLight = _greenLight;
}

void ControlLights::clearLights()
{
    lights[0] = 0;
    lights[1] = 0;
    lights[2] = 0;
    updateLights();
}

bool ControlLights::redLightsOn()
{
    return lights[2];
}

bool ControlLights::yellowLightsOn()
{
    return lights[1];
}

bool ControlLights::greenLightsOn()
{
    return lights[0];
}

void ControlLights::updateLights()
{
    usbBoard->ClearAllDigital();
    redLight->setPixmap(QPixmap(QString::fromUtf8(":/resources/lightRedOff.jpg")));
    yellowLight->setPixmap(QPixmap(QString::fromUtf8(":/resources/lightYellowOff.jpg")));
    greenLight->setPixmap(QPixmap(QString::fromUtf8(":/resources/lightGreenOff.jpg")));

    if(lights[0])
    {
        usbBoard->SetDigitalChannel(1);
        greenLight->setPixmap(QPixmap(QString::fromUtf8(":/resources/lightGreenOn.jpg")));
    }

    if(lights[1])
    {
        usbBoard->SetDigitalChannel(2);
        yellowLight->setPixmap(QPixmap(QString::fromUtf8(":/resources/lightYellowOn.jpg")));
    }

    if(lights[2])
    {
        usbBoard->SetDigitalChannel(3);
        redLight->setPixmap(QPixmap(QString::fromUtf8(":/resources/lightRedOn.jpg")));
    }
}
