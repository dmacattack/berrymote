TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    ui/berrymotemain.cpp \
    ui/roomdata.cpp \
    utility/configparser.cpp \
    utility/qmlgenericobject.cpp \
    utility/qmlobjectbase.cpp \
    hw/irhandler.cpp \
    hw/iphandler.cpp \
    ui/roomstatusbar.cpp \
    ui/roomdrawer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ui/berrymotemain.hpp \
    ui/roomdata.hpp \
    utility/configparser.hpp \
    utility/qmlgenericobject.hpp \
    utility/qmlobjectbase.hpp \
    hw/irhandler.hpp \
    hw/iphandler.hpp \
    ui/roomstatusbar.hpp \
    ui/roomdrawer.hpp \
    berrymotetypes.hpp

INCLUDEPATH +=$$PWD
INCLUDEPATH +=$$PWD/ui
INCLUDEPATH +=$$PWD/utility

DISTFILES += \
    berrymote.json \
    fonts/fontAwesomev5.5.0.otf \
    utility/berrymote.json
