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

// ctor
RoomData::RoomData(QJsonObject jObj)
: mName("")
, mSuperButtons(*new ROOM::SuperButtons() )
{
    setData(jObj);
}

// dtor
RoomData::~RoomData()
{
    // delete the super buttons
    for (int i = 0, sz = mSuperButtons.size(); i < sz; i++)
    {
        delete &mSuperButtons.at(i);
    }
    delete &mSuperButtons;
}

// return a string of this room's data
// its nice for debugging
QString RoomData::getString()
{
    QString str = QString("%1: \n").arg(mName);

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

// set the data of the room from the json object
void RoomData::setData(QJsonObject jObj)
{
    // name of this room
    mName = jObj.find(JSON_PROP_NAME).value().toString();

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

// convert the string to the enum type
ROOM::eCMD_TYPE RoomData::getType(QString type)
{
    return (type == "ir" ? ROOM::eCMD_IR :
           (type == "ip" ? ROOM::eCMD_IP : ROOM::eCMD_UNKNOWN));
}
