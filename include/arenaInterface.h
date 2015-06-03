#ifndef ARENAINTERFACE_H
#define ARENAINTERFACE_H

class ArenaInterface
{
public:
    virtual ~ArenaInterface();

    virtual QWidget getWidget();
};

#define ArenaInterface_iid "com.carolinacombat.ArenaControl.ArenaInterface"

Q_DECLARE_INTERFACE(ArenaInterface, ArenaInterface_iid)

#endif // ARENAINTERFACE_H
