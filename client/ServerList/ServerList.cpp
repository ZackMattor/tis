#include "ServerList.h"
#include <QDebug>

using namespace std;

ServerList::ServerList(ALLEGRO_FONT *ServerListFont)
{
    qDebug() << "Refreshing list";
    m_backPushed = false;
    m_serverListFont = ServerListFont;

    m_buttonBack = new AllegroButton(100, 500, 40, 95, m_serverListFont, al_map_rgb(0,0,0), al_map_rgb(40,40,40), "Back" );
    m_buttonRefresh = new AllegroButton(250, 500, 40, 230, m_serverListFont, al_map_rgb(0,0,0), al_map_rgb(40,40,40), "Refresh List" );
}

ServerList::~ServerList()
{
	qDeleteAll(m_serverInfo);
	qDeleteAll(m_buttons);

	delete m_buttonBack;
	delete m_buttonRefresh;
}

void ServerList::AddServer(QString id, QString serverName, int maxPlayers, int connectedPlayers, QString ipAddr, int port)
{
    ServerInfo *sInfo = new ServerInfo();

    sInfo->id = id;
    sInfo->serverName = serverName;
    sInfo->maxPlayers = maxPlayers;
    sInfo->connectedPlayers = connectedPlayers;
    sInfo->ipAddr = ipAddr;
    sInfo->port = port;

    QString buttonName = (sInfo->serverName + " (" + QString::number(sInfo->connectedPlayers) + "/" + QString::number(sInfo->maxPlayers) + ")");
    AllegroButton *newButton = new AllegroButton(100, 30+(50*m_buttons.count()), 40, 600, m_serverListFont, al_map_rgb(0,0,0), al_map_rgb(40,40,40), buttonName );
    m_serverInfo << sInfo;
    m_buttons << newButton;
}

ServerInfo* ServerList::Update(ALLEGRO_MOUSE_EVENT *mouse)
{
    int count = 0;
    foreach(AllegroButton *but, m_buttons)
    {
        if(but->Update(mouse))
        {
            return m_serverInfo[count];
        }
        count++;
    }

    if(m_buttonBack->Update(mouse))
    {
        m_backPushed = true;
    }

    if(m_buttonRefresh->Update(mouse))
    {
        RefreshList();
    }

    return 0;
}

void ServerList::Draw()
{
    foreach(AllegroButton *but, m_buttons)
    {
        but->Draw();
    }

    m_buttonBack->Draw();
    m_buttonRefresh->Draw();
}

bool ServerList::RefreshList()
{
    ClearList();
    qDebug() << "Refreshing list";
    WebServices webService;
    QList <ServerInfo> RetrievedData = webService.GetServerData();

    foreach(ServerInfo info, RetrievedData)
    {
        AddServer(info.id, info.serverName, info.maxPlayers, info.connectedPlayers, info.ipAddr, info.port);
    }

    return true;
}

bool ServerList::BackPushed()
{
    return m_backPushed;
}

void ServerList::ClearList()
{
	qDeleteAll(m_serverInfo);
	qDeleteAll(m_buttons);
    m_serverInfo.clear();
    m_buttons.clear();
}
