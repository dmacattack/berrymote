#ifndef BERRYMOTEMAIN_H
#define BERRYMOTEMAIN_H

#include <QObject>
#include "qmlgenericobject.hpp"
#include "configparser.hpp"
#include "roomstatusbar.hpp"

namespace BERRYMOTE
{
    const int MAX_SUPER_BUTTONS = 6;
    const int MAX_ROOMS         = 3;
}

class BerrymoteMain
: public QObject
{
    Q_OBJECT
public:
    BerrymoteMain(QObject *pRootObj);
    ~BerrymoteMain();

    void init();

private slots:
    void onButtonClick(int btnID);

private:
    void initRooms();
    void setRooms(ROOM::Rooms &rooms);
    void setSuperButtons(ROOM::SuperButtons &sb);

private:
    QObject *mpRootObj;
    QmlGenericObject *mpSuperButtonGrid;
    QmlGenericObject *mpSuperButtons[BERRYMOTE::MAX_SUPER_BUTTONS];
    QmlGenericObject *mpRoomDrawer;
    QmlGenericObject *mpRoomGrid;
    QmlGenericObject *mpRoomButtons[BERRYMOTE::MAX_ROOMS];
    RoomStatusBar *mpRoomStatusBar;

    ConfigParser &mConfigParser;

    ROOM::Rooms *mpRooms;
};

#endif // BERRYMOTEMAIN_H
