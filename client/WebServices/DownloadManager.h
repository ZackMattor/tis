#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QtCore/QByteArray>

class QNetworkAccessManager;
class QNetworkReply;
class QUrl;

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = 0);

    QByteArray resultData() const;

    void downloadFile(const QUrl &url);

    void clearResult();
private:
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_currentJob;

    QByteArray m_data;

private slots:
    void downloadFinished(QNetworkReply *reply);
};

#endif // DOWNLOADMANAGER_H
