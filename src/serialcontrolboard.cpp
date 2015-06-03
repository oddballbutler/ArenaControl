#include "serialcontrolboard.h"

SerialControlBoard::SerialControlBoard(const QString &name, QObject *parent)
{
    serialPort = new QSerialPort(name,this);
}

SerialControlBoard::SerialControlBoard(const QSerialPortInfo &serialPortInfo, QObject *parent)
{
    serialPort = new QSerialPort(serialPortInfo, this);
}

SerialControlBoard::~SerialControlBoard()
{
    delete serialPort;
}
