#include "Player.h"

Player::Player()
    : m_port(0)
    , m_receivedHeartbeat(false)
    , m_timeoutsMissed(0)
{
}

int Player::userId() const
{
    return m_userId;
}

QString Player::userName() const
{
    return m_userName;
}

QByteArray Player::sessionId() const
{
    return m_sessionId;
}

quint16 Player::port() const
{
    return m_port;
}

bool Player::receivedHeartbeat() const
{
    return m_receivedHeartbeat;
}

int Player::timeoutsMissed() const
{
    return m_timeoutsMissed;
}

int Player::kills() const
{
    return m_kills;
}

int Player::deaths() const
{
    return m_deaths;
}

void Player::setUserId(int userId)
{
    m_userId = userId;
}

void Player::setUserName(const QString &userName)
{
    m_userName = userName;
}

void Player::setSessionId(const QByteArray &sessionId)
{
    m_sessionId = sessionId;
}

void Player::setPort(quint16 port)
{
    m_port = port;
}

void Player::setReceivedHeartbeat(bool received)
{
    m_receivedHeartbeat = received;
}

void Player::addTimeoutMissed()
{
    m_timeoutsMissed++;
}

void Player::setKills(int kills)
{
    m_kills = kills;
}

void Player::addKill()
{
    m_kills++;
}

void Player::setDeaths(int deaths)
{
    m_deaths = deaths;
}

void Player::addDeath()
{
    m_deaths++;
}
