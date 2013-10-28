#ifndef DEFAULTSETTINGS_H
#define DEFAULTSETTINGS_H

#include <QtCore/QString>

class DefaultSettings
{
public:
    static QString serverName();
    static QString loginServerUrl();
    static int maxPlayers();
    static bool isLocal();
    static quint16 localPort();
};

#endif // DEFAULTSETTINGS_H
