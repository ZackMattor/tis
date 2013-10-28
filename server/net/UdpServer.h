#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QtCore/QSettings>
#include <QtCore/QStringList>
#include <QtNetwork/QHostAddress>

#include "console/ConsoleCommands.h"
#include "Packet.h"

class QUdpSocket;

/*
  Class: UdpServer
  A class for communicating with the network. This class is the
  TiS server's main gateway for communicating with the outside world.
  Packet receiving/dispatch is controlled through this class.
*/
class UdpServer : public QObject
{
    Q_OBJECT
public:
    /*
      Constructor: UdpServer

      Initializes a UdpServer object

      Parameters:

          parent - The UdpServer's parent in the QObject heirarchy.
    */
    explicit UdpServer(QObject *parent = 0);

    bool isRunning() const;

private:
    QSettings m_settings;
    QUdpSocket *m_socket;
    bool m_isRunning;
    quint16 m_localPort;

    QHostAddress localIP() const;

signals:
    void packetReceived(Packet packet, const QHostAddress &sender, quint16 port);

    /*
      Signal: writeToConsole

      Emitted when the game wants to send data about its status to
      the console.
    */
    void writeToConsole(const QString &str);

public slots:
    /*
      Function: runCommand

      Executes the given command supplied by the server's local
      console.

      Parameters:

          command - The CommandType to be executed.
          args    - Additional arguments associated with the command.
    */
    void runCommand(CommandType command, QStringList args);

    void sendResponse(Packet packet, const QHostAddress &receiver, quint16 port);

private slots:
    void readPendingDatagrams();
    void socketError(QAbstractSocket::SocketError error);
    void bind(const QStringList &args);
    void bind(quint16 port);
    void stop();
    void start();
};

#endif // UDPSERVER_H
