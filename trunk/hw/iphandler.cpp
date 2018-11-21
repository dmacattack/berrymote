/*!
 * \file
 * \brief
 * IP Handler class handles sending and receiving IP (internet protocol) Signals
 */
#include "iphandler.hpp"
#include <QDebug>
#include <QJsonDocument>

/*!
 * \brief IPHandler::IPHandler
 */
IPHandler::IPHandler()
{

}

/*!
 * \brief IPHandler::~IPHandler
 */
IPHandler::~IPHandler()
{

}

/*!
 * \brief IPHandler::processCommand
 * \param cmd
 */
void IPHandler::processCommand(QJsonArray cmd)
{
    qDebug() << "IP::processCmd - " << QString(QJsonDocument(cmd).toJson() );
}
