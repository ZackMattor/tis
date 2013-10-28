#include "DownloadManager.h"

#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDebug>

DownloadManager::DownloadManager(QObject *parent)
    : QObject(parent)
    , m_currentJob(0)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::downloadFile(const QUrl &url)
{
    if (m_currentJob)
        return;

    m_currentJob = m_manager->get(QNetworkRequest(url));
}

void DownloadManager::downloadFinished(QNetworkReply *reply)
{
    qDebug() << "Finished!";
    if (reply != m_currentJob || reply->error())
    {
        reply->deleteLater();
        return;
    }

    m_data = reply->readAll();
    reply->deleteLater();
    m_currentJob = 0;
}

QByteArray DownloadManager::resultData() const
{
    return m_data;
}

void DownloadManager::clearResult()
{
    m_data.clear();
}
