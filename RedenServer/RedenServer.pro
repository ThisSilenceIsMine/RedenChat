QT += network sql

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/include

SOURCES += \
        main.cpp \
        src/dbfacade.cpp \
        src/server.cpp
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../RedenNetworkLib/release/ -lRedenNetworkLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../RedenNetworkLib/debug/ -lRedenNetworkLib
else:unix: LIBS += -L$$OUT_PWD/../RedenNetworkLib/ -lRedenNetworkLib

INCLUDEPATH += $$PWD/../RedenNetworkLib
DEPENDPATH += $$PWD/../RedenNetworkLib

HEADERS += \
    include/dbfacade.h \
    include/server.h
