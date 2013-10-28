#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Entity.h"

class Player;

class Explosion : public Entity
{
public:
    Explosion();

    void setID(quint64 timestamp, qint16 num);
    void setPlayer(Player *deadPlayer);

    quint64 ID() const;
    quint64 createdAt() const;
    Player *player() const;

    void tick(int height, int width);
private:
    quint64 m_id;
    quint64 m_timeCreated;
    Player *m_player;
};

#endif // EXPLOSION_H
