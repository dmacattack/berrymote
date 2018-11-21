#ifndef IPHANDLER_H
#define IPHANDLER_H

#include <QObject>
#include <QJsonArray>

class IPHandler
: public QObject
{
    Q_OBJECT
public:
    IPHandler();
    ~IPHandler();

    void processCommand(QJsonArray cmd);
};

#endif // IPHANDLER_H
