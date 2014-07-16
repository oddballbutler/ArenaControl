#include "k8055usbboard.h"
#include <QLibrary>
#include <iostream>
#include <QTimer>
#include <QtDebug>
using namespace std;

K8055USBBoard::K8055USBBoard(QObject *parent) :
    QObject(parent),
    connected(false)
{
    QLibrary myLib("k8055");
    if (!myLib.load())
        qDebug() << myLib.errorString();
    else
        qDebug() << "library loaded";

    k8055OpenDevice = (k8055OpenDeviceFunct) myLib.resolve("OpenDevice");
    k8055CloseDevice = (k8055CloseDeviceFunct) myLib.resolve("CloseDevice");
    k8055ReadAnalogChannel = (k8055ReadAnalogChannelFunct) myLib.resolve("ReadAnalogChannel");
    k8055ReadAllAnalog = (k8055ReadAllAnalogFunct) myLib.resolve("ReadAllAnalog");
    k8055OutputAnalogChannel = (k8055OutputAnalogChannelFunct) myLib.resolve("OutputAnalogChannel");
    k8055OutputAllAnalog = (k8055OutputAllAnalogFunct) myLib.resolve("OutputAllAnalog");
    k8055ClearAnalogChannel = (k8055ClearAnalogChannelFunct) myLib.resolve("ClearAnalogChannel");
    k8055ClearAllAnalog = (k8055ClearAllAnalogFunct) myLib.resolve("ClearAllAnalog");
    k8055SetAnalogChannel = (k8055SetAnalogChannelFunct) myLib.resolve("SetAnalogChannel");
    k8055SetAllAnalog = (k8055SetAllAnalogFunct) myLib.resolve("SetAllAnalog");
    k8055WriteAllDigital = (k8055WriteAllDigitalFunct) myLib.resolve("WriteAllDigital");
    k8055ClearDigitalChannel = (k8055ClearDigitalChannelFunct) myLib.resolve("ClearDigitalChannel");
    k8055ClearAllDigital = (k8055ClearAllDigitalFunct) myLib.resolve("ClearAllDigital");
    k8055SetDigitalChannel = (k8055SetDigitalChannelFunct) myLib.resolve("SetDigitalChannel");
    k8055SetAllDigital = (k8055SetAllDigitalFunct) myLib.resolve("SetAllDigital");
    k8055ReadDigitalChannel = (k8055ReadDigitalChannelFunct) myLib.resolve("ReadDigitalChannel");
    k8055ReadAllDigital = (k8055ReadAllDigitalFunct) myLib.resolve("ReadAllDigital");
    k8055ResetCounter = (k8055ResetCounterFunct) myLib.resolve("ResetCounter");
    k8055ReadCounter = (k8055ReadCounterFunct) myLib.resolve("ReadCounter");
    k8055SetCounterDebounceTime = (k8055SetCounterDebounceTimeFunct) myLib.resolve("SetCounterDebounceTime");

    long address = BOARD_ADDRESS;
    if(OpenDevice(address) == address)
        connected = true;


    SetCounterDebounceTime(1, 1000);
    SetCounterDebounceTime(2, 1000);

}

long K8055USBBoard::OpenDevice(long x)
{
    return k8055OpenDevice(x);
}

void K8055USBBoard::CloseDevice(void)
{
    k8055CloseDevice();
}

long K8055USBBoard::ReadAnalogChannel(long x)
{
    return k8055ReadAnalogChannel(x);
}

void K8055USBBoard::ReadAllAnalog(long* x, long* y)
{
    return k8055ReadAllAnalog(x,y);
}

void K8055USBBoard::OutputAnalogChannel(long x, long y)
{
    k8055OutputAnalogChannel(x,y);
}

void K8055USBBoard::OutputAllAnalog(long x, long y)
{
    k8055OutputAllAnalog(x,y);
}

void K8055USBBoard::ClearAnalogChannel(long x)
{
    k8055ClearAnalogChannel(x);
}

void K8055USBBoard::ClearAllAnalog(void)
{
    k8055ClearAllAnalog();
}

void K8055USBBoard::SetAnalogChannel(long x)
{
    k8055SetAnalogChannel(x);
}

void K8055USBBoard::SetAllAnalog(void)
{
    k8055SetAllAnalog();
}

void K8055USBBoard::WriteAllDigital(long x)
{
    k8055WriteAllDigital(x);
}

void K8055USBBoard::ClearDigitalChannel(long x)
{
    k8055ClearDigitalChannel(x);
}

void K8055USBBoard::ClearAllDigital(void)
{
    k8055ClearAllDigital();
}

void K8055USBBoard::SetDigitalChannel(long x)
{
    k8055SetDigitalChannel(x);
}

void K8055USBBoard::SetAllDigital(void)
{
    k8055SetAllDigital();
}

int K8055USBBoard::ReadDigitalChannel(long x)
{
    return k8055ReadDigitalChannel(x);
}

long K8055USBBoard::ReadAllDigital(void)
{
    return k8055ReadAllDigital();
}

void K8055USBBoard::ResetCounter(long x)
{
    k8055ResetCounter(x);
}

long K8055USBBoard::ReadCounter(long x)
{
    return k8055ReadCounter(x);
}

void K8055USBBoard::SetCounterDebounceTime(long x, long y)
{
    k8055SetCounterDebounceTime(x,y);
}

bool K8055USBBoard::isConnected()
{
    return connected;
}
