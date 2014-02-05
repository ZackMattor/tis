TEMPLATE = app
TARGET = tisclient

QT += core network

INCLUDEPATH += ../netlib/

    #INCLUDEPATH += D:/allegro-5.0
unix {
    CONFIG += console
    LIBS += -L../netlib/ -ltisnetlib -lallegro -lallegro_ttf -lallegro_font -lallegro_primitives -lGluonAudio
    INCLUDEPATH +=/usr/include/AL/
}

win32 {
    CONFIG += windows
    CONFIG += console
    LIBS += ../lib/tisnetlib.lib -L../lib

    #Zack's computer
    LIBS += -LC:/Users/zmattor/Documents/Code/allegro-5.0.6-msvc-10.0/lib/
    INCLUDEPATH += C:/Users/zmattor/Documents/Code/allegro-5.0.6-msvc-10.0/include
    INCLUDEPATH += E:/Docs/Code/Librarys/boost_1_49_0
    INCLUDEPATH += E:/Docs/Code/Librarys/gluontest-build-desktop/debug/openal-soft-src/include/AL
    #INCLUDEPATH += D:/gluon-redist/OpenAL/include/AL
    INCLUDEPATH += E:/Docs/Code/Librarys/gluontest-build-desktop/debug

    #School computers
    #LIBS += -LD:/allegro-5.0.6-msvc-10.0/lib/.6-msvc-10.0/include
    #INCLUDEPATH += D:/mysql-connector-1.1/include
    #INCLUDEPATH += D:/boost/boost_1_49_0
    #INCLUDEPATH += D:/gluon-redist
    #INCLUDEPATH += D:/gluon-redist/OpenAL/include/AL
    #LIBS += -LD:/mysql-connector-1.1/lib/

    LIBS += -lallegro-5.0.6-mt-debug -lallegro_font-5.0.6-mt-debug -lallegro_ttf-5.0.6-mt-debug -lallegro_primitives-5.0.6-mt-debug -lGluonAudio
}

SOURCES += main.cpp \
    player.cpp \
    UdpClient.cpp \
    Menu.cpp \
    Elements/allegrotextbox.cpp \
    Elements/allegrobutton.cpp \
    ServerList/ServerList.cpp \
    ServerList/ServerInfo.cpp \
    Pages/LoginPage.cpp \
    Pages/DisconnectPage.cpp \
    Pages/AboutPage.cpp \
    Game/MainGame.cpp \
    Game/Explosion.cpp \
    Game/Camera2D.cpp \
    SoundPlayer.cpp \
    Game/Minimap.cpp \
    WebServices/DownloadManager.cpp \
    WebServices/WebServices.cpp


HEADERS += \
    player.h \
    UdpClient.h \
    Menu.h \
    DisplayGlobals.h \
    Elements/allegrotextbox.h \
    Elements/allegrobutton.h \
    ServerList/ServerList.h \
    ServerList/ServerInfo.h \
    Pages/LoginPage.h \
    Elements/Account.h \
    Pages/DisconnectPage.h \
    Pages/AboutPage.h \
    Game/MainGame.h \
    Game/Explosion.h \
    Game/Camera2D.h \
    SoundPlayer.h \
    Game/Minimap.h \
    WebServices/DownloadManager.h \
    WebServices/WebServices.h

other_files.files = arial.ttf \
                    TIFAX.ttf \
                    onetrickpony.ogg \
                    repeatnoss.ogg \
                    bitsisisis.ogg \
                    fire.ogg \
                    explode.ogg \
                    rocket.ogg

unix:{
INCLUDEPATH += /home/zmattor/allegro-5.0.6/include
    target.path = /usr/bin
    other_files.path = /usr/share/tis/
    INSTALLS += target
    INSTALLS += other_files
}
