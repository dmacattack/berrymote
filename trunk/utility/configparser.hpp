#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <QJsonObject>
#include "roomdata.hpp"

namespace ROOM
{
    typedef QVector<RoomData*> Rooms;
}

class ConfigParser
{
public:
    ConfigParser();
    ~ConfigParser();

    bool init();
    bool getRooms(ROOM::Rooms *pRooms);
    bool getWifiCreds(QString *pSSSID, QString *pPassphrase);

private:
    bool readConfigFile();
    bool verifyConfigVersion();

private:
    QJsonObject *mpConfigFile;
};

#endif // CONFIGPARSER_H
