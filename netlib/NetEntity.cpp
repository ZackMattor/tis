#include "NetEntity.h"

NetEntity::NetEntity(EntityType type, quint16 x, quint16 y, float rotation)
    : m_type(type)
    , m_X(x)
    , m_Y(y)
    , m_rotation(rotation)
{
}

quint8 NetEntity::type() const
{
    return m_type;
}

quint16 NetEntity::X() const
{
    return m_X;
}

quint16 NetEntity::Y() const
{
    return m_Y;
}

float NetEntity::rotation() const
{
    return m_rotation;
}
