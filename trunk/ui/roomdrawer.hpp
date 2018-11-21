#ifndef ROOMDRAWER_HPP
#define ROOMDRAWER_HPP

#include "qmlgenericobject.hpp"
#include "berrymotetypes.hpp"

class RoomDrawer
: public QmlGenericObject
{
public:
    RoomDrawer(QString objectName, QObject *pRootObj);
    ~RoomDrawer();

    void init();
    void setRooms(BERRYMOTE::Rooms &rooms);

public slots:

private:
    QmlGenericObject *mpQmlRoomGrid;
    QmlGenericObject *mpQmlRoomButtons[BERRYMOTE::MAX_ROOMS];

};

#endif // ROOMDRAWER_HPP
