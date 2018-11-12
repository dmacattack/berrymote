/*!
 * \file
 * \brief
 * Object representing a Generic QML objects which provides accessors to
 * its properties
 *
 */
#include "qmlgenericobject.hpp"

/*!
 * \brief QmlGenericObject::constructor
 * initialize subobjects of this object
 */
QmlGenericObject::QmlGenericObject(QString objName, QObject *pParentObj)
: QmlObjectBase(objName)
{
    findQmlObject(pParentObj);
}

/*!
 * \brief QmlGenericObject::constructor
 * initialize subobjects of this object using an objectId and pointer to qml object
 * rather than finding the object by its name
 */
QmlGenericObject::QmlGenericObject(QString objName, int objId, QObject *pObj)
: QmlObjectBase(objName + QString::number(objId))
{
    // the derived classes of this base shall call this ctor with
    // QmlObjectBase("MyObject", id, pObjectPointer)
    setQmlObj(pObj);
}
