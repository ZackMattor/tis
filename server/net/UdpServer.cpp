#include "UdpServer.h"

#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QUdpSocket>

#include "DefaultSettings.h"
#include "ProtocolGlobals.h"
#include <QDebug>

UdpServer::UdpServer(QObject *parent)
    : QObject(parent)
    , m_socket(new QUdpSocket())
    , m_isRunning(false)
{


    m_localPort = m_settings.value("port", DefaultSettings::localPort()).toUInt();
}

bool UdpServer::isRunning() const
{
    return m_isRunning;
}

void UdpServer::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_socket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        // Size validation
        if (datagram.size() < Packet::MinSize)
            continue;

        Packet packet(datagram);
        // Protocol ID validation
        if (packet.protocolId() != Protocol::CurrentVersion)
            continue;

        // CRC validation
        if (packet.checksum() != 0)
            continue;

        emit packetReceived(packet, sender, senderPort);
    }
}

void UdpServer::socketError(QAbstractSocket::SocketError error)
{
    emit writeToConsole("Socket Error: " + QString::number(error));
}

void UdpServer::sendResponse(Packet packet, const QHostAddress &receiver, quint16 port)
{
    m_socket->writeDatagram(packet.toByteArray(), receiver, port);
}

void UdpServer::runCommand(CommandType type, QStringList args)
{
    switch (type) {
    case BindCommand:
        bind(args);
    case StopCommand:
        stop();
        break;
    case StartCommand:
        start();
    default:
        break;
    }
}

void UdpServer::bind(const QStringList &args)
{
    if (!args.count()) {
        emit writeToConsole("Must provide a port for binding.");
        return;
    }

    bool ok;
    quint16 port = args.first().toUInt(&ok);

    if (ok)
        bind(port);
    else
        emit writeToConsole("Failed to parse port.");
}

void UdpServer::bind(quint16 port)
{
    stop();
    m_isRunning = m_socket->bind(QHostAddress::Any, m_localPort);

    if (m_isRunning) {
        m_localPort = port;
        connect(m_socket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
        connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(socketError(QAbstractSocket::SocketError)));

        QString ip = m_settings.value("serverIP", localIP().toString()).toString();
        emit writeToConsole("Starting server on " + ip + ':' + QString::number(port));
    }
}

void UdpServer::stop()
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

void UdpServer::start()
{
    if (!m_isRunning)
        bind(m_localPort);
}

QHostAddress UdpServer::localIP() const
{
    QList<QHostAddress> hosts = QNetworkInterface::allAddresses();
    hosts.removeAll(QHostAddress(QHostAddress::LocalHost));

    // Remove all IPv6 IPs.
    QList<QHostAddress>::iterator it = hosts.begin();
    while (it != hosts.end()) {
        if ((*it).toString().contains(':'))
            it = hosts.erase(it);
        else
            it++;
    }

    return hosts.first();
}
