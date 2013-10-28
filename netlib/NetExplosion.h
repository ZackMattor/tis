#ifndef NETEXPLISION_H
#define NETEXPLISION_H

#include "NetEntity.h"

class TISNETLIB_EXPORT NetExplosion : public NetEntity
{
public:
    NetExplosion(quint16 x = 0, quint16 y = 0, float rotation = 0, quint64 id = 0);
    NetExplosion(const QByteArray &raw);

    qint64 ID();

    QByteArray toByteArray() const;
    void setFromRaw(const QByteArray &raw);
private:
    quint64 m_id;
};

#endif // NETEXPLISION_H
