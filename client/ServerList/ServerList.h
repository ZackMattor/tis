#ifndef SERVERLIST_H
#define SERVERLIST_H

#include <QList>
#include <QString>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "DisplayGlobals.h"
#include "Elements/allegrobutton.h"
#include "ServerList/ServerInfo.h"
#include "WebServices/WebServices.h"

class ServerList
{
private:
    QList <AllegroButton*>m_buttons;
    QList <ServerInfo*>m_serverInfo;

    AllegroButton *m_buttonBack;
    AllegroButton *m_buttonRefresh;

    ALLEGRO_FONT *m_serverListFont;
    bool m_backPushed;
    void ClearList();

public:
    ServerList(ALLEGRO_FONT *ServerListFont);
	~ServerList();

    void AddServer(QString id, QString serverName, int maxPlayers, int connectedPlayers, QString ipAddr, int port);
    ServerInfo* Update(ALLEGRO_MOUSE_EVENT *mouse);
    void Draw();
    bool RefreshList();
    bool BackPushed();
};

#endif // SERVERLIST_H
