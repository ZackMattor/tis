#ifndef PACKET_H
#define PACKET_H

#include <QtCore/QByteArray>
#include <QtCore/QMetaType>

#include "tisnetlib_global.h"

class TISNETLIB_EXPORT Packet
{
public:
    enum Sizes { // in bytes
        MinSize = 26,
        MaxSize = 8217,
        MinArgumentSize = 1,
        MaxArgumentSize = 8192,
        SessionIDSize = 16
    };

    Packet();
    Packet(const QByteArray &raw);

    quint32 protocolId() const;
    QByteArray sessionId() const;
    quint8 commandId() const;
    quint16 argsSize() const;
    QByteArray args() const;
    quint16 checksum() const;

    void setProtocolId(quint32 protocolId);
    void setSessionId(const QByteArray &sessionId);
    void setCommandId(quint8 commandId);
    void setArgs(const QByteArray &args);
    void calculateChecksum();

    QByteArray toByteArray() const;
    void setFromRaw(const QByteArray &raw);

private:
    quint32 m_protocolId;
    QByteArray m_sessionId;
    quint8 m_commandId;
    quint16 m_argsSize;
    QByteArray m_args;
    quint16 m_crc;
};

Q_DECLARE_METATYPE(Packet)

#endif // PACKET_H
