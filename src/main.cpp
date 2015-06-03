#include <QApplication>
#include "arenacontrol.h"
#include "audiencescreen.h"
#include "team.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArenaControl w;
    w.show();

    return a.exec();
}
