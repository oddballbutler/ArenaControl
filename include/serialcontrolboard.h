#ifndef SERIALCONTROLBOARD_H
#define SERIALCONTROLBOARD_H

#include <QObject>
#include "controlboardinterface.h"
#include <QtSerialPort/QtSerialPort>

class SerialControlBoard : public QObject, public ControlBoardInterface
{
    Q_OBJECT
public:

    SerialControlBoard(const QString &name, QObject *parent);
    SerialControlBoard(const QSerialPortInfo &serialPortInfo, QObject *parent);
    ~SerialControlBoard();
signals:

public slots:

private:
    QSerialPort *serialPort;
};

#endif // SERIALCONTROLBOARD_H
