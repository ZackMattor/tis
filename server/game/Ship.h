#ifndef SHIP_H
#define SHIP_H

#include "Entity.h"
#include <QtCore/qmath.h>
class Player;

enum Health
{
    Dead = 0,
    NormalHealth = 100,
    UpgradedHealth = 120,
    MaxHealth = 150
};

enum GunCooldown
{
    NormalCooldown = 500,
    FastCooldown = 250,
    UltraCooldown = 100
};

class Ship : public Entity
{
public:
    Ship(float x, float y, int width, int height);

    int health() const;
    QByteArray name() const;
    Player *player() const;
    Player *killer() const;

    void tick(int height, int width);
    void damage(int damage, Player *killer);
    void setPlayer(Player *player);
    void setGunCooldown(GunCooldown cooldown);
    void rotateLeft();
    void rotateRight();
    void fireWeapon(quint64 time);
    void thrustFoward();
    void thrustReverse();

private:
    Player *m_player;
    Player *m_killer;

    int m_health;
    GunCooldown m_cooldown;
    quint64 m_lastShot;
};

#endif // SHIP_H
