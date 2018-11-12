#ifndef QMLGENERICOBJECT_H
#define QMLGENERICOBJECT_H

#include <QObject>
#include <QString>
#include "qmlobjectbase.hpp"

class QmlGenericObject
: public QmlObjectBase
{
public:
    QmlGenericObject(QString objName, QObject *pParentObj);
    QmlGenericObject(QString objName, int objId, QObject *pObj);
    virtual ~QmlGenericObject() {}

private:
    // Object should have no child QML objects
    // therefore suppress warnings from unused pure virtual functions
    void setChildQmlObject(QObject *pQmlParentObj) { pQmlParentObj = pQmlParentObj; }
    void setChildVisibility(bool visible) { visible = visible; }
};

#endif // QMLGENERICOBJECT_H
