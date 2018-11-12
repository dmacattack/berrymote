#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <QJsonObject>

class ConfigParser
{
public:
    ConfigParser();
    ~ConfigParser();

    bool init();


private:
    bool readConfigFile();
    bool verifyConfigVersion();

private:
    QJsonObject *mpConfigFile;
};

#endif // CONFIGPARSER_H
