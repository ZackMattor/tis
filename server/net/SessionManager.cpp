#include "SessionManager.h"

#include <QtCore/QCryptographicHash>
#include <QtCore/QDateTime>
#include <QtCore/QTimer>

#include "db/Database.h"
#include "DefaultSettings.h"
#include "UdpServer.h"
#include "Player.h"
#include "ProtocolGlobals.h"
#include "Crypto.h"

SessionManager::SessionManager(QObject *parent, Database *database)
    : QObject(parent)
    , m_database(database)
    , m_heartbeat(new QTimer(this))
{
    connect(m_heartbeat, SIGNAL(timeout()), this, SLOT(checkTimeouts()));
}

Player *SessionManager::playerByName(const QString &name)
{
    foreach (Player *player, m_players)
    {
        if (player->userName() == name)
            return player;
    }

    return 0;
}

Player *SessionManager::playerBySession(const QByteArray &sessionId)
{
    foreach (Player *player, m_players)
    {
        if (player->sessionId() == sessionId)
            return player;
    }

    return 0;
}

void SessionManager::start()
{
    m_database->establishServer();
    m_heartbeat->start(TIMEOUT_MS);
}

void SessionManager::stop()
{
    disconnectAll();
    m_heartbeat->stop();
    m_database->disestablishServer();
}

void SessionManager::processPacket(Packet packet, const QHostAddress &sender, quint16 port)
{
    // Handle connection-related packets
    switch (packet.commandId()) {
    case Protocol::PlayerConnect:
    {
        Packet response;
        QByteArray args;

        response.setCommandId(Protocol::PlayerConnectResponse);

        if (m_players.size() == m_settings.value("maxPlayers", DefaultSettings::maxPlayers()))
        {
            args.append(Protocol::ServerFull);
        }
        else
        {
            Player *player = authenticateUser(packet);
            if (player) {
                QByteArray sessionId = Crypto::sessionId(sender.toString());
                m_sessionIPHash[sessionId] = sender;
                player->setSessionId(sessionId);
                player->setPort(port);

                // Response packet args
                args.append(Protocol::Successful);
                args.append(sessionId);

                // Send new player to the game
                m_players.append(player);
                emit playerConnected(player);
                m_database->updatePlayerCount(m_players.size());
            } else {
                args.append(Protocol::LoginFailed);
            }
        }

        response.setArgs(args);
        response.calculateChecksum();

        emit responseReady(response, sender, port);
        return;
    }
    case Protocol::PlayerDisconnect:
    {
        disconnectUser(packet.sessionId(), "Disconnect by User");
        return;
    }
    default:
        break;
    }

    // Validate all other packets
    if (packetIsAuthorized(packet, sender)) {
        // Receiving a packet counts as a heartbeat
        Player *player = playerBySession(packet.sessionId());
        player->setReceivedHeartbeat(true);
        emit packetValidated(packet);
    }
}

void SessionManager::runCommand(CommandType type, QStringList args)
{
    switch (type) {
    case StartCommand:
        start();
        break;
    case StopCommand:
        stop();
        break;
    case KickCommand:
        kickUser(args);
        break;
    case WhoCommand:
        printWho();
        break;
    // Values not handled here:
    case HelpCommand:     // Handled in Console
    case AliasesCommand:
    case BindCommand:     // Handled in UdpServer
    case QuitCommand:     // Handled in GameEngine
    case CommandTypeSize: // Dummy value
        break;
    }
}

void SessionManager::sendUpdatePacket(Packet packet)
{
    // Send update packet to all players
    foreach (Player *player, m_players)
    {
        emit responseReady(packet, m_sessionIPHash[player->sessionId()], player->port());
    }
}

Player *SessionManager::authenticateUser(const Packet &packet)
{
    QByteArray credArray = packet.args();
    QList<QByteArray> credList = credArray.split('\0');

    if (credList.size() < 2)
        return false;

    QString username = credList.first();
    QString password = credList.at(1);
    return m_database->authenticateUser(username, password);
}

void SessionManager::disconnectUser(Player *player, const QString &reason)
{
    disconnectUser(player->sessionId(), reason);
}

void SessionManager::disconnectUser(const QByteArray &sessionId, const QString &reason)
{
    if (!m_sessionIPHash.contains(sessionId))
        return;

    Player *player = playerBySession(sessionId);
    if (!player)
        return;

    Packet dcPacket;
    QHostAddress receiver = m_sessionIPHash.value(sessionId);

    // Populate response packet
    dcPacket.setSessionId(sessionId);
    dcPacket.setCommandId(Protocol::PlayerDisconnected);
    dcPacket.setArgs(reason.toAscii());
    dcPacket.calculateChecksum();

    // Remove session from hash
    m_sessionIPHash.remove(sessionId);
    m_players.removeAll(player);
    m_database->updatePlayerCount(m_players.size());

    emit responseReady(dcPacket, receiver, player->port());
    emit playerDisconnected(player);
}

void SessionManager::disconnectAll()
{
    foreach (Player *player, m_players)
    {
        disconnectUser(player->sessionId(), "Server shutting down");
    }
}

bool SessionManager::packetIsAuthorized(Packet packet, const QHostAddress &sender) const
{
    const QByteArray sessionId = packet.sessionId();
    return m_sessionIPHash.contains(sessionId) &&
           m_sessionIPHash.value(sessionId) == sender;
}

void SessionManager::checkTimeouts()
{
    foreach (Player *player, m_players)
    {
        if (!player->receivedHeartbeat())
            player->addTimeoutMissed();

        // Reset for the next timeout period
        player->setReceivedHeartbeat(false);

        if (player->timeoutsMissed() == 2)
        {
            disconnectUser(player, "Player timed out.");
            emit writeToConsole("Player " + player->userName() + " disconnected. (Timed Out)");
        }
    }
}

void SessionManager::kickUser(const QStringList &args)
{
    if (!args.size())
        return;

    QString playerName = args.first();
    QString reason;

    if (args.size() == 2)
        reason = args.at(1);
    else if (args.size() > 2)
    {
        for (int i = 1; i < args.size(); i++)
        {
            reason.append(args.at(i) + ' ');
        }

        reason = reason.trimmed();
    }

    Player *player = playerByName(playerName);
    if (!player)
    {
        emit writeToConsole("No such player \"" + playerName + "\".");
        return;
    }

    disconnectUser(player->sessionId(), reason);
    emit writeToConsole("Player \"" + playerName + "\" kicked for \"" + reason + '\"');
}

void SessionManager::printWho()
{
    emit writeToConsole("========== Who List ==========");
    foreach (Player *player, m_players)
    {
        QString name = player->userName();
        if (name.size() < 16)
        {
            QString padding;
            padding.fill(' ', 16 - name.size());
            name += padding;
        }
        emit writeToConsole(name + '\t' + m_sessionIPHash[player->sessionId()].toString());
    }
}
