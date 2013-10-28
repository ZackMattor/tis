#include "NetExplosion.h"

#include <QtCore/QDataStream>
#include <QDebug>
NetExplosion::NetExplosion(quint16 x, quint16 y, float rotation, quint64 id)
    : NetEntity(ExplosionType, x, y, rotation)
{
    m_id = id;
}

NetExplosion::NetExplosion(const QByteArray &raw)
    : NetEntity(ExplosionType)
{
    setFromRaw(raw);
}

qint64 NetExplosion::ID()
{
    return m_id;
}

QByteArray NetExplosion::toByteArray() const
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out << m_type;
    out << m_X;
    out << m_Y;
    out << m_rotation;
    out << m_id;

    return array;
}

void NetExplosion::setFromRaw(const QByteArray &raw)
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

    stream.readRawData((char*)&m_id, sizeof(m_id));
    idx += sizeof(m_id);
}
