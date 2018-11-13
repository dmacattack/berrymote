/*!
 * \file
 * \brief
 * The Config Parser class is responsible for providing startup configurations of the
 * the entire application. The UI and actions are entirely laid out in the config file
 */
#include "configparser.hpp"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "roomdata.hpp"

// anonymous namespace
namespace
{
    const int MAJOR_VER = 1;
    const int MINOR_VER = 0;

    // TODO non-hardcoded path
    const char* CFG_FILE = "./berrymote.json";

    // json data
    const char* JSON_PROP_ROOMS     = "rooms";
    const char* JSON_PROP_VER_MAJOR = "versionMajor";
    const char* JSON_PROP_VER_MINOR = "versionMinor";
}

/*!
 * \brief ConfigParser::ConfigParser
 * ctor of the config parser class
 */
ConfigParser::ConfigParser()
: mpConfigFile (nullptr)
{
}

/*!
 * \brief ConfigParser::~ConfigParser
 * dtor of the configparser class
 */
ConfigParser::~ConfigParser()
{
    if (mpConfigFile)
    {
        delete mpConfigFile;
    }
}

/*!
 * \brief ConfigParser::init
 * Init the config parser by loading the config file and checking its version
 * \returns true if the init process was successful
 */
bool ConfigParser::init()
{
    bool isOk = true;

    if (readConfigFile())
    {
        // verify its version
        if (!verifyConfigVersion())
        {
            isOk = false;
        }
    }
    else
    {
        // couldnt read the config file for some reason
        isOk = false;
    }

    return isOk;
}

/*!
 * \brief ConfigParser::getRooms
 * Populate the rooms from the json file
 * \param 
 */
void ConfigParser::getRooms()
{
    QJsonArray roomArray = mpConfigFile->find(JSON_PROP_ROOMS).value().toArray();

    int sz = roomArray.size();

    for (int i=0; i<sz; i++)
    {
        QJsonObject pObj = roomArray.at(i).toObject();

        RoomData *pData = new RoomData(pObj);
        // debug test
        qDebug() << pData->getString();
    }
}

/*!
 * \brief ConfigParser::readConfigFile
 * \returns true if the config file was read into memory correctly
 */
bool ConfigParser::readConfigFile()
{
    bool isOk = true;

    QFile file(CFG_FILE);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical() << "problem opening cfg file";
        isOk = false;
    }
    else
    {
        // file is open, read in all the data
        QString jData = file.readAll();
        // close the file
        file.close();

        if (jData.isEmpty())
        {
            qCritical() << "config file is empty";
            isOk = false;
        }
        else
        {
            QJsonDocument doc = QJsonDocument::fromJson(jData.toUtf8());
            mpConfigFile = new QJsonObject(doc.object());

            if (mpConfigFile == NULL)
            {
                qCritical() << "unable to parse file to json";
                isOk = false;
            }
        }
    }

    return isOk;
}

/*!
 * \brief ConfigParser::verifyConfigVersion
 * \returns true if the config version matches what is expected
 */
bool ConfigParser::verifyConfigVersion()
{
    bool isOk = false;

    int major = mpConfigFile->find(JSON_PROP_VER_MAJOR).value().toInt(0);
    int minor = mpConfigFile->find(JSON_PROP_VER_MINOR).value().toInt(0);

    qDebug("config version: %d.%d. Expected: %d.%d", major, minor, MAJOR_VER, MINOR_VER);

    if ((major == MAJOR_VER) && (minor == MINOR_VER))
    {
        isOk = true;
    }
    else
    {
        qCritical() << "incorrect version";
    }

    return isOk;
}


