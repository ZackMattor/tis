#include "GameThread.h"

#include <QtCore/QElapsedTimer>
#include <QtCore/QThread>
#include <QtNetwork/QHostAddress>

#include "GameEngine.h"
#include "net/Player.h"
#include "net/SessionManager.h"

#ifndef Q_OS_WIN
#include "unistd.h"
#else
#include "Windows.h"
#endif

GameThread::GameThread(QObject *parent, Database *database, SessionManager *sessionManager)
    : QObject(parent)
    , m_shouldQuit(false)
    , m_stop(true)
    , m_sessionManager(sessionManager)
{
    m_gameEngine = new GameEngine(this, database);

    connect(m_sessionManager, SIGNAL(packetValidated(Packet)),
            m_gameEngine, SLOT(addPacket(Packet)),
            Qt::DirectConnection);
    connect(m_sessionManager, SIGNAL(playerConnected(Player*)),
            m_gameEngine, SLOT(queueAddPlayer(Player*)),
            Qt::DirectConnection);
    connect(m_sessionManager, SIGNAL(playerDisconnected(Player*)),
            m_gameEngine, SLOT(queueRemovePlayer(Player*)),
            Qt::DirectConnection);

    connect(m_gameEngine, SIGNAL(updatePacketReady(Packet)),
            this, SIGNAL(updatePacketReady(Packet)));
}

void GameThread::mainLoop()
{
    m_stop = false;

    m_gameEngine->initialize();

    while (!m_stop)
    {
        QElapsedTimer timer;
        timer.start();

        // Game tick
        m_gameEngine->runTick();

        threadSleep(10 - timer.elapsed());
    }

    if (m_shouldQuit)
        thread()->quit();
}

void GameThread::start()
{
    if (m_stop)
        QMetaObject::invokeMethod(this, "mainLoop", Qt::QueuedConnection);
}

void GameThread::stop()
{
    if (!m_stop)
    {
        m_stop = true;
        m_sessionManager->stop();
        emit writeToConsole("Stopping after current tick");
    }
    else
        emit writeToConsole("Server stopped");
}

void GameThread::quit()
{
    if (m_stop)
        thread()->quit();

    emit writeToConsole("Server going down");
    m_shouldQuit = true;
    stop();
}

void GameThread::threadSleep(unsigned int ms)
{
#ifndef Q_OS_WIN
    usleep(1000 * ms);
#else
    Sleep(ms);
#endif
}

void GameThread::runCommand(CommandType type, QStringList /*args*/)
{
    switch (type) {
    case QuitCommand:
        quit();
        break;
    case StartCommand:
        start();
        break;
    case StopCommand:
        stop();
        break;
    // Values not handled here:
    case HelpCommand:     // Handled in Console
    case AliasesCommand:
    case KickCommand:     // Handled in SessionManager
    case WhoCommand:
    case BindCommand:     // Handled in UdpServer
    case CommandTypeSize: // Dummy value
        break;
    }
}
