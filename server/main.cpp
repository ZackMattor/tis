#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QThread>
#include <QtCore/QTimer>

#include "console/Console.h"
#include "db/Database.h"
#include "game/GameThread.h"
#include "net/SessionManager.h"
#include "net/UdpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setOrganizationName("arksaw");
    app.setApplicationName("tisserver");

    // Initialize settings stuff
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings settings;
    settings.setValue("port", 50000);
    settings.sync();

    Console console;
    Database database;
    SessionManager sessionManager(0, &database);
    GameThread game(0, &database, &sessionManager);
    UdpServer udpServer;

    qRegisterMetaType<Packet>("Packet");
    qRegisterMetaType<QHostAddress>("QHostAddress");
    // Console signals/slots
    QObject::connect(&console, SIGNAL(commandEntered(CommandType,QStringList)),
                     &sessionManager, SLOT(runCommand(CommandType,QStringList)));
    QObject::connect(&console, SIGNAL(commandEntered(CommandType,QStringList)),
                     &game, SLOT(runCommand(CommandType,QStringList)),
                     Qt::DirectConnection); // Need direct connection from cross-thread signals to blocked thread
    QObject::connect(&console, SIGNAL(commandEntered(CommandType,QStringList)),
                     &udpServer, SLOT(runCommand(CommandType,QStringList)));

    // Database signals/slots
    QObject::connect(&database, SIGNAL(writeToConsole(QString)),
                     &console, SLOT(writeLine(QString)),
                     Qt::QueuedConnection);

    // SessionManager signals/slots
    QObject::connect(&sessionManager, SIGNAL(writeToConsole(QString)),
                     &console, SLOT(writeLine(QString)));
    QObject::connect(&sessionManager, SIGNAL(responseReady(Packet,QHostAddress,quint16)),
                     &udpServer, SLOT(sendResponse(Packet,QHostAddress,quint16)), Qt::QueuedConnection);

    // GameThread signals/slots
    QObject::connect(&game, SIGNAL(writeToConsole(QString)),
                     &console, SLOT(writeLine(QString)));
    QObject::connect(&game, SIGNAL(updatePacketReady(Packet)),
                     &sessionManager, SLOT(sendUpdatePacket(Packet)),
                     Qt::QueuedConnection);

    // UdpServer signals/slots
    QObject::connect(&udpServer, SIGNAL(writeToConsole(QString)),
                     &console, SLOT(writeLine(QString)));
    QObject::connect(&udpServer, SIGNAL(packetReceived(Packet,QHostAddress,quint16)),
                     &sessionManager, SLOT(processPacket(Packet,QHostAddress,quint16)),
                     Qt::DirectConnection);

    // Set up threading.
    QThread thread;
    game.moveToThread(&thread);
    thread.start();
    thread.connect(&thread, SIGNAL(finished()), &app, SLOT(quit()));

    // Invoke with Qt::QueuedConnection since the Qt event loop isn't up yet
    QMetaObject::invokeMethod(&database, "init", Qt::QueuedConnection);
    QMetaObject::invokeMethod(&sessionManager, "start", Qt::QueuedConnection);
    QMetaObject::invokeMethod(&game, "start", Qt::QueuedConnection);
    QMetaObject::invokeMethod(&udpServer, "start", Qt::QueuedConnection);

    // Run the primary thread's main event loop.
    // exec() will return when we stop the main event loop via a signal
    return app.exec();
}
