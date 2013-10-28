#include "DefaultSettings.h"

QString DefaultSettings::serverName()
{
    return "Triangles in Space Server";
}

QString DefaultSettings::loginServerUrl()
{
    return "foxx.arksaw.com";
}

int DefaultSettings::maxPlayers()
{
    return 4;
}

bool DefaultSettings::isLocal()
{
    return false;
}

quint16 DefaultSettings::localPort()
{
    return 50000;
}
