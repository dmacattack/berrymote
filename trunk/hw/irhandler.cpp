/*!
 * \file
 * \brief
 * IR Handler class handles sending and receiving IR (infrared) Signals
 */
#include "irhandler.hpp"
#include <QDebug>
#include <QJsonDocument>

/*!
 * \brief IRHandler::IRHandler
 */
IRHandler::IRHandler()
{

}

/*!
 * \brief IRHandler::~IRHandler
 */
IRHandler::~IRHandler()
{

}

/*!
 * \brief IRHandler::processCommand
 * \param cmd
 */
void IRHandler::processCommand(QJsonArray cmd)
{
    qDebug() << "IR::processCmd - " << QString(QJsonDocument(cmd).toJson() );
}
