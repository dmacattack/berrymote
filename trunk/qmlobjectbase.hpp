#ifndef QMLOBJECTBASE_H
#define QMLOBJECTBASE_H

#include <QObject>

class QmlObjectBase
{
public:
    QmlObjectBase(QString objName);
    virtual ~QmlObjectBase();

    void findQmlObject(QObject *pParentObj);
    void setQmlObj(QObject *pObj);
    virtual void setVisibility(bool visible);
    void setId(int id);

    int getButtonId() { return mButtonId; }
    virtual bool isVisible()  { return mIsVisible; }

    void setProperty(const char* prop, QString value);
    void setProperty(const char* prop, int value);
    void setProperty(const char* prop, double value);
    void setProperty(const char* prop, bool value);
    void setProperty(const char* prop, QVariant value);
    QVariant getProperty(const char* prop);

    bool isValid() { return mIsValid; }
    QObject *getQmlObj() { return mpQmlObj; }

protected:
    // derived class functions to implement
    virtual void setChildQmlObject(QObject *pQmlParentObj)      = 0;
    virtual void setChildVisibility(bool visible)               = 0;

    // optional class functions to implement
    virtual void setQmlSignalsAndSlots() {}

protected:
    void setValid(bool isValid);

    QObject *getParentQmlObject() { return mpQmlObj; }
    QString getParentQmlName()   { return mQmlObjName; }

protected:
    QObject *mpQmlObj;   // pointer to this QML object
    QObject *mpQmlParentObj;   // pointer to the QML objects parent

private:
    QString mQmlObjName; // name of the QML object
    bool mIsValid;       // bool if the QML object is valid
    int mButtonId;       // class allocated button id
    bool mIsVisible;     // bool if this object is visible
};

#endif // QMLOBJECTBASE_H
