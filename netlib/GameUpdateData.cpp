#include "GameUpdateData.h"

#include <QtCore/QDataStream>

GameUpdateData::GameUpdateData(quint64 timestamp)
    : d(new GameUpdateDataData)
{
    d->timestamp = timestamp;
    d->shipCount = 0;
    d->bulletCount = 0;
    d->explosionCount = 0;
}

GameUpdateData::GameUpdateData(const GameUpdateData &rhs)
    : d(rhs.d)
{
}

GameUpdateData &GameUpdateData::operator=(const GameUpdateData &rhs)
{
    if (this != &rhs)
        d.operator=(rhs.d);
    return *this;
}

GameUpdateData::GameUpdateData(const QByteArray &raw)
    : d(new GameUpdateDataData)
{
    setFromRaw(raw);
}

quint64 GameUpdateData::timestamp() const
{
    return d->timestamp;
}

quint16 GameUpdateData::shipCount() const
{
    return d->shipCount;
}

quint16 GameUpdateData::bulletCount() const
{
    return d->bulletCount;
}

quint16 GameUpdateData::explosionCount() const
{
    return d->explosionCount;
}

QVector<NetShip> GameUpdateData::ships() const
{
    return d->ships;
}

QVector<NetBullet> GameUpdateData::bullets() const
{
    return d->bullets;
}

QVector<NetExplosion> GameUpdateData::explosions() const
{
    return d->explosions;
}

QByteArray GameUpdateData::toByteArray() const
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out << d->timestamp;
    out << d->shipCount;
    out << d->bulletCount;
    out << d->explosionCount;

    foreach(const NetShip &ship, d->ships)
    {
        QByteArray shipArray = ship.toByteArray();
        out.writeRawData(shipArray.data(), 27);
    }

    foreach(const NetBullet &bullet, d->bullets)
    {
        QByteArray bulletArray = bullet.toByteArray();
        out.writeRawData(bulletArray.data(), 9);
    }

    foreach(const NetExplosion &explosion, d->explosions)
    {
        QByteArray explosionArray = explosion.toByteArray();
        out.writeRawData(explosionArray.data(), 17);
    }

    return array;
}

void GameUpdateData::setFromRaw(const QByteArray &raw)
{
    QDataStream stream(raw);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    int idx = 0;

    stream.readRawData((char*)&d->timestamp, sizeof(d->timestamp));
    idx +=sizeof(d->timestamp);

    stream.readRawData((char*)&d->shipCount, sizeof(d->shipCount));
    idx +=sizeof(d->shipCount);

    stream.readRawData((char*)&d->bulletCount, sizeof(d->bulletCount));
    idx +=sizeof(d->bulletCount);

    stream.readRawData((char*)&d->explosionCount, sizeof(d->bulletCount));
    idx +=sizeof(d->explosionCount);

    for (int i = 0; i < d->shipCount; i++)
    {
        QByteArray shipArray = raw.mid(idx, 27);
        idx += 27;

        d->ships.append(NetShip(shipArray));
    }

    for (int i = 0; i < d->bulletCount; i++)
    {
        QByteArray bulletArray = raw.mid(idx, 9);
        idx += 9;

        d->bullets.append(NetBullet(bulletArray));
    }

    for (int i = 0; i < d->explosionCount; i++)
    {
        QByteArray explosionArray = raw.mid(idx, 17);
        idx += 17;

        d->explosions.append(NetExplosion(explosionArray));
    }
}

void GameUpdateData::setShips(const QVector<NetShip> &ships)
{
    d->ships = ships;
    d->shipCount = ships.count();
}

void GameUpdateData::setBullets(const QVector<NetBullet> &bullets)
{
    d->bullets = bullets;
    d->bulletCount = bullets.count();
}

void GameUpdateData::setExplosions(const QVector<NetExplosion> &explosions)
{
    d->explosions = explosions;
    d->explosionCount = explosions.count();
}
