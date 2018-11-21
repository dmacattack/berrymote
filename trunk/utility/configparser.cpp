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

#define DBG_BLOCK 0

// anonymous namespace
namespace
{
    const int MAJOR_VER = 1;
    const int MINOR_VER = 0;

    // TODO non-hardcoded path
    const char* CFG_FILE = "./berrymote.json";

    // json data
    const char* JSON_PROP_ROOMS      = "rooms";
    const char* JSON_PROP_VER_MAJOR  = "versionMajor";
    const char* JSON_PROP_VER_MINOR  = "versionMinor";
    const char* JSON_PROP_SSID       = "wifiSSID";
    const char* JSON_PROP_PASSPHRASE = "wifiPass";
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
 * \param pRooms - pointer to Rooms object to populate
 * \returns true if successful
 */
bool ConfigParser::getRooms(BERRYMOTE::Rooms *pRooms)
{
    bool isOk = false;

    if (pRooms != NULL)
    {
        //pRooms = new ROOM::Rooms();
        QJsonArray roomArray = mpConfigFile->find(JSON_PROP_ROOMS).value().toArray();
        int sz = roomArray.size();

        if (sz > 0)
        {
            isOk = true;

            for (int i=0; i<sz; i++)
            {
                QJsonObject pObj = roomArray.at(i).toObject();

                RoomData *pData = new RoomData(pObj);
                pRooms->push_back(pData);
            }

            // debug test
    #if DBG_BLOCK
            for (int i = 0 ; i< pRooms->size(); i++)
            {
                qDebug () << "----------------------------------------------";
                RoomData *room = pRooms->at(i);
                qDebug("name: %s [%s] ", room->getName().toStdString().c_str(), room->getIcon().toStdString().c_str() );

                ROOM::SuperButtons sbs = room->getSuperButtons();
                for (int j = 0; j< sbs.size(); j++ )
                {
                    ROOM::tSuperButton sb = sbs.at(j);
                    qDebug("   name: %s [%s] type:%d", sb.name.toStdString().c_str(), sb.icon.toStdString().c_str(), sb.type );
                    QJsonDocument doc(sb.cmd);
                    QString cmd = QString(doc.toJson());
                    qDebug("      %s", cmd.toStdString().c_str());
                }
            }
    #endif
        }
    }

    return isOk;
}

/*!
 * \brief ConfigParser::getWifiCreds
 * \param pSSSID - reference to SSID to populate
 * \param pPassphrase - reference to passphrase to populate
 * \returns true if successful
 */
bool ConfigParser::getWifiCreds(QString *pSSSID, QString *pPassphrase)
{
    bool isOk = true;

    *pSSSID      = mpConfigFile->find(JSON_PROP_SSID).value().toString("");
    *pPassphrase = mpConfigFile->find(JSON_PROP_PASSPHRASE).value().toString("");

    if (pSSSID->length() == 0)
    {
        isOk = false;
    }
    return isOk;
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


