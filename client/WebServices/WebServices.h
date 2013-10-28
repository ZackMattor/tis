#ifndef WEBSERVICES_H
#define WEBSERVICES_H

#include <QtCore/QUrl>
#include <QList>
#include <QXmlStreamReader>

#include "WebServices/DownloadManager.h"
#include "ServerList/ServerInfo.h"

class WebServices
{
public:
    WebServices();

    QList<ServerInfo> GetServerData();
private:
    DownloadManager m_webStream;
};

#endif // WEBSERVICES_H
