#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QtCore/QElapsedTimer>
#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtCore/qmath.h>

#include <QDebug>

#include "Packet.h"

class Database;
class Player;
class BulletPool;
class Ship;
class Explosion;

/*
  Class: GameEngine
  A class for running all game logic. The main tick of
  the server is implemented here.
*/
class GameEngine : public QObject
{
    Q_OBJECT
public:
    GameEngine(QObject *parent, Database *database);

    /*
      Function: runTick

      Simulates a single tick of the game.
    */
    void runTick();

private:
    QElapsedTimer m_timer;
    Database *m_database;
    QVector<Packet> m_inPackets;
    QMutex m_inPacketsMutex;
    QList<Player *> m_players;
    QMutex m_playersMutex;
    QList<Player *> m_inPlayers;
    QMutex m_inPlayersMutex;
    QList<Player *> m_outPlayers;
    QMutex m_outPlayersMutex;

    int m_screenHeight;
    int m_screenWidth;

    BulletPool *m_bulletPool;
    QVector<Ship *> m_ships;
    QVector<Explosion *> m_explosions;

    Player *playerBySession(const QByteArray &sessionId);
    Player *playerByName(const QString &name);
    Ship *shipByPlayer(Player *player);

    void processPackets();
    void processPlayers();
    void sendUpdateData();
    void processShipData();

    void spawnShip(Player *player);
    double calculateDistance(int x1, int y1, int x2, int y2);
    
signals:
    void updatePacketReady(Packet packet);
    
public slots:
    /*
      Function: addPacket

      Initializes the server for a fresh game. Called when the parenting
      GameThread receives a start command.
    */
    void initialize();

    /*
      Function: addPacket

      Used by the main thread to add an incoming packet for processing
      next tick. This method is thread safe.
    */
    void addPacket(Packet packet);

    void queueAddPlayer(Player *player);
    void queueRemovePlayer(Player *player);
};

#endif // GAMEENGINE_H
