#include "berrymotemain.hpp"
#include <QDebug>
#include <QJsonDocument>

// anonymous namespace
namespace
{
    // qml objects
    const char* QML_OBJ_STATUS_BAR  = "roomStatusBar";
    const char* QML_OBJ_SUPERBTNGRID = "gridSuperButtons";
    const char* QML_OBJ_SUPERBTN     = "superButton";
    const char* QML_OBJ_ROOMDRAWER   = "roomDrawer";

    // qml props
    const char* QML_PROP_TITLE      = "title";
    const char* QML_PROP_ICON       = "icon";

    // button indexes
    enum eBTN_IDS
    {
        eBTN_TBD,
        eBTN_SUPER_BUTTON_OFFSET = 100,
        eBTN_ROOM_BUTTON_OFFSET = 200
    };
}

// ctor
BerrymoteMain::BerrymoteMain(QObject *pRootObj)
: mpRootObj(pRootObj)
, mpSuperButtonGrid(nullptr)
, mpRoomStatusBar(nullptr)
, mpRoomDrawer(nullptr)
, mConfigParser(*new ConfigParser())
, mpRooms(nullptr)
{
    // init the super buttons objects
    for (int i = 0; i< BERRYMOTE::MAX_SUPER_BUTTONS; i++)
    {
        mpSuperButtons[i] = nullptr;
    }
}

// dtor
BerrymoteMain::~BerrymoteMain()
{
    // delete qml objects
    if (mpSuperButtonGrid)
    {
        delete mpSuperButtonGrid;
    }

    for (int i = 0; i< BERRYMOTE::MAX_SUPER_BUTTONS; i++)
    {
        if (mpSuperButtons[i])
        {
            delete mpSuperButtons[i];
        }
    }

    if (mpRoomDrawer)
    {
        delete mpRoomDrawer;
    }

    if (mpRoomStatusBar)
    {
        delete mpRoomStatusBar;
    }

    // delete objects
    delete &mConfigParser;

    if (mpRooms)
    {
        delete mpRooms;
    }
}

// init
void BerrymoteMain::init()
{
    // init the config parser first
    if ( mConfigParser.init() )
    {
        // allocate the status bar
        mpRoomStatusBar = new RoomStatusBar(QML_OBJ_STATUS_BAR, mpRootObj);

        // allocate the super button grid
        mpSuperButtonGrid = new QmlGenericObject(QML_OBJ_SUPERBTNGRID, mpRootObj);

        // allocate the buttons in the grid and assign button ids
        if (mpSuperButtonGrid != nullptr)
        {
            int sz = mpSuperButtonGrid->getQmlObj()->children().size();

            for (int i = 0; i< sz; i++)
            {
                // the buttons are added by their ID. So for debugging the id provides
                // a string since the qml isn't discovered by name
                QObject *pObj = mpSuperButtonGrid->getQmlObj()->children().at(i);
                int btnId = eBTN_SUPER_BUTTON_OFFSET + i;
                mpSuperButtons[i] = new QmlGenericObject(QML_OBJ_SUPERBTN, btnId, pObj);
                mpSuperButtons[i]->setId(btnId);
            }
        }

        // allocat the drawer and sub-objects
        mpRoomDrawer = new RoomDrawer(QML_OBJ_ROOMDRAWER, mpRootObj);
        mpRoomDrawer->init();

        // connect signals/slots
        QObject::connect( mpRootObj, SIGNAL(buttonClick(int)), this, SLOT(onButtonClick(int)) );

        // init the rooms
        initRooms();
    }
    else
    {
        qCritical() << "problem with configs";
    }
}

/*!
 * \brief BerrymoteMain::initRooms
 * init the UI Rooms from the config
 */

void BerrymoteMain::initRooms()
{
    mpRooms = new BERRYMOTE::Rooms();

    if ( mConfigParser.getRooms(mpRooms) )
    {
        // set the status bar title
        mpRoomStatusBar->setTitle(mpRooms->at(0)->getName());

        // set the rooms
        if (mpRooms->size() > 0)
        {
            mpRoomDrawer->setRooms(*mpRooms);
        }

        // set the super Buttons to the first room
        if (mpRooms->size() > 0)
        {
            ROOM::SuperButtons sb = mpRooms->at(0)->getSuperButtons();
            setSuperButtons( sb );
        }
    }
    else
    {
        qCritical() << "couldn't get the rooms";
    }
}

/*!
 * \brief BerrymoteMain::setSuperButtons
 * set the superbuttons on the main screen
 * \param sb - list of super buttons
 */
void BerrymoteMain::setSuperButtons(ROOM::SuperButtons &sb)
{
    int i = 0;
    int numSb = sb.size() > BERRYMOTE::MAX_SUPER_BUTTONS ? BERRYMOTE::MAX_SUPER_BUTTONS : sb.size();

    for (; i< numSb; i++)
    {
        // show the button
        mpSuperButtons[i]->setVisibility(true);
        // set the title
        mpSuperButtons[i]->setProperty(QML_PROP_TITLE, sb.at(i).name);
        // set the icon
        mpSuperButtons[i]->setProperty(QML_PROP_ICON, sb.at(i).icon);
    }

    // hide the rest of the super buttons
    for (; i< BERRYMOTE::MAX_SUPER_BUTTONS; i++)
    {
        mpSuperButtons[i]->setVisibility(false);
    }
}

// slot callback for button click
void BerrymoteMain::onButtonClick(int btnID)
{
    qDebug() << "clicked button ID:" << btnID;
}
