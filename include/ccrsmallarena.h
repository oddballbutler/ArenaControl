#ifndef CCRSMALLARENA_H
#define CCRSMALLARENA_H

#include <QObject>
#include "arenaInterface.h"

class CCRSmallArena : public QObject, public ArenaInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ArenaInterface_iid)
    Q_INTERFACES(ArenaInterface)

public:
    QWidget getWidget();

    CCRSmallArena(QObject *parent);


};

#endif // CCRSMALLARENA_H
