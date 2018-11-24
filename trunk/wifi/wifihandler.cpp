#include "wifihandler.hpp"
#include <QDebug>

/*!
 * \brief WifiHandler::WifiHandler
 */
WifiHandler::WifiHandler()
: mSSID("")
, mPassphrase("")
{

}

/*!
 * \brief WifiHandler::~WifiHandler
 */
WifiHandler::~WifiHandler()
{

}

/*!
 * \brief WifiHandler::setWifiCreds
 * \param ssid
 * \param pass
 */
void WifiHandler::setWifiCreds(QString ssid, QString pass)
{
    mSSID = ssid;
    mPassphrase = pass;

    qDebug() << "rc'd wifi ssid/pass : " << ssid << pass;

    // TODO connect to the given wifi
    emit setWifiConnected(false);
}

