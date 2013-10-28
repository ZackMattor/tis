#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QtCore/QMutex>
#include <QtCore/QStringList>
#include <QtNetwork/QAbstractSocket>

#include "Packet.h"

class QTimer;

#define TIMEOUT_MS 5000

class QUdpSocket;

class UdpClient : public QObject
{
    Q_OBJECT
public:
    explicit UdpClient(QObject *parent = 0);

    bool isRunning() const;
    QList<Packet> receivedPackets();
    QByteArray sessionID() const;

    void setServer(const QString &serverIP, quint16 port);
    void clearReceivedPackets();
    void disconnectFromServer();
    void sendPacket(Packet &packet);


private:
    QUdpSocket *m_socket;
    QString m_server;
    QByteArray m_sessionID;
    QTimer *m_heartbeat;
    quint16 m_localPort;
    quint16 m_remotePort;
    bool m_isRunning;

    QList<Packet> m_inPackets;
    QMutex m_mutex;

public slots:
    void init();
    void stop();

private slots:
    void readPendingDatagrams();
    void socketError(QAbstractSocket::SocketError error);
    void heartbeatTimeout();
    void bind();
    void authReceived(Packet packet);
};

#endif // UDPCLIENT_H
