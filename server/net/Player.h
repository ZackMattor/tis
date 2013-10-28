#ifndef PLAYER_H
#define PLAYER_H

#include <QtCore/QByteArray>
#include <QtCore/QString>

class Player
{
public:
    Player();

    int userId() const;
    QString userName() const;
    QByteArray sessionId() const;
    quint16 port() const;
    bool receivedHeartbeat() const;
    int timeoutsMissed() const;
    int kills() const;
    int deaths() const;

    void setUserId(int userId);
    void setUserName(const QString &userName);
    void setSessionId(const QByteArray &sessionId);
    void setPort(quint16 port);
    void setReceivedHeartbeat(bool received);
    void addTimeoutMissed();
    void setKills(int kills);
    void addKill();
    void setDeaths(int deaths);
    void addDeath();

private:
    QString m_userName;
    int m_userId;
    QByteArray m_sessionId;
    quint16 m_port;
    bool m_receivedHeartbeat;
    int m_timeoutsMissed;
    int m_kills;
    int m_deaths;
};

#endif // PLAYER_H
