#ifndef HARDKEYHANDLER_HPP
#define HARDKEYHANDLER_HPP

#include <QObject>

namespace KEYS
{
    enum eKEYS
    {
        eKEY_UP,
        eKEY_DN,
        eKEY_LEFT,
        eKEY_RIGHT,
        eKEY_BTN_GENA,
        eKEY_BTN_GENB,
        eKEY_BTN_GENC,
        eKEY_NUM_KEYS
    };
}

class HardKeyHandler
: public QObject
{
    Q_OBJECT
public:
    HardKeyHandler();
    ~HardKeyHandler();

    void init();

signals:
    void hardKeyPressed(KEYS::eKEYS key);

};

#endif // HARDKEYHANDLER_HPP
