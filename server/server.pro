#-------------------------------------------------
#
# Project created by QtCreator 2012-04-05T23:18:20
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = tisserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES *= QT_USE_QSTRINGBUILDER
INCLUDEPATH += ../netlib

win32 {
    CONFIG += debug
    LIBS += -L../lib

    # Zach's config
    INCLUDEPATH += E:/Docs/Code/Librarys/mysql-connector-1.1/include
    INCLUDEPATH += E:/Docs/Code/Librarys/boost_1_49_0
    LIBS += -LE:/Docs/Code/Librarys/mysql-connector-1.1/lib

    # L230 config
    #INCLUDEPATH += D:/mysql-connector-1.1/include
    #INCLUDEPATH += D:/boost/boost_1_49_0
    #LIBS += -LD:/mysql-connector-1.1/lib/
}

LIBS += -L../netlib/ -ltisnetlib -lmysqlcppconn

SOURCES += main.cpp \
    console/Console.cpp \
    game/GameThread.cpp \
    net/Player.cpp \
    net/SessionManager.cpp \
    net/UdpServer.cpp \
    console/ConsoleCommands.cpp \
    console/WinConsole.cpp \
    game/GameEngine.cpp \
    game/Vector2D.cpp \
    db/Database.cpp \
    DefaultSettings.cpp \
    game/Entity.cpp \
    game/Ship.cpp \
    game/Bullet.cpp \
    game/BulletPool.cpp \
    game/Explosion.cpp \
    game/GravityWell.cpp

HEADERS += \
    console/Console.h \
    game/GameThread.h \
    net/Player.h \
    net/SessionManager.h \
    net/UdpServer.h \
    console/ConsoleCommands.h \
    console/WinConsole.h \
    game/GameEngine.h \
    game/Vector2D.h \
    db/Database.h \
    DefaultSettings.h \
    game/Entity.h \
    game/Ship.h \
    game/Bullet.h \
    game/BulletPool.h \
    game/Explosion.h \
    game/GravityWell.h

unix:{
    target.path = /usr/bin
    INSTALLS += target
}
