#include "Explosion.h"
#include "net/Player.h"
Explosion::Explosion(): Entity(0, 0, 5, 5)
{
    setRadius(3);
    m_id = 0;
}

void Explosion::setID(quint64 timestamp, qint16 num)
{
    m_id = timestamp + num;
    m_timeCreated = timestamp;
}

void Explosion::setPlayer(Player *deadPlayer)
{
    m_player = deadPlayer;
}

quint64 Explosion::ID() const
{
    return m_id;
}

quint64 Explosion::createdAt() const
{
    return m_timeCreated;
}

Player *Explosion::player() const
{
    return m_player;
}

void Explosion::tick(int width, int height)
{
    m_position += m_velocity;

    if(m_position.X() < 0 || m_position.X() > width)
    {
        kill();
    }
    if(m_position.Y() < 0 || m_position.Y() > height)
    {
        kill();
    }
}
