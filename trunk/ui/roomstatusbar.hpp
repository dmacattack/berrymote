#ifndef ROOMSTATUSBAR_H
#define ROOMSTATUSBAR_H

#include "qmlgenericobject.hpp"

class RoomStatusBar
: public QmlGenericObject
{
public:
    RoomStatusBar(QString objectName, QObject *pRootObj);
    ~RoomStatusBar();

    void setTitle(const QString &title);
    void enableWifi(bool isConnected);
    void setBattLevel(int lvl);

private:

};

#endif // ROOMSTATUSBAR_H
