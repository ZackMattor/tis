#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Player;

enum Damage
{
    NormalDamage = 5,
    ExtraDamage = 10,
    MaxDamage = 15
};

class Bullet : public Entity
{
public:
    Bullet();

    int damage() const;
    Player *player() const;

    void tick(int width, int height);
    void setDamage(int damage);
    void setPlayer(Player *player);

private:
    int m_damage;
    Player *m_player;
};

#endif // BULLET_H
