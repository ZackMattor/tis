#include "Bullet.h"

#include "net/Player.h"

Bullet::Bullet()
    : Entity(0, 0, 5, 5)
    , m_player(0)
{
    m_damage = NormalDamage;
    setRadius(3);
}

int Bullet::damage() const
{
    return m_damage;
}

Player *Bullet::player() const
{
    return m_player;
}

void Bullet::tick(int width, int height)
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

void Bullet::setDamage(int damage)
{
    m_damage = damage;
}

void Bullet::setPlayer(Player *player)
{
    m_player = player;
}
