QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boxbrick.cpp \
    brokenbrick.cpp \
<<<<<<< HEAD
=======
    castle.cpp \
>>>>>>> 5ecb130 (whole scene)
    coin.cpp \
    floorbrick.cpp \
    main.cpp \
    mainwindow.cpp \
    normalbrick.cpp \
<<<<<<< HEAD
    player.cpp \
    score.cpp

HEADERS += \
    boxbrick.h \
=======
    normalbrickwcoin.cpp \
    player.cpp \
    supermushroom.cpp \
    waterpipe.cpp

HEADERS += \
    boxbrick.h \
    castle.h \
>>>>>>> 5ecb130 (whole scene)
    coin.h \
    brokenbrick.h \
    floorbrick.h \
    game.h \
    mainwindow.h \
    normalbrick.h \
<<<<<<< HEAD
    player.h \
    score.h \
    stonebrick.h
=======
    normalbrickwcoin.h \
    player.h \
    stonebrick.h \
    supermushroom.h \
    waterpipe.h
>>>>>>> 5ecb130 (whole scene)

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background_scene_resource.qrc
