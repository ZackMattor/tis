#-------------------------------------------------
#
# Project created by QtCreator 2012-04-12T09:16:16
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = tisnetlib
TEMPLATE = lib

DEFINES += TISNETLIB_LIBRARY

SOURCES += Packet.cpp \
           Crypto.cpp \
    NetEntity.cpp \
    NetBullet.cpp \
    NetShip.cpp \
    GameUpdateData.cpp \
    NetExplosion.cpp

HEADERS += Packet.h \
           ProtocolGlobals.h \
           tisnetlib_global.h \
           Crypto.h \
    NetEntity.h \
    NetBullet.h \
    NetShip.h \
    GameUpdateData.h \
    NetExplosion.h

unix:{
    target.path = /usr/lib
    INSTALLS += target
}

win32:{
    target.path += ../libs
}
