#ifndef GAMEUPDATEDATA_H
#define GAMEUPDATEDATA_H

#include <QtCore/QSharedDataPointer>
#include <QtCore/QVector>

#include "NetBullet.h"
#include "NetShip.h"
#include "NetExplosion.h"

#include "tisnetlib_global.h"

class GameUpdateDataData : public QSharedData {
public:
    quint64 timestamp;
    quint16 shipCount;
    quint16 bulletCount;
    quint16 explosionCount;
    QVector<NetShip> ships;
    QVector<NetBullet> bullets;
    QVector<NetExplosion> explosions;
};

class TISNETLIB_EXPORT GameUpdateData
{
public:
    explicit GameUpdateData(quint64 timestamp);
    GameUpdateData(const GameUpdateData &);
    GameUpdateData &operator=(const GameUpdateData &);
    GameUpdateData(const QByteArray &raw);

    quint64 timestamp() const;
    quint16 shipCount() const;
    quint16 bulletCount() const;
    quint16 explosionCount() const;

    QVector<NetShip> ships() const;
    QVector<NetBullet> bullets() const;
    QVector<NetExplosion> explosions() const;

    QByteArray toByteArray() const;
    void setFromRaw(const QByteArray &raw);

    void setShips(const QVector<NetShip> &ships);
    void setBullets(const QVector<NetBullet> &bullets);
    void setExplosions(const QVector<NetExplosion> &explosions);
private:
    QSharedDataPointer<GameUpdateDataData> d;
};

#endif // GAMEUPDATEDATA_H
