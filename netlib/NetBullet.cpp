#include "NetBullet.h"

#include <QtCore/QDataStream>

NetBullet::NetBullet(quint16 x, quint16 y, float rotation)
    : NetEntity(BulletType, x, y, rotation)
{
}

NetBullet::NetBullet(const QByteArray &raw)
    : NetEntity(BulletType)
{
    setFromRaw(raw);
}

QByteArray NetBullet::toByteArray() const
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out << m_type;
    out << m_X;
    out << m_Y;
    out << m_rotation;

    return array;
}

void NetBullet::setFromRaw(const QByteArray &raw)
{
    QDataStream stream(raw);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    int idx = 0;

    m_type = raw.at(idx);
    idx += sizeof(m_type);
    stream.skipRawData(1);

    stream.readRawData((char*)&m_X, sizeof(m_X));
    idx +=sizeof(m_X);

    stream.readRawData((char*)&m_Y, sizeof(m_Y));
    idx +=sizeof(m_Y);

    stream.readRawData((char*)&m_rotation, sizeof(m_rotation));
}
