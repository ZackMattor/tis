#include "UdpClient.h"

#include <QtCore/QTimer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QUdpSocket>
#include <QDebug>

#include "ProtocolGlobals.h"

UdpClient::UdpClient(QObject *parent)
    : QObject(parent)
    , m_localPort(50004)
    , m_remotePort(50000)
{
    m_sessionID.resize(Packet::SessionIDSize);
    m_sessionID.fill('\0');
}

bool UdpClient::isRunning() const
{
    return m_isRunning;
}

QList<Packet> UdpClient::receivedPackets()
{
    QMutexLocker locker(&m_mutex);
    return m_inPackets;
}

QByteArray UdpClient::sessionID() const
{
    return m_sessionID;
}

void UdpClient::setServer(const QString &serverIP, quint16 port)
{
    m_server = serverIP;
    m_remotePort = port;
}

void UdpClient::init()
{
    m_socket = new QUdpSocket(this);
    bind();
    m_heartbeat = new QTimer(this);
    connect(m_heartbeat, SIGNAL(timeout()), this, SLOT(heartbeatTimeout()));
    m_heartbeat->start();
}

void UdpClient::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_socket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        // Size validation
        if (datagram.size() < Packet::MinSize) {
            continue;
        }

        // Sender validation
        if (sender != QHostAddress(m_server))
            continue;

        Packet packet(datagram);

        // Protocol ID validation
        if (packet.protocolId() != Protocol::CurrentVersion)
            continue;

        // CRC validation
        if (packet.checksum() != 0)
            continue;

        if (packet.commandId() == Protocol::PlayerConnectResponse)
            authReceived(packet);
        else if (packet.commandId() == Protocol::PlayerDisconnected)
        {
            m_sessionID.clear();
            m_heartbeat->stop();
        }

        m_mutex.lock();
        m_inPackets.append(packet);
        m_mutex.unlock();
    }
}

void UdpClient::socketError(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket Error:" << (int)error;
}

void UdpClient::heartbeatTimeout()
{
    if (!m_isRunning)
        return;

    Packet packet;

    packet.setCommandId(Protocol::PlayerHeartbeat);
    QByteArray args;
    args.resize(1);
    args.fill(0);
    packet.setArgs(args);

    sendPacket(packet);
}

void UdpClient::bind()
{
    stop();
    // Listen for packets
    m_isRunning = m_socket->bind(QHostAddress::Any, m_localPort);

    if (m_isRunning) {
        connect(m_socket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()),
                Qt::DirectConnection);
        connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(socketError(QAbstractSocket::SocketError)),
                Qt::DirectConnection);
        qDebug() << "Connecting to server at " + m_server + ':' + QString::number(m_remotePort);
    }
}

void UdpClient::stop()
{
    if (m_isRunning) {
        disconnect(m_socket, SIGNAL(readyRead()),
                   this, SLOT(readPendingDatagrams()));
        disconnect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
                   this, SLOT(socketError(QAbstractSocket::SocketError)));
    }

    m_socket->close();
    m_isRunning = false;
}

void UdpClient::clearReceivedPackets()
{
    QMutexLocker locker(&m_mutex);
    m_inPackets.clear();
}

void UdpClient::sendPacket(Packet &packet)
{
    QMetaObject::invokeMethod(m_heartbeat, "start", Q_ARG(int, TIMEOUT_MS));
    packet.setSessionId(m_sessionID);
    packet.calculateChecksum();
    m_socket->writeDatagram(packet.toByteArray(), QHostAddress(m_server), m_remotePort);
}

void UdpClient::authReceived(Packet packet)
{
    QByteArray responseArgs = packet.args();
    int res = Protocol::InvalidCode;

    if (responseArgs.size() > 0)
    {
        res = responseArgs.at(0);
    }

    if (res == Protocol::Successful)
    {
        m_sessionID = responseArgs.mid(1, responseArgs.length());
        qDebug() << "successfully logged in" << m_sessionID.toHex();
        m_heartbeat->start(TIMEOUT_MS);
    }
}
