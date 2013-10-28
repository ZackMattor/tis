#include "WebServices.h"

#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QXmlStreamReader>

WebServices::WebServices()
{
}

QList<ServerInfo> WebServices::GetServerData()
{
    QList<ServerInfo> serverListInfo;
    m_webStream.downloadFile(QUrl("http://foxx.arksaw.com/tis/website/WebService/GetServerlist.php"));

    while(!m_webStream.resultData().size()){ QCoreApplication::processEvents(); }

    QXmlStreamReader xml(m_webStream.resultData());

    ServerInfo newServer;
    QString currentElement;
    while(!xml.atEnd())
    {
        int type = xml.readNext();

        if(type == QXmlStreamReader::StartElement)
        {
            currentElement = xml.name().toString();

            if(xml.name().toString() == "server")
            {
                newServer = ServerInfo();
            }
        }

        if(type == QXmlStreamReader::Characters)
        {
            if(currentElement == "id")
            {
                newServer.id = xml.text().toString();
            }
            if(currentElement == "serverName")
            {
                newServer.serverName = xml.text().toString();
            }
            if(currentElement == "maxPlayers")
            {
                newServer.maxPlayers = xml.text().toString().toInt();
            }
            if(currentElement == "connectedPlayers")
            {
                newServer.connectedPlayers = xml.text().toString().toInt();
            }
            if(currentElement == "ipAddr")
            {
                newServer.ipAddr = xml.text().toString();
            }
            if(currentElement == "port")
            {
                newServer.port = xml.text().toString().toInt();
            }
        }


        if(type == QXmlStreamReader::EndElement)
        {
            if(xml.name().toString() == "server")
            {
                serverListInfo << newServer;
            }
        }

    }

    if(xml.hasError())
    {
        qDebug() << "We have an error!";
    }

    m_webStream.clearResult();

    return serverListInfo;
}
