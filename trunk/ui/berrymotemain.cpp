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
, mConfigParser  ( *new ConfigParser() )
, mIRHandler     ( *new IRHandler() )
, mIPHandler     ( *new IPHandler() )
, mHardkeyHandler( *new HardKeyHandler() )
, mWifiHandler   ( *new WifiHandler() )
, mpRooms(nullptr)
, mCurrentRoomIdx(0)
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
    delete &mIRHandler;
    delete &mIPHandler;
    delete &mHardkeyHandler;
    delete &mWifiHandler;

    if (mpRooms)
    {
        delete mpRooms;
    }
}

/*!
 * \brief BerrymoteMain::init
 * Init all the qml objects and any sub-objects
 */
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

        // allocate the drawer and sub-objects
        mpRoomDrawer = new RoomDrawer(QML_OBJ_ROOMDRAWER, mpRootObj);
        mpRoomDrawer->init();

        // init the hardkwy handler
        mHardkeyHandler.init();

        // connect signals/slots
        QObject::connect( mpRootObj, SIGNAL(buttonClick(int)), this, SLOT(onButtonClick(int)) );
        QObject::connect( &mHardkeyHandler, SIGNAL(hardKeyPressed(KEYS::eKEYS)), this, SLOT(onHardKeyPressed(KEYS::eKEYS)) );
        QObject::connect( this, SIGNAL(setWifiCreds(QString, QString)), &mWifiHandler, SLOT(setWifiCreds(QString, QString)) );

        // init the wifi
        initWifi();

        // init the rooms
        initRooms();
    }
    else
    {
        qCritical() << "problem with configs";
    }
}

/*!
 * \brief BerrymoteMain::initWifi
 */
void BerrymoteMain::initWifi()
{
    // init the wifi info
    QString ssid = "";
    QString pass = "";
    if ( mConfigParser.getWifiCreds(&ssid, &pass) )
    {
        emit setWifiCreds(ssid, pass);
    }
    else
    {
        qCritical() << "couldn't get the wifi credentials";
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
        if (mpRooms->size() > 0)
        {
            // set the status bar title
            mpRoomStatusBar->setTitle(mpRooms->at(0)->getName());

            // set the rooms
            mpRoomDrawer->setRooms(*mpRooms);

            // set the super Buttons to the first room
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

/*!
 * \brief BerrymoteMain::onButtonClick
 * Slot callback for button clicks on the main.qml
 * \param btnID - id of the button that was clicked
 */
void BerrymoteMain::onButtonClick(int btnID)
{
    qDebug() << "clicked button ID:" << btnID;

    if ( (btnID >= eBTN_SUPER_BUTTON_OFFSET) &&
         (btnID < eBTN_ROOM_BUTTON_OFFSET) )
    {
        int sbIdx = btnID - eBTN_SUPER_BUTTON_OFFSET;
        ROOM::SuperButtons sb = mpRooms->at(mCurrentRoomIdx)->getSuperButtons();

        processSuperButton( sb.at(sbIdx) );
    }
    else if (btnID >= eBTN_ROOM_BUTTON_OFFSET)
    {
        // switch rooms by swtiching the superbuttons
        mCurrentRoomIdx = btnID - eBTN_ROOM_BUTTON_OFFSET;
        ROOM::SuperButtons sb = mpRooms->at(mCurrentRoomIdx)->getSuperButtons();
        setSuperButtons( sb );

        // update the title
        mpRoomStatusBar->setTitle(mpRooms->at(mCurrentRoomIdx)->getName());
    }
    else
    {
        // unhandled button
    }
}

/*!
 * \brief BerrymoteMain::onHardKeyPressed
 * \param key
 */
void BerrymoteMain::onHardKeyPressed(KEYS::eKEYS key)
{
    qDebug() << "pressed key " << key;
}

/*!
 * \brief BerrymoteMain::processSuperButton
 * \param btn
 */
void BerrymoteMain::processSuperButton(ROOM::tSuperButton btn)
{
    ROOM::eCMD_TYPE cmdType = btn.type;
    QJsonArray cmd          = btn.cmd;

    switch(cmdType)
    {
    case ROOM::eCMD_IR:
        mIRHandler.processCommand(cmd);
        break;
    case ROOM::eCMD_IP:
        mIPHandler.processCommand(cmd);
        break;
    default:
        qWarning() << "unknown cmd type";
        break;
    }
}
