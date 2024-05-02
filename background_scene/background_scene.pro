QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boxbrick.cpp \
    brokenbrick.cpp \
    castle.cpp \
    coin.cpp \
    fireflower.cpp \
    floorbrick.cpp \
    health.cpp \
    main.cpp \
    mainwindow.cpp \
    normalbrick.cpp \
    player.cpp \
    score.cpp \
    supermushroom.cpp \
    toxicmushroom.cpp \
    waterpipe.cpp

HEADERS += \
    boxbrick.h \
    castle.h \
    coin.h \
    brokenbrick.h \
    fireflower.h \
    floorbrick.h \
    game.h \
    health.h \
    mainwindow.h \
    normalbrick.h \
    player.h \
    score.h \
    supermushroom.h \
    toxicmushroom.h \
    waterpipe.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background_scene_resource.qrc
