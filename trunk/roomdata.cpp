#include "roomdata.hpp"

RoomData::RoomData(QJsonObject jObj)
{
    setData(jObj);
}

// set the data of the room from the json object
void RoomData::setData(QJsonObject jObj)
{
    mName = jObj.find("name").value().toString();
    mIcon = jObj.find("icon").value().toString();
    QString type = jObj.find("type").value().toString();

    if (type == "ir")
    {
        mType = 0; // TODO implement enum
    }
    else
    {
        mType = 1;
    }

    mPayload = jObj.find("payload").value().toString();
}
