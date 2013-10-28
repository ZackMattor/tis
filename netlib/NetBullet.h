#ifndef NETBULLET_H
#define NETBULLET_H

#include "tisnetlib_global.h"

#include "NetEntity.h"

class TISNETLIB_EXPORT NetBullet : public NetEntity
{
public:
    NetBullet(quint16 x = 0, quint16 y = 0, float rotation = 0);
    NetBullet(const QByteArray &raw);

    QByteArray toByteArray() const;
    void setFromRaw(const QByteArray &raw);
};

#endif // NETBULLET_H
