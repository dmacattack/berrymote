#include "roomdrawer.hpp"
#include <QDebug>

// anonymous namespace
namespace
{
    // qml props
    const char* QML_OBJ_ROOMGRID     = "gridRooms";
    const char* QML_OBJ_ROOMBTN      = "roomButton";

    // qml props
    const char* QML_PROP_TITLE      = "title";
    const char* QML_PROP_ICON       = "icon";

    // button indexes
    enum eBTN_IDS
    {
        eBTN_TBD,
        eBTN_ROOM_BUTTON_OFFSET = 200
    };
}

/*!
 * \brief RoomDrawer::RoomDrawer
 * \param objectName
 * \param pRootObj
 */
RoomDrawer::RoomDrawer(QString objectName, QObject *pRootObj)
: QmlGenericObject (objectName, pRootObj)
, mpQmlRoomGrid(nullptr)
{
    // init the qml room buttons
    for (int i = 0; i< BERRYMOTE::MAX_ROOMS; i++)
    {
        mpQmlRoomButtons[i] = nullptr;
    }
}

/*!
 * \brief RoomDrawer::~RoomDrawer
 */
RoomDrawer::~RoomDrawer()
{
    if (mpQmlRoomGrid)
    {
        delete mpQmlRoomGrid;
    }

    for (int i = 0; i< BERRYMOTE::MAX_ROOMS; i++)
    {
        if (mpQmlRoomButtons[i])
        {
            delete mpQmlRoomButtons[i];
        }
    }
}

/*!
 * \brief RoomDrawer::init
 */
void RoomDrawer::init()
{
    mpQmlRoomGrid = new QmlGenericObject( QML_OBJ_ROOMGRID, this->getQmlObj() );

    qDebug() << "roomdrawer init . roomgrid is null " << (mpQmlRoomGrid == nullptr) ;

    if (mpQmlRoomGrid != nullptr)
    {
        int sz = mpQmlRoomGrid->getQmlObj()->children().size();

        for (int i = 0 ; i< sz; i++)
        {
            // all the buttons are added by their ID. So for debugging the id provides
            // a string since the qml isn't discovered by name
            QObject *pObj = mpQmlRoomGrid->getQmlObj()->children().at(i);
            int btnId = eBTN_ROOM_BUTTON_OFFSET + i;
            mpQmlRoomButtons[i] = new QmlGenericObject(QML_OBJ_ROOMBTN, btnId, pObj);
            mpQmlRoomButtons[i]->setId(btnId);
        }
    }
}

/*!
 * \brief RoomDrawer::setRooms
 * set the rooms on the drawer
 * \param rooms
 */
void RoomDrawer::setRooms(BERRYMOTE::Rooms &rooms)
{
    int i = 0;
    int numRooms = rooms.size() > BERRYMOTE::MAX_ROOMS ? BERRYMOTE::MAX_ROOMS : rooms.size();

    qDebug() << "setRooms - nRooms" << numRooms;

    for (; i < numRooms; i++)
    {
        qDebug() << "setRooms " << i << ":" << rooms.at(i)->getName() << rooms.at(i)->getIcon();

        // show the button
        mpQmlRoomButtons[i]->setVisibility(true);
        // set the title
        mpQmlRoomButtons[i]->setProperty(QML_PROP_TITLE, rooms.at(i)->getName() );
        // set the icon
        mpQmlRoomButtons[i]->setProperty(QML_PROP_ICON, rooms.at(i)->getIcon() );
    }

    // hide the rest of the buttons
    for (; i < BERRYMOTE::MAX_ROOMS; i++)
    {
        mpQmlRoomButtons[i]->setVisibility(false);
    }
}



