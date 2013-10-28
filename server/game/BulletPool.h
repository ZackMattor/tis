#ifndef BULLETPOOL_H
#define BULLETPOOL_H

#include <QtCore/QVector>

#include "Bullet.h"

#define MAX_BULLETS 1024

class BulletPool
{
public:
    BulletPool();
    static BulletPool* singleton();

    Bullet &nextFreeBullet();
    QVector<Bullet *> activeBullets();

    void reset();

private:
    QVector<Bullet> m_bullets;
    int m_bulletIndex;
};

#endif // BULLETPOOL_H
