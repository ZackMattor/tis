#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QObject>
#include <QtCore/QStringList>

#include "console/ConsoleCommands.h"
#include "Packet.h"

class Database;
class GameEngine;
class SessionManager;

class QHostAddress;

/*
  Class: GameThread
  A class for controlling the game simulation thread.
*/
class GameThread : public QObject
{
    Q_OBJECT
public:
    /*
      Constructor: GameThread

      Initializes a GameThread object

      Parameters:

          parent - The GameThread's parent in the QObject heirarchy.
    */
    GameThread(QObject *parent, Database *database, SessionManager *sessionManager);

private:
    bool m_shouldQuit;
    bool m_stop;

    GameEngine *m_gameEngine;
    SessionManager *m_sessionManager;
    
signals:
    /*
      Signal: writeToConsole

      Emitted when the game wants to send data about its status to
      the console.
    */
    void writeToConsole(const QString &str);

    void updatePacketReady(Packet packet);
    
public slots:
    /*
      Function: runCommand

      Executes the given command supplied by the server's local
      console.

      Parameters:

          command - The CommandType to be executed.
          args    - Additional arguments associated with the command.
    */
    void runCommand(CommandType command, QStringList args);

    /*
      Function: start

      Starts the game's main loop, unless the loop is already running.
    */
    void start();

    /*
      Function: stop

      Stops the game's main loop, unless already stopped.
    */
    void stop();

    /*
      Function: quit

      Stops the game's main loop if still running, then quits the
      QThread's event loop. This quits the whole server.
    */
    void quit();

    void threadSleep(unsigned int ms);

private slots:
    void mainLoop();
};

#endif // GAMETHREAD_H
