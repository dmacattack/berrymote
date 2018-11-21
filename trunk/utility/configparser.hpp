#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <QJsonObject>
#include "berrymotetypes.hpp"

class ConfigParser
{
public:
    ConfigParser();
    ~ConfigParser();

    bool init();
    bool getRooms(BERRYMOTE::Rooms *pRooms);
    bool getWifiCreds(QString *pSSSID, QString *pPassphrase);

private:
    bool readConfigFile();
    bool verifyConfigVersion();

private:
    QJsonObject *mpConfigFile;
};

#endif // CONFIGPARSER_H
