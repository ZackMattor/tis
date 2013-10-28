#include "NetShip.h"

#include <QtCore/QDataStream>
#include <QDebug>


NetShip::NetShip(quint16 x, quint16 y, float rotation, quint16 health, const QByteArray &name)
    : NetEntity(ShipType, x, y, rotation)
    , m_health(health)
    , m_name(name)
{
    m_name.resize(16);
}

NetShip::NetShip(const QByteArray &raw)
    : NetEntity(ShipType)
{
    setFromRaw(raw);
}

quint16 NetShip::health() const
{
    return m_health;
}

QByteArray NetShip::name() const
{
    return m_name;
}

QByteArray NetShip::toByteArray() const
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out << m_type;
    out << m_X;
    out << m_Y;
    out << m_rotation;
    out << m_health;
    out.writeRawData(m_name.data(), 16);

    return array;
}

void NetShip::setFromRaw(const QByteArray &raw)
{
    QDataStream stream(raw);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    int idx = 0;

    m_type = raw.at(idx);
    idx += sizeof(m_type);
    stream.skipRawData(1);

    stream.readRawData((char*)&m_X, sizeof(m_X));
    idx += sizeof(m_X);

    stream.readRawData((char*)&m_Y, sizeof(m_Y));
    idx += sizeof(m_Y);

    stream.readRawData((char*)&m_rotation, sizeof(m_rotation));
    idx += sizeof(m_rotation);

    stream.readRawData((char*)&m_health, sizeof(m_health));
    idx += sizeof(m_health);

    m_name = raw.mid(idx, 16);
}
