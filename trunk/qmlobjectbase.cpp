/*!
 * \file
 * \brief
 * Base class for all QML objects. Provide the name of the object and QML parent.
 * The QML object discovery is obfuscated, and contains the basic qml visibility
 * property setting
 *
 */
#include "qmlobjectbase.hpp"
#include <QVariant>
#define DBG_BLOCK 0

#if DBG_BLOCK
#include <QDebug>
#endif

namespace
{
    const char* QML_PROP_VISIBLE    = "visible";
    const char* QML_PROP_BUTTON_ID  = "buttonId";
    const int INVALID_BUTTON_ID     = -1;
}

/*!
 * \brief QmlObjectBase::constructor
 * initialize the references and pointers of the class
 */
QmlObjectBase::QmlObjectBase(QString objName)
: mpQmlObj(NULL)
, mpQmlParentObj(NULL)
, mQmlObjName(objName)
, mIsValid(false)
, mButtonId(INVALID_BUTTON_ID)
, mIsVisible(false)
{
}

/*!
 * \brief QmlObjectBase::destructor
 * cleanup of allocated objects
 */
QmlObjectBase::~QmlObjectBase()
{
    mpQmlObj = NULL;
    mpQmlParentObj = NULL;
    mQmlObjName.clear();
    mIsValid = false;
}

/*!
 * \brief QmlObjectBase::findQmlObject
 * Find the qml object from its parent
 */
void QmlObjectBase::findQmlObject(QObject *pParentObj)
{
    mpQmlParentObj = pParentObj;
    mpQmlObj = mpQmlParentObj->findChild<QObject*>(mQmlObjName);

    if (mpQmlObj != NULL)
    {
        mIsValid = true;
        mIsVisible = getProperty(QML_PROP_VISIBLE).toBool();

        setChildQmlObject(mpQmlObj);
        // after the child elements are setup, setup the signals and slots (if applicable)
        setQmlSignalsAndSlots();
    }
    else
    {
#if DBG_BLOCK
        qWarning() << mQmlObjName << " Could not find QML object ";
#endif
    }
}

/*!
 * \brief QmlObjectBase::setQmlObject
 * Manually set the qml object resource
 */
void QmlObjectBase::setQmlObj(QObject *pObj)
{
    mpQmlObj = pObj;

    if (mpQmlObj != NULL)
    {
        mIsValid = true;
        mIsVisible = getProperty(QML_PROP_VISIBLE).toBool();

        setChildQmlObject(mpQmlObj);
        // after the child elements are setup, setup the signals and slots (if applicable)
        setQmlSignalsAndSlots();
    }
    else
    {
#if DBG_BLOCK
        qWarning() << mQmlObjName << " Could not find QML object ";
#endif
    }
}

/*!
 * \brief QmlObjectBase::setVisibility
 * Set the visibility of the qml object
 */
void QmlObjectBase::setVisibility(bool visible)
{
    if (mIsValid)
    {
        mIsVisible = visible;
        // set visibility of the object
        setProperty(QML_PROP_VISIBLE, visible);

        // set the visibility of the sub-objects
        // derived classes must implement this
        setChildVisibility(visible);
    }
    else
    {
#if DBG_BLOCK
        qWarning() << mQmlObjName << " is not valid";
#endif
    }
}

/*!
 * \brief QmlObjectBase::setId
 * Set the qml object's button ID, which can be used for clickcallbacks
 */
void QmlObjectBase::setId(int id)
{
    mButtonId = id;
    if (mIsValid)
    {
        setProperty(QML_PROP_BUTTON_ID, mButtonId);
#if DBG_BLOCK
        qDebug() << mQmlObjName << " set the property button ID to" << mButtonId;
#endif
    }
    else
    {
#if DBG_BLOCK
        qWarning() << mQmlObjName << " is not valid";
#endif
    }
}

/*!
 * \brief QmlObjectBase::setProperty
 * Overloaded function to set a QML object property of the text object
 */
void QmlObjectBase::setProperty(const char* prop, QString value)
{
    setProperty(prop, QVariant(value) );
}

/*!
 * \brief QmlObjectBase::setProperty
 * Overloaded function to set a QML object property of the text object
 */
void QmlObjectBase::setProperty(const char* prop, int value)
{
    setProperty(prop, QVariant(value) );
}

/*!
 * \brief QmlObjectBase::setProperty
 * Overloaded function to set a QML object property of the text object
 */
void QmlObjectBase::setProperty(const char* prop, double value)
{
    setProperty(prop, QVariant(value) );
}

/*!
 * \brief QmlObjectBase::setProperty
 * Overloaded function to set a QML object property of the text object
 */
void QmlObjectBase::setProperty(const char* prop, bool value)
{
    setProperty(prop, QVariant(value) );
}

/*!
 * \brief QmlObjectBase::setProperty
 * set a QML object property of the text object
 */
void QmlObjectBase::setProperty(const char* prop, QVariant value)
{
    mpQmlObj->setProperty(prop, value);
}

/*!
 * \brief QmlObjectBase::getProperty
 * Return a QML object property. Caller must cast to the correct datatype
 */
QVariant QmlObjectBase::getProperty(const char* prop)
{
    return mpQmlObj->property(prop);
}

/*!
 * \brief QmlObjectBase::setValid
 * Set the validity of the object (if the object was found)
 */
void QmlObjectBase::setValid(bool isValid)
{
    mIsValid = isValid;
}
