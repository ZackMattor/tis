#include "Entity.h"

Entity::Entity(float x, float y, int width, int height)
    : m_isAlive(false)
    , m_width(width)
    , m_height(height)
    , m_rotation(0)
    , m_position(Vector2D(x, y))
    , m_velocity(Vector2D::zero())
{
}

bool Entity::isAlive() const
{
    return m_isAlive;
}

Vector2D Entity::position() const
{
    return m_position;
}

Vector2D Entity::velocity() const
{
    return m_velocity;
}

int Entity::width() const
{
    return m_width;
}

int Entity::height() const
{
    return m_height;
}

float Entity::radius() const
{
    return m_radius;
}

float Entity::rotation() const
{
    return m_rotation;
}

void Entity::kill()
{
    setAlive(false);
}

void Entity::setAlive(bool alive)
{
    m_isAlive = alive;
}

void Entity::setPosition(const Vector2D &pos)
{
    m_position = pos;
}

void Entity::setVelocity(const Vector2D &vel)
{
    m_velocity = vel;
}

void Entity::setWidth(int width)
{
    m_width = width;
}

void Entity::setHeight(int height)
{
    m_height = height;
}

void Entity::setRadius(float radius)
{
    m_radius = radius;
}

void Entity::setRotation(float angle)
{
    m_rotation = angle;
}

void Entity::rotate(float angle)
{
    m_rotation += angle;
}
