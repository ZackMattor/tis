#include "GameEngine.h"

// Netlib includes
#include "net/Player.h"
#include "ProtocolGlobals.h"
#include "GameUpdateData.h"
#include "NetBullet.h"
#include "NetShip.h"
#include "NetExplosion.h"
#include "Vector2D.h"

// Own includes
#include "BulletPool.h"
#include "db/Database.h"
#include "Ship.h"
#include "Explosion.h"

GameEngine::GameEngine(QObject *parent, Database *database)
    : QObject(parent)
    , m_database(database)
{
    m_bulletPool = BulletPool::singleton();
    qsrand(m_timer.elapsed());
    qRegisterMetaType<Player *>("Player *");

    m_screenHeight = 2000;
    m_screenWidth = 2000;
}

void GameEngine::runTick()
{
    // Check for new/old players
    processPlayers();

    // Process packets from players
    processPackets();

    // Process bullet collisions and dead ships
    processShipData();

    // Update entity locations
    foreach (Ship *ship, m_ships)
    {
        ship->tick(m_screenHeight, m_screenWidth);
    }

    foreach (Bullet *bullet, m_bulletPool->activeBullets())
    {
        bullet->tick(m_screenHeight, m_screenWidth);
    }

    foreach (Explosion *explosion, m_explosions) //process the explosions here, if an explosion has expired, spawn ship
    {
        if((explosion->createdAt() + 5000) > m_timer.elapsed()) //We are still exploading
        {
            explosion->tick(m_screenHeight, m_screenWidth);
        }
        else //we are done exploding
        {
            spawnShip(explosion->player());

            m_explosions.remove(m_explosions.indexOf(explosion));
            delete explosion;
        }
    }

    // Send update packet
    sendUpdateData();
}

Player *GameEngine::playerByName(const QString &name)
{
    QMutexLocker locker(&m_playersMutex);

    foreach (Player *player, m_players)
    {
        if (player->userName() == name)
            return player;
    }

    return 0;
}

Player *GameEngine::playerBySession(const QByteArray &sessionId)
{
    QMutexLocker locker(&m_playersMutex);

    foreach (Player *player, m_players)
    {
        if (player->sessionId() == sessionId)
            return player;
    }

    return 0;
}

Ship *GameEngine::shipByPlayer(Player *player)
{
    foreach (Ship *ship, m_ships)
    {
        if (ship->player() == player)
            return ship;
    }

    return 0;
}

void GameEngine::initialize()
{
    qDeleteAll(m_players);
    qDeleteAll(m_ships);
    m_ships.clear();
    m_players.clear();

    m_inPackets.clear();
    m_inPlayers.clear();
    m_outPlayers.clear();
    m_bulletPool->reset();

    m_timer.start();
}

void GameEngine::processPlayers()
{
    m_inPlayersMutex.lock();
    m_playersMutex.lock();
    // Add queued players
    foreach (Player *player, m_inPlayers)
    {
        m_players.append(player);

        spawnShip(player);
    }
    m_inPlayers.clear();
    m_inPlayersMutex.unlock();

    m_outPlayersMutex.lock();

    Ship *ship;

    // Remove queued players
    foreach (Player *player, m_outPlayers)
    {
        m_players.removeAll(player);

        ship = shipByPlayer(player);

        if(ship != 0)
        {
            m_ships.remove(m_ships.indexOf(ship));
            delete ship;
        }

        delete player;
    }
    m_outPlayers.clear();
    m_outPlayersMutex.unlock();
    m_playersMutex.unlock();
}

void GameEngine::processPackets()
{
    QMutexLocker locker(&m_inPacketsMutex);

    Player *player = 0;
    Ship *ship = 0;

    foreach (const Packet &packet, m_inPackets)
    {
        player = playerBySession(packet.sessionId());
        ship = shipByPlayer(player);

        if(ship != 0) // The ship might be null if the player is currently dead
        {
            switch (packet.commandId())
            {
            case Protocol::PlayerRotateLeft:
                ship->rotateLeft();
                break;
            case Protocol::PlayerRotateRight:
                ship->rotateRight();
                break;
            case Protocol::PlayerFireWeapon:
                //qDebug() << player->userName() << ": PlayerFireWeapon";
                ship->fireWeapon(m_timer.elapsed());
                break;
            case Protocol::PlayerThrustFoward:
                ship->thrustFoward();
                break;
            case Protocol::PlayerThrustReverse:
                ship->thrustReverse();
                break;
            // Handled in SessionManager
            case Protocol::PlayerConnect:
            case Protocol::PlayerDisconnect:
            case Protocol::InvalidCommand:
                break;
            }
        }
    }

    m_inPackets.clear();
}

void GameEngine::sendUpdateData()
{
    Packet updatePacket;
    GameUpdateData updateData(m_timer.elapsed());

    QVector<Bullet *> activeBullets = m_bulletPool->activeBullets();
    QVector<NetBullet> netBullets;
    netBullets.reserve(activeBullets.size());

    foreach (Bullet *bullet, activeBullets)
    {
        netBullets.append(NetBullet(bullet->position().X(), bullet->position().Y(), bullet->rotation()));
    }

    updateData.setBullets(netBullets);

    QVector<NetShip> netShips;
    netShips.reserve(m_ships.size());

    foreach (Ship *ship, m_ships)
    {
        netShips.append(NetShip(ship->position().X(), ship->position().Y(), ship->rotation(), ship->health(), ship->name()));
    }

    updateData.setShips(netShips);

    QVector<NetExplosion> netExplosions;
    netExplosions.reserve(m_explosions.size());

    foreach (Explosion *explosion, m_explosions)
    {
        netExplosions.append(NetExplosion(explosion->position().X(), explosion->position().Y(), explosion->rotation(), explosion->ID()));
    }

    updateData.setExplosions(netExplosions);

    updatePacket.setCommandId(Protocol::GameUpdate);
    updatePacket.setArgs(updateData.toByteArray());
    updatePacket.calculateChecksum();

    // Send packets to connected users
    emit updatePacketReady(updatePacket);
}

void GameEngine::processShipData()
{
    QVector<Bullet *> activeBullets = m_bulletPool->activeBullets();

    foreach (Ship *ship, m_ships)
    {

        foreach (Bullet *bullet, activeBullets) //process bullet collisions
        {
            double distance = calculateDistance(ship->position().X(), ship->position().Y(), bullet->position().X(), bullet->position().Y());

            if(distance < ship->radius())
            {
                ship->damage(bullet->damage(), bullet->player());
                bullet->kill();
            }
        }

        if(!ship->isAlive()) //Check if ship is dead
        {
            Player *killer = ship->killer();
            Player *player = ship->player();

            killer->addKill();
            player->addDeath();
            //QMetaObject::invokeMethod(m_database, "updatePlayer", Qt::QueuedConnection, Q_ARG(Player *, killer));
            //QMetaObject::invokeMethod(m_database, "updatePlayer", Qt::QueuedConnection, Q_ARG(Player *, player));

            Explosion *explosion = new Explosion();
            explosion->setPlayer(ship->player());
            explosion->setID(m_timer.elapsed(), m_explosions.size());
            explosion->setVelocity(ship->velocity());
            explosion->setPosition(ship->position());

            m_explosions.append(explosion);

            m_ships.remove(m_ships.indexOf(ship));
            delete ship;
        }
    }
}

void GameEngine::spawnShip(Player *player)
{
    if (!m_players.contains(player))
        return;

    // Set up new ship
    Ship *ship = new Ship(qrand() % m_screenWidth, qrand() % m_screenHeight, 10, 10);
    ship->setPlayer(player);
    m_ships.append(ship);
}

double GameEngine::calculateDistance(int x1, int y1, int x2, int y2)
{
    return (qSqrt(qPow((x2-x1), 2) + qPow((y2-y1), 2)));
}

void GameEngine::addPacket(Packet packet)
{
    QMutexLocker locker(&m_inPacketsMutex);
    m_inPackets.append(packet);
}

void GameEngine::queueAddPlayer(Player *player)
{
    QMutexLocker locker(&m_inPlayersMutex);
    m_inPlayers.append(player);
}

void GameEngine::queueRemovePlayer(Player *player)
{
    QMutexLocker locker(&m_outPlayersMutex);
    m_outPlayers.append(player);
}
