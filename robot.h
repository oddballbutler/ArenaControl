#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>

class Robot : public QObject
{
public:
    enum WeightClass{
        NONE,
        FAIRY,
        ANT,
        BEETLE,
        MANTIS,
        HOBBY,
        LIGHT,
        MIDDLE,
        HEAVY,
        SUPERHEAVY
    };

    Q_OBJECT
public:
    explicit Robot(QObject *parent = 0);
    Robot(const Robot & other);
    Robot & operator= (const Robot & other);

signals:

public slots:
    QString getName();
    void setName(const QString &_name);
    WeightClass getWeightClass();
    void setWeightClass(const WeightClass _weight);
    void clearRecord();
    void giveWin();
    void giveloss();
    int getWins();
    int getLosses();

private:
    QString name;
    WeightClass weight;
    int wins;
    int losses;

};

#endif // ROBOT_H
