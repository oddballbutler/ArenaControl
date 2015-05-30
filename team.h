#ifndef TEAM_H
#define TEAM_H

#include <QAbstractItemModel>

class Team : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit Team(QObject *parent = 0);

signals:

public slots:

};

#endif // TEAM_H
