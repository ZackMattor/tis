#include "Ship.h"

#include "net/Player.h"
#include "BulletPool.h"
#include <QDebug>

#define TURN_SPEED 0.04f // Radians

Ship::Ship(float x, float y, int width, int height)
    : Entity(x, y, width, height)
    , m_player(0)
    , m_health(NormalHealth)
    , m_cooldown(FastCooldown)
        , m_lastShot(0)
{
    setAlive(true);
    setRadius(13);
}

int Ship::health() const
{
    return m_health;
}

QByteArray Ship::name() const
{
    if (m_player)
        return m_player->userName().toLatin1();

    return QByteArray();
}

Player *Ship::player() const
{
    return m_player;
}

Player *Ship::killer() const
{
    return m_killer;
}

void Ship::tick(int width, int height)
{
    m_position += m_velocity;

    if(m_position.X() < 0 || m_position.X() > width)
    {
        m_position -= m_velocity;
        m_velocity.setX(-m_velocity.X());
    }
    if(m_position.Y() < 0 || m_position.Y() > height)
    {
        m_position -= m_velocity;
        m_velocity.setY(-m_velocity.Y());
    }
}

void Ship::damage(int damage, Player *killer)
{
    m_health -= damage;

    if (m_health <= Dead)
    {
        m_killer = killer;
        kill();
    }
}

void Ship::setPlayer(Player *player)
{
    m_player = player;
}

void Ship::setGunCooldown(GunCooldown cooldown)
{
    m_cooldown = cooldown;
}

void Ship::rotateLeft()
{
    rotate(-TURN_SPEED);
}

void Ship::rotateRight()
{
    rotate(TURN_SPEED);
}

void Ship::fireWeapon(quint64 time)
{
    if (m_lastShot + m_cooldown > time)
    {
        return;
    }

    m_lastShot = time;

    BulletPool *pool = BulletPool::singleton();
    Bullet *bullet = &pool->nextFreeBullet();

    // Set bullet position/rotation/velocity
    bullet->setAlive(true);
    bullet->setPlayer(m_player);
    float bulletX = position().X() + qCos(rotation()) * radius()*1.2;
    float bulletY = position().Y() + qSin(rotation()) * radius() *1.2;
    bullet->setDamage(10);
    bullet->setPosition(Vector2D(bulletX, bulletY));
    bullet->setRotation(rotation());
    bullet->setVelocity(velocity() + Vector2D(qCos(rotation()) * 3, qSin(rotation()) *3));
}

void Ship::thrustFoward()
{
    m_velocity += Vector2D(qCos(rotation())*.015, qSin(rotation()) * .015);
}

void Ship::thrustReverse()
{
    m_velocity -= Vector2D(qCos(rotation())*.015, qSin(rotation()) * .015);
}
