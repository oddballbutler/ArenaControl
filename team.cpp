#include "team.h"

Team::Team(QObject *parent) :
    QAbstractItemModel(parent),
    name(""),
    members(),
    robots()
{
    return;
}

QString Team::getName()
{
    return name;
}

void Team::setName(const QString & _name)
{
    name = _name;
}

const QList<QString>& Team::getMembers()
{
    return members;
}

void Team::addMember(const QString & _name)
{
   members.append(_name);
}

const QList<Robot>& Team::getRobots()
{
    return robots;
}

void Team::addRobot(const QString & _name, const Robot::WeightClass _weight)
{
    Robot newBot(this);
    newBot.setName(_name);
    newBot.setWeightClass(_weight);
    robots.append(newBot);
}
