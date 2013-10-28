#include "BulletPool.h"

#include "qglobal.h"

Q_GLOBAL_STATIC(BulletPool, singletonInstance)

BulletPool *BulletPool::singleton()
{
    return singletonInstance();
}

BulletPool::BulletPool()
    : m_bulletIndex(0)
{
    m_bullets.reserve(MAX_BULLETS);
}

Bullet &BulletPool::nextFreeBullet()
{
    for (int i = 0; i < m_bullets.size(); i++)
    {
        if (!m_bullets.at(i).isAlive())
            return m_bullets[i];
    }

    m_bullets.append(Bullet());
    return m_bullets.back();
}

QVector<Bullet *> BulletPool::activeBullets()
{
    QVector<Bullet *> activeBullets;

    for (int i = 0; i < m_bullets.size(); i++)
    {
        Bullet *bullet = &(m_bullets[i]);
        if (bullet->isAlive())
            activeBullets.append(bullet);
    }

    return activeBullets;
}

void BulletPool::reset()
{
    // Kill all bullets
    Bullet *bullet = 0;
    for (int i = 0; i < m_bullets.size(); i++)
    {
        bullet = &(m_bullets[i]);
        bullet->kill();
    }
}
