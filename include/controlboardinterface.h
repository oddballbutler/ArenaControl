#ifndef CONTROLBOARDINTERFACE_H
#define CONTROLBOARDINTERFACE_H

class ControlBoardInterface
{
public:
    virtual ~ControlBoardInterface() {}

    virtual void initialize() = 0;
    virtual QStringList commands() const = 0;
    virtual void callCommand(const QString & command) = 0;

};

#endif // CONTROLBOARDINTERFACE_H
