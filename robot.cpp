#include "robot.h"

Robot::Robot(QObject *parent) :
    QObject(parent),
    name(""),
    weight(NONE),
    wins(0),
    losses(0)
{
    return;
}

Robot::Robot(const Robot & other) :
    QObject(other.parent()),
    name(other.name),
    weight(other.weight),
    wins(other.wins),
    losses(other.losses)
{
    return;
}

Robot & Robot::operator= (const Robot & other)
{
    if(this != &other)
    {
        name = other.name;
        weight = other.weight;
        wins = other.wins;
        losses = other.losses;
    }
    return *this;
}

QString Robot::getName()
{
    return name;
}

void Robot::setName(const QString &_name)
{
    name = _name;
}

Robot::WeightClass Robot::getWeightClass()
{
    return weight;
}

void Robot::setWeightClass(const WeightClass _weight)
{
    weight = _weight;
}

void Robot::clearRecord()
{
    wins = 0;
    losses = 0;
}

void Robot::giveWin()
{
    wins++;
}

void Robot::giveloss()
{
    losses++;
}

int Robot::getWins()
{
    return wins;
}

int Robot::getLosses()
{
    return losses;
}
