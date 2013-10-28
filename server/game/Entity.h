#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2D.h"

class Entity
{
public:
    Entity(float x, float y, int width, int height);

    bool isAlive() const;
    Vector2D position() const;
    Vector2D velocity() const;
    int width() const;
    int height() const;
    float radius() const;
    float rotation() const;

    // Subclasses must implement tick
    virtual void tick(int height, int width) = 0;
    void kill();
    void setAlive(bool alive);
    void setPosition(const Vector2D &pos);
    void setVelocity(const Vector2D &vel);
    void setWidth(int width);
    void setHeight(int height);
    void setRadius(float radius);
    void setRotation(float angle);
    void rotate(float angle);

private:
    bool m_isAlive;
    int m_width;
    int m_height;
    float m_radius;
    float m_rotation;

protected:
    Vector2D m_position;
    Vector2D m_velocity;
};

#endif // ENTITY_H
