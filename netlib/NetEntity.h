#ifndef NETENTITY_H
#define NETENTITY_H

#include "tisnetlib_global.h"

#include <QtCore/QByteArray>

enum EntityType
{
    InvalidType = 0,
    BulletType,
    ShipType,
    ExplosionType
};

class TISNETLIB_EXPORT NetEntity
{
public:
    NetEntity(EntityType type, quint16 x = 0, quint16 y = 0, float rotation = 0);

    quint8 type() const;
    quint16 X() const;
    quint16 Y() const;
    float rotation() const;

    virtual QByteArray toByteArray() const = 0;
    virtual void setFromRaw(const QByteArray &raw) = 0;

protected:
    quint8 m_type;
    quint16 m_X;
    quint16 m_Y;
    float m_rotation;
};

#endif // NETENTITY_H
