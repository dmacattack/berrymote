#include "berrymotemain.hpp"
#include <QDebug>

// anonymous namespace
namespace
{
    const char* QML_OBJ_SUPERBTNGRID = "gridSuperButtons";
    const char* QML_OBJ_SUPERBTN     = "superButton";

    enum eBTN_IDS
    {
        eBTN_TBD,
        eBTN_SUPER_BUTTON_OFFSET = 100
    };
}

// ctor
BerrymoteMain::BerrymoteMain(QObject *pRootObj)
: mpRootObj(pRootObj)
, mpSuperButtonGrid(NULL)
{
    for (int i = 0; i< BERRYMOTE::MAX_SUPER_BUTTONS; i++)
    {
        mpSuperButtons[i] = NULL;
    }
}

// dtor
BerrymoteMain::~BerrymoteMain()
{
    if (mpSuperButtonGrid)
    {
        delete mpSuperButtonGrid;
    }

    for (int i = 0; i< BERRYMOTE::MAX_SUPER_BUTTONS; i++)
    {
        if (mpSuperButtons[i])
        {
            delete mpSuperButtons[i];
        }
    }
}

// init
void BerrymoteMain::init()
{
    // allocate the qml objects
    mpSuperButtonGrid = new QmlGenericObject(QML_OBJ_SUPERBTNGRID, mpRootObj);

    // allocate the buttons in the grid and assign button ids
    if (mpSuperButtonGrid != NULL)
    {
        int sz = mpSuperButtonGrid->getQmlObj()->children().size();

        for (int i = 0; i< sz; i++)
        {
            // the buttons are added by their ID. So for debugging the id provides
            // a string since the qml isn't discovered by name
            QObject *pObj = mpSuperButtonGrid->getQmlObj()->children().at(i);
            int btnId = eBTN_SUPER_BUTTON_OFFSET + i;
            mpSuperButtons[i] = new QmlGenericObject(QML_OBJ_SUPERBTN, btnId, pObj);
            mpSuperButtons[i]->setId(btnId);
        }
    }

    // connect signals/slots
    QObject::connect( mpRootObj, SIGNAL(buttonClick(int)), this, SLOT(onButtonClick(int)) );

}

// slot callback for button click
void BerrymoteMain::onButtonClick(int btnID)
{
    qDebug() << "clicked button ID:" << btnID;
}
