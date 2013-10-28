#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QtCore/QHash>
#include <QtCore/QSettings>
#include <QtNetwork/QHostAddress>

#include "console/ConsoleCommands.h"
#include "Packet.h"

class QHostAddress;
class QTimer;

class Database;
class Player;

#define TIMEOUT_MS 15000

class SessionManager : public QObject
{
    Q_OBJECT
public:
    SessionManager(QObject *parent, Database *database);

    Player *playerBySession(const QByteArray &sessionId);
    Player *playerByName(const QString &name);

    void disconnectUser(Player *player, const QString &reason = QString());
    void disconnectUser(const QByteArray &sessionId, const QString &reason = QString());
    void disconnectAll();

private:
    Database *m_database;
    QSettings m_settings;
    QHash<QByteArray, QHostAddress> m_sessionIPHash;
    QList<Player *> m_players;
    QTimer *m_heartbeat;

    Player *authenticateUser(const Packet &packet);
    bool packetIsAuthorized(Packet packet, const QHostAddress &sender) const;
    
signals:
    /*
      Signal: writeToConsole

      Emitted when the game wants to send data about its status to
      the console.
    */
    void writeToConsole(const QString &str);
    void packetValidated(Packet packet);
    void responseReady(Packet packet, const QHostAddress &receiver,quint16);
    void playerConnected(Player *player);
    void playerDisconnected(Player *player);
    
public slots:
    void start();
    void stop();
    void processPacket(Packet packet, const QHostAddress &sender, quint16 port);

    /*
      Function: runCommand

      Executes the given command supplied by the server's local
      console.

      Parameters:

          command - The CommandType to be executed.
          args    - Additional arguments associated with the command.
    */
    void runCommand(CommandType command, QStringList args);
    void sendUpdatePacket(Packet packet);

private slots:
    void checkTimeouts();
    void kickUser(const QStringList &args);
    void printWho();
};

#endif // SESSIONMANAGER_H
