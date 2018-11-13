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
}

// ctor
ConfigParser::ConfigParser()
: mpConfigFile (nullptr)
{
}

// dtor
ConfigParser::~ConfigParser()
{

}

// init
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

// test function to parse out the data from the config file
void ConfigParser::getRooms()
{
    QJsonArray roomArray = mpConfigFile->find("rooms").value().toArray();

    QJsonDocument doc(roomArray);

    int sz = roomArray.size();

    for (int i=0; i<sz; i++)
    {
        QJsonObject pObj = roomArray.at(i).toObject();
        RoomData *pData = new RoomData(pObj);
        // debug test
        qDebug() << pData->getName() << pData->getIcon() << pData->getPayload();

        delete pData;
    }


}

// read the config file into the json object
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

// verify the config file version is correct
bool ConfigParser::verifyConfigVersion()
{
    bool isOk = false;

    int major = mpConfigFile->find("versionMajor").value().toInt(0);
    int minor = mpConfigFile->find("versionMinor").value().toInt(0);

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


