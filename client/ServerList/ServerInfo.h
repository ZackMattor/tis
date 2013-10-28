#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QString>

class ServerInfo
{
public:
    ServerInfo();
    QString id;
    QString serverName;
    int maxPlayers;
    int connectedPlayers;
    QString ipAddr;
    int port;
};

#endif // SERVERINFO_H
