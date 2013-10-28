#include "Packet.h"

#include <QtCore/QDataStream>

#include "ProtocolGlobals.h"

Packet::Packet()
    : m_protocolId(Protocol::VersionOne)
    , m_commandId(0)
    , m_argsSize(0)
    , m_crc(0)
{
    m_sessionId.resize(SessionIDSize);
    m_sessionId.fill(0);

    m_argsSize = 1;
    m_args.resize(1);
    m_args.fill('\0');
}

Packet::Packet(const QByteArray &raw)
{
    m_sessionId.resize(SessionIDSize);
    m_sessionId.fill(0);
    setFromRaw(raw);
}

quint32 Packet::protocolId() const
{
    return m_protocolId;
}

QByteArray Packet::sessionId() const
{
    return m_sessionId;
}

quint8 Packet::commandId() const
{
    return m_commandId;
}

quint16 Packet::argsSize() const
{
    return m_argsSize;
}

QByteArray Packet::args() const
{
    return m_args;
}

quint16 Packet::checksum() const
{
    return m_crc;
}

void Packet::setProtocolId(quint32 protocolId)
{
    m_protocolId = protocolId;
}

void Packet::setSessionId(const QByteArray &sessionId)
{
    if (sessionId.length() > SessionIDSize)
        return;

    m_sessionId = sessionId;
}

void Packet::setCommandId(quint8 commandId)
{
    m_commandId = commandId;
}

void Packet::setArgs(const QByteArray &args)
{
    int length = args.length();
    if (length > MaxArgumentSize || length < MinArgumentSize)
        return;

    m_args = args;
    m_argsSize = length;
}

QByteArray Packet::toByteArray() const
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    out << m_protocolId;
    out.writeRawData(m_sessionId.data(), SessionIDSize);
    out << m_commandId;
    out << m_argsSize;
    out.writeRawData(m_args.data(), m_args.length());
    out << m_crc;

    return array;
}

void Packet::setFromRaw(const QByteArray &raw)
{
    if (raw.length() < MinSize && raw.length() > MaxSize)
        return;

    QDataStream stream(raw);
    stream.setByteOrder(QDataStream::LittleEndian);

    int idx = 0;

    // Protocol ID
    stream.readRawData((char*)&m_protocolId, sizeof(m_protocolId));
    idx += sizeof(m_protocolId);

    // Session ID
    m_sessionId = raw.mid(idx, SessionIDSize);
    stream.skipRawData(SessionIDSize);
    idx += SessionIDSize;

    // Command ID
    m_commandId = raw.at(idx);
    idx += sizeof(m_commandId);
    stream.skipRawData(1);

    // Arguments size
    stream.readRawData((char*)&m_argsSize, sizeof(m_argsSize));
    idx += sizeof(m_argsSize);

    // Arguments
    m_args = raw.mid(idx, m_argsSize);
    idx += m_argsSize;
    stream.skipRawData(m_argsSize);

    // CRC-B (X.25 algorithm)
    quint16 crc;
    stream.readRawData((char*)&crc, sizeof(crc));
    m_crc = 0;
    calculateChecksum();

    if (crc == m_crc)
        m_crc = 0;
}

void Packet::calculateChecksum()
{
    QByteArray tmp = toByteArray();

    m_crc = qChecksum(tmp.data(), tmp.size());
}
