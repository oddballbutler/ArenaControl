#ifndef K8055USBBOARD_H
#define K8055USBBOARD_H

#include <QObject>
#include "controlboardinterface.h"

const int BOARD_ADDRESS = 0; //depending on sk5 and sk6

class K8055USBBoard : public QObject, public ControlBoardInterface
{
    Q_OBJECT

public:
    explicit K8055USBBoard(QObject *parent = 0);

signals:

public slots:
    long OpenDevice(long x);
    void CloseDevice(void);
    long ReadAnalogChannel(long x);
    void ReadAllAnalog(long* x, long* y);
    void OutputAnalogChannel(long x, long y);
    void OutputAllAnalog(long x, long y);
    void ClearAnalogChannel(long x);
    void ClearAllAnalog(void);
    void SetAnalogChannel(long x);
    void SetAllAnalog(void);
    void WriteAllDigital(long x);
    void ClearDigitalChannel(long x);
    void ClearAllDigital(void);
    void SetDigitalChannel(long x);
    void SetAllDigital(void);
    int ReadDigitalChannel(long x);
    long ReadAllDigital(void);
    void ResetCounter(long x);
    long ReadCounter(long x);
    int SetCounterDebounceTime(long x, long y);
    bool isConnected();

private:
    typedef long (*k8055OpenDeviceFunct)(long);
    typedef void (*k8055CloseDeviceFunct)(void);
    typedef long (*k8055ReadAnalogChannelFunct)(long);
    typedef void (*k8055ReadAllAnalogFunct)(long*, long*);
    typedef void (*k8055OutputAnalogChannelFunct)(long, long);
    typedef void (*k8055OutputAllAnalogFunct)(long, long);
    typedef void (*k8055ClearAnalogChannelFunct)(long);
    typedef void (*k8055ClearAllAnalogFunct)(void);
    typedef void (*k8055SetAnalogChannelFunct)(long);
    typedef void (*k8055SetAllAnalogFunct)(void);
    typedef void (*k8055WriteAllDigitalFunct)(long);
    typedef void (*k8055ClearDigitalChannelFunct)(long);
    typedef void (*k8055ClearAllDigitalFunct)(void);
    typedef void (*k8055SetDigitalChannelFunct)(long);
    typedef void (*k8055SetAllDigitalFunct)(void);
    typedef int (*k8055ReadDigitalChannelFunct)(long);
    typedef long (*k8055ReadAllDigitalFunct)(void);
    typedef void (*k8055ResetCounterFunct)(long);
    typedef long (*k8055ReadCounterFunct)(long);
    typedef int (*k8055SetCounterDebounceTimeFunct)(long, long);
    k8055OpenDeviceFunct k8055OpenDevice;
    k8055CloseDeviceFunct k8055CloseDevice;
    k8055ReadAnalogChannelFunct k8055ReadAnalogChannel;
    k8055ReadAllAnalogFunct k8055ReadAllAnalog;
    k8055OutputAnalogChannelFunct k8055OutputAnalogChannel;
    k8055OutputAllAnalogFunct k8055OutputAllAnalog;
    k8055ClearAnalogChannelFunct k8055ClearAnalogChannel;
    k8055ClearAllAnalogFunct k8055ClearAllAnalog;
    k8055SetAnalogChannelFunct k8055SetAnalogChannel;
    k8055SetAllAnalogFunct k8055SetAllAnalog;
    k8055WriteAllDigitalFunct k8055WriteAllDigital;
    k8055ClearDigitalChannelFunct k8055ClearDigitalChannel;
    k8055ClearAllDigitalFunct k8055ClearAllDigital;
    k8055SetDigitalChannelFunct k8055SetDigitalChannel;
    k8055SetAllDigitalFunct k8055SetAllDigital;
    k8055ReadDigitalChannelFunct k8055ReadDigitalChannel;
    k8055ReadAllDigitalFunct k8055ReadAllDigital;
    k8055ResetCounterFunct k8055ResetCounter;
    k8055ReadCounterFunct k8055ReadCounter;
    k8055SetCounterDebounceTimeFunct k8055SetCounterDebounceTime;
    bool connected;

};

#endif // K8055USBBOARD_H
