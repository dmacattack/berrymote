#include "roomdata.hpp"
#include <QJsonDocument>

// anonymous namespace
namespace
{
    const char* JSON_PROP_NAME          = "name";
    const char* JSON_PROP_SUPER_BUTTONS = "superButtons";
    const char* JSON_PROP_ICON          = "icon";
    const char* JSON_PROP_TYPE          = "type";
    const char* JSON_PROP_CMD           = "cmd";
}

/*!
 * \brief RoomData::RoomData
 * ctor of the Room data container class. init any sub-objects
 * \param jObj - json object from the config file containing 1 room
 */
RoomData::RoomData(QJsonObject jObj)
: mName("")
, mIcon("")
, mSuperButtons(*new ROOM::SuperButtons() )
{
    setData(jObj);
}

/*!
 * \brief RoomData::~RoomData
 * dtor or the Room data class. cleanup and allocated memory
 */
RoomData::~RoomData()
{
    // delete the super buttons
    for (int i = 0, sz = mSuperButtons.size(); i < sz; i++)
    {
        delete &mSuperButtons.at(i);
    }
    delete &mSuperButtons;
}

/*!
 * \brief RoomData::getString
 * \returns a friendly string of this rooms data. its nice for debugging
 */
QString RoomData::getString()
{
    QString str = QString("%1: [%2] \n").arg(mName).arg(mIcon);

    for (int i = 0, sz = mSuperButtons.size(); i < sz; i++)
    {
        QJsonDocument doc(mSuperButtons.at(i).cmd);
        QString cmds = QString(doc.toJson());
        QString superBtn = QString("   name: %1 \n"
                                   "   icon: %2 \n"
                                   "   type: %3 \n"
                                   "   cmd:  %4 \n\n")
                                   .arg(mSuperButtons.at(i).name)
                                   .arg(mSuperButtons.at(i).icon)
                                   .arg(getString(mSuperButtons.at(i).type))
                                   .arg(cmds);
        str.append(superBtn);
    }

    return str;
}

/*!
 * \brief RoomData::setData
 * Set the data of the room from the json object
 * \param jObj - json object from the config file containing 1 room
 */
void RoomData::setData(QJsonObject jObj)
{
    // name of this room
    mName = jObj.find(JSON_PROP_NAME).value().toString();
    // icon for this room
    mIcon = jObj.find(JSON_PROP_ICON).value().toString();

    // super button data
    QJsonArray jSuperButtons = jObj.find(JSON_PROP_SUPER_BUTTONS).value().toArray();

    for (int i = 0, sz = jSuperButtons.size() ; i < sz; i++)
    {
        QJsonObject jBtn     = jSuperButtons.at(i).toObject();
        QString name         = jBtn.find(JSON_PROP_NAME).value().toString();
        QString icon         = jBtn.find(JSON_PROP_ICON).value().toString();
        ROOM::eCMD_TYPE type = getType( jBtn.find(JSON_PROP_TYPE).value().toString() );
        QJsonArray cmds      = jBtn.find(JSON_PROP_CMD).value().toArray();

        ROOM::tSuperButton *pSuperButton = new ROOM::tSuperButton(name, icon, type, cmds);
        mSuperButtons.push_back(*pSuperButton);
    }
}

/*!
 * \brief RoomData::getType
 * \param type - string of the type
 * \returns the enum value of a command type string
 */
ROOM::eCMD_TYPE RoomData::getType(QString type)
{
    return (type == "ir" ? ROOM::eCMD_IR :
           (type == "ip" ? ROOM::eCMD_IP : ROOM::eCMD_UNKNOWN));
}
