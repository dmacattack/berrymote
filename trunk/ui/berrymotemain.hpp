#ifndef BERRYMOTEMAIN_H
#define BERRYMOTEMAIN_H

#include <QObject>
#include "qmlgenericobject.hpp"
#include "configparser.hpp"
#include "roomstatusbar.hpp"
#include "roomdrawer.hpp"
#include "berrymotetypes.hpp"

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
    void setSuperButtons(ROOM::SuperButtons &sb);
    void processSuperButton(ROOM::tSuperButton btn);

private:
    QObject *mpRootObj;
    QmlGenericObject *mpSuperButtonGrid;
    QmlGenericObject *mpSuperButtons[BERRYMOTE::MAX_SUPER_BUTTONS];

    RoomStatusBar *mpRoomStatusBar;
    RoomDrawer    *mpRoomDrawer;
    ConfigParser &mConfigParser;

    BERRYMOTE::Rooms *mpRooms;
    int mCurrentRoomIdx;
};

#endif // BERRYMOTEMAIN_H
