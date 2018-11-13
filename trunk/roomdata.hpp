#ifndef ROOMDATA_HPP
#define ROOMDATA_HPP

#include <QJsonObject>
#include <QString>

class RoomData
{
public:
    RoomData(QJsonObject jObj);

    QString getName()    { return mName; }
    QString getIcon()    { return mIcon; }
    int getType()        { return mType; }
    QString getPayload() {return mPayload; }

private:
    void setData(QJsonObject jObj);

private:
    QString mName;
    QString mIcon;
    int mType;
    QString mPayload;
};

#endif // ROOMDATA_HPP
