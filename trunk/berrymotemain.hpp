#ifndef BERRYMOTEMAIN_H
#define BERRYMOTEMAIN_H

#include <QObject>
#include "qmlgenericobject.hpp"
#include "configparser.hpp"

namespace BERRYMOTE
{
    const int MAX_SUPER_BUTTONS = 6;
}

class BerrymoteMain
: public QObject
{
    Q_OBJECT
public:
    BerrymoteMain(QObject *pRootObj);
    ~BerrymoteMain();

    void init();

private slots:
    void onButtonClick(int btnID);

private:
    QObject *mpRootObj;
    QmlGenericObject *mpSuperButtonGrid;
    QmlGenericObject *mpSuperButtons[BERRYMOTE::MAX_SUPER_BUTTONS];

    ConfigParser &mConfigParser;

};

#endif // BERRYMOTEMAIN_H
