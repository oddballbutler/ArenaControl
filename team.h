#ifndef TEAM_H
#define TEAM_H

#include <QAbstractItemModel>
#include "robot.h"

class Team : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit Team(QObject *parent = 0);

signals:

public slots:
    QString getName();
    void setName(const QString & _name);
    const QList<QString>& getMembers();
    void addMember(const QString & _name);
    const QList<Robot>& getRobots();
    void addRobot(const QString & _name, Robot::WeightClass _weight);

private:
    QString name;
    QList<QString> members;
    QList<Robot> robots;

};

#endif // TEAM_H
