#ifndef ROOMDATA_HPP
#define ROOMDATA_HPP

#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QString>

namespace ROOM
{
    enum eCMD_TYPE
    {
        eCMD_UNKNOWN,
        eCMD_IR,
        eCMD_IP
    };

    struct tSuperButton
    {
        QString name;
        QString icon;
        ROOM::eCMD_TYPE type;
        QJsonArray cmd;

        // default ctor
        tSuperButton()
        {
            clear();
        }

        // data ctor
        tSuperButton(QString _name, QString _icon, ROOM::eCMD_TYPE _type, QJsonArray _cmd)
        {
            set(_name, _icon, _type, _cmd);
        }

        // clear function
        void clear()
        {
            //set("", "", eCMD_UNKNOWN, QJsonArray());
        }

        // set function
        void set(QString _name, QString _icon, ROOM::eCMD_TYPE _type, QJsonArray _cmd)
        {
            name = _name;
            icon = _icon;
            type = _type;
            cmd = _cmd;
        }
    };

    typedef QVector<tSuperButton> SuperButtons;
}

class RoomData
{
public:
    RoomData(QJsonObject jObj);
    ~RoomData();

    QString getString();
    QString getName() { return mName; }

private:
    void setData(QJsonObject jObj);
    ROOM::eCMD_TYPE getType(QString type);
    QString getString(ROOM::eCMD_TYPE type);

private:
    QString mName;
    ROOM::SuperButtons &mSuperButtons;
};

inline QString RoomData::getString(ROOM::eCMD_TYPE type)
{
    return (type == ROOM::eCMD_IR ? "ir" :
           (type == ROOM::eCMD_IP ? "ip" : "???"));
}

#endif // ROOMDATA_HPP
