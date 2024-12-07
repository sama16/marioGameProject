QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Coin.cpp \
    Enemy.cpp \
    GameScene.cpp \
    GameWindow.cpp \
    Player.cpp \
    WelcomeWindow.cpp \
    bullet.cpp \
    fallingRock.cpp \
    main.cpp \
    store.cpp \
    weapon.cpp

HEADERS += \
    Coin.h \
    Enemy.h \
    GameScene.h \
    GameWindow.h \
    Player.h \
    WelcomeWindow.h \
    bullet.h \
    fallingRock.h \
    store.h \
    weapon.h

FORMS += \
    GameWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    mario.png
