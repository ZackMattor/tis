#ifndef NETSHIP_H
#define NETSHIP_H

#include "NetEntity.h"

#include "tisnetlib_global.h"

class TISNETLIB_EXPORT NetShip : public NetEntity
{
public:
    NetShip(quint16 x = 0, quint16 y = 0, float rotation = 0, quint16 health = 0, const QByteArray &name = QByteArray());
    NetShip(const QByteArray &raw);

    quint16 health() const;
    QByteArray name() const;

    QByteArray toByteArray() const;
    void setFromRaw(const QByteArray &raw);

private:
    quint16 m_health;
    QByteArray m_name;
};

#endif // NETSHIP_H
