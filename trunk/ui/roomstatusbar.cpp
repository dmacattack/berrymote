/*!
 * \file
 * \brief
 * RoomStatusBar class to wrap the QML status bar object
 */
#include "roomstatusbar.hpp"
#include <QDebug>

// anonymous namespace
namespace
{
    // qml props
    const char* QML_PROP_ROOM_TITLE = "roomTitle";
    const char* QML_PROP_WIFI_CONN  = "wifiConnected";
}

/*!
 * \brief RoomStatusBar::RoomStatusBar
 * \param objectName - qml object name of the status bar
 * \param pRootObj - qml root object of the status bar
 */
RoomStatusBar::RoomStatusBar(QString objectName, QObject *pRootObj)
: QmlGenericObject(objectName, pRootObj)
{
    qDebug() << "obj = " << objectName ;
}

/*!
 * \brief RoomStatusBar::~RoomStatusBar
 * destructor
 */
RoomStatusBar::~RoomStatusBar()
{
}

/*!
 * \brief RoomStatusBar::setTitle
 * \param title - string of the title
 */
void RoomStatusBar::setTitle(const QString &title)
{
    this->setProperty(QML_PROP_ROOM_TITLE, title);
}

/*!
 * \brief RoomStatusBar::enableWifi
 * \param isEnabled
 */
void RoomStatusBar::enableWifi(bool isConnected)
{
    this->setProperty(QML_PROP_WIFI_CONN, isConnected);
}

/*!
 * \brief RoomStatusBar::setBattLevel
 * \param lvl - battery % level
 */
void RoomStatusBar::setBattLevel(int lvl)
{
    // TODO implement
    lvl = lvl;
}
