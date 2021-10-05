QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 \
          resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baseitem.cpp \
    buildtowericon.cpp \
    bullet.cpp \
    demontower.cpp \
    enemy.cpp \
    eyetower.cpp \
    game.cpp \
    intdisplayicon.cpp \
    intdisplaytext.cpp \
    lifebar.cpp \
    main.cpp \
    road.cpp \
    sounds.cpp \
    swordtower.cpp \
    tower.cpp \
    wave.cpp

HEADERS += \
    baseitem.h \
    buildtowericon.h \
    bullet.h \
    demontower.h \
    enemy.h \
    eyetower.h \
    game.h \
    intdisplayicon.h \
    intdisplaytext.h \
    lifebar.h \
    road.h \
    sounds.h \
    swordtower.h \
    tower.h \
    wave.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

win32:RC_ICONS += icon1.ico
