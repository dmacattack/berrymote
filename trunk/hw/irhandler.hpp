#ifndef IRHANDLER_H
#define IRHANDLER_H

#include <QObject>
#include <QJsonArray>

class IRHandler
: public QObject
{
    Q_OBJECT
public:
    IRHandler();
    ~IRHandler();

    void processCommand(QJsonArray cmd);
};

#endif // IRHANDLER_H
