#ifndef DATABASE_H
#define DATABASE_H

// Qt headers
#include <QtCore/QSettings>

//MySQL C++ Connector 1.1 headers
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

using namespace sql;

class Player;

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    ~Database();

    bool isConnected() const;
    Player *authenticateUser(const QString& user, const QString& password);
    void establishServer();
    void disestablishServer();
    void updatePlayerCount(int count);

private:
    Connection *m_database;
    bool m_isConnected;
    QString m_serverID;
    QSettings m_settings;
    
signals:
    /*
      Signal: writeToConsole

      Emitted when the game wants to send data about its status to
      the console.
    */
    void writeToConsole(const QString &str);
    
public slots:
    bool init();
    void updatePlayer(Player *player);
};

#endif // DATABASE_H
