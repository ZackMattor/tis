#include "Database.h"

#include <QtCore/QVariant>
#include <QtCore/QDateTime>

#include "DefaultSettings.h"
#include "net/Player.h"
#include "Crypto.h"
#include <QDebug>

Database::Database(QObject *parent)
    : QObject(parent)
    , m_isConnected(false)
{
}

Database::~Database()
{
    disestablishServer();

    if (m_database)
        m_database->close();
    delete m_database;
}

bool Database::init()
{
    Driver* driver = get_driver_instance();

    QString loginServerUrl = m_settings.value("loginServerUrl", DefaultSettings::loginServerUrl()).toString();
    QString serverUserName = m_settings.value("serverUserName").toString();
    QString serverPassword = m_settings.value("serverPassword").toString();

    try
    {
        m_database = driver->connect(loginServerUrl.toLatin1().data(),
                                     serverUserName.toLatin1().data(),
                                     serverPassword.toLatin1().data());
        m_database->setSchema("tis");
    }
    catch (SQLException &e)
    {
        emit writeToConsole("DB connect failed: "  + QLatin1String(e.getSQLStateCStr()));
        return false;
    }

    m_isConnected = true;

    return true;
}

bool Database::isConnected() const
{
    return m_isConnected;
}

Player *Database::authenticateUser(const QString &user, const QString &password)
{
    if (!isConnected())
        init();

    if (!m_isConnected)
        return 0;

    Player *player = 0;

    Statement *stmt = 0;
    ResultSet *res = 0;

    stmt = m_database->createStatement();

    try {
        QString qry = QString("SELECT id, username, kills, deaths FROM accounts where username='%1' and secret='%2'").arg(user, password);

        res = stmt->executeQuery(qry.toStdString());

        if (res -> rowsCount() != 0)
        {
            player = new Player();

            while (res->next())
            {
                player->setUserId(res->getInt("id"));
                player->setUserName(QString::fromStdString(res->getString("username")));
                player->setKills(res->getInt("kills"));
                player->setDeaths(res->getInt("deaths"));
            }
        }
    } catch (SQLException &e)
    {
        emit writeToConsole("Query failed: " + QLatin1String(e.getSQLStateCStr()));
        return false;
    }

    delete stmt;
    delete res;

    return player;
}

void Database::establishServer()
{
    if (!isConnected())
        init();

    if (!m_isConnected)
        return;

    if(m_isConnected)
    {
        PreparedStatement *prep_stmt = 0;
        Statement *stmt= 0;
        ResultSet *res = 0;
        QString IP;

        stmt = m_database->createStatement();

        try
        {
            QString qry = QString("SELECT USER( ) AS a");

            res = stmt->executeQuery(qry.toStdString());

            if (res -> rowsCount() != 0)
            {
                while (res->next())
                {
                    IP =  QString(res->getString("a").c_str());
                }
            }

            m_serverID = Crypto::sessionId(IP).toHex();
            prep_stmt = m_database->prepareStatement("INSERT INTO servers(id, serverName, maxPlayers, connectedPlayers, ipAddr) VALUES (?, ?, ?, ?, ?)");

            prep_stmt->setString(1, m_serverID.toStdString());
            prep_stmt->setString(2, m_settings.value("serverName", DefaultSettings::serverName()).toString().toStdString());
            prep_stmt->setInt(3, m_settings.value("maxPlayers", DefaultSettings::maxPlayers()).toInt());
            prep_stmt->setInt(4, 0);
            prep_stmt->setString(5, m_settings.value("serverIP", "127.0.0.1").toString().toStdString());

            prep_stmt->executeUpdate();
        }
        catch (SQLException &e)
        {
            emit writeToConsole("Query failed(establishServer): " + QLatin1String(e.getSQLStateCStr()));
        }

        delete prep_stmt;
        delete stmt;
        delete res;
    }
}

void Database::disestablishServer()
{
    if (!isConnected())
        init();

    if(m_isConnected)
    {
        PreparedStatement *prep_stmt = 0;

        try
        {
            prep_stmt = m_database->prepareStatement("DELETE FROM servers where id = ?");
            prep_stmt->setString(1, m_serverID.toStdString());

            prep_stmt->executeQuery();
        }
        catch (SQLException &e)
        {
            emit writeToConsole("Query failed(disestablishServer): " + QLatin1String(e.getSQLStateCStr()));
        }

        delete prep_stmt;
    }
}

void Database::updatePlayerCount(int count)
{
    if (!isConnected())
        init();

    if (!m_isConnected)
        return;

    PreparedStatement *statement = 0;

    try
    {
        statement = m_database->prepareStatement("UPDATE servers SET connectedPlayers = ? WHERE id = ?");
        statement->setInt(1, count);
        statement->setString(2, m_serverID.toStdString());

        statement->executeQuery();
    }
    catch (SQLException &e)
    {
        emit writeToConsole("Query failed(updatePlayerCount): " + QLatin1String(e.getSQLStateCStr()));
    }

    delete statement;
}

void Database::updatePlayer(Player *player)
{
    if (!isConnected())
        init();

    if (!m_isConnected)
        return;

    PreparedStatement *statement = 0;

    try
    {
        statement = m_database->prepareStatement("UPDATE accounts SET kills = ?, deaths = ? WHERE id = ?");
        statement->setInt(1, player->kills());
        statement->setInt(2, player->deaths());
        statement->setInt(3, player->userId());

        statement->executeQuery();
    }
    catch (SQLException &e)
    {
        emit writeToConsole("Query failed(updatePlayer): " + QLatin1String(e.getSQLStateCStr()));
    }

    delete statement;
}
