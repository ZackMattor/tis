#ifndef MAINGAME_H
#define MAINGAME_H

#include <QtCore/qmath.h>
#include <QtCore/QElapsedTimer>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "UdpClient.h"
#include "GameUpdateData.h"
#include "ProtocolGlobals.h"
#include "Elements/Account.h"
#include "Menu.h"
#include "Explosion.h"
#include "Camera2D.h"
#include "Minimap.h"

enum {ROT_LEFT, ROT_RIGHT};

class MainGame
{
public:
    MainGame(ALLEGRO_FONT playerFont, UdpClient *client, ALLEGRO_BITMAP *bg, ALLEGRO_DISPLAY *display);

    bool Update(const GameUpdateData &data, bool keys[255], ALLEGRO_MOUSE_EVENT mouse);
    void Draw();

    ALLEGRO_FONT getPlayerFont();
    void setAccount(Account account);
    GameUpdateData GetGameDate() const;
private:
    void DrawShip(int X, int Y, float rotation, ALLEGRO_COLOR color);
    void DrawBullet(int X, int Y);
    void DrawHealth(int X, int Y, int health, QString name);
    void DrawExplosion(int X, int Y);

    void RotateShip(const qint8 dir);
    void ThrustFoward();
    void ThrustReverse();
    void FireWeapon();
    void Disconnect();
    void StartRocketSound();
    void StopRocketSound();

    ALLEGRO_TRANSFORM m_shipTrans;
    ALLEGRO_BITMAP *m_background;
    ALLEGRO_FONT m_playerFont;

    int m_localX, m_localY;
    bool m_menuOpen;
    int m_fieldHeight, m_fieldWidth;
    quint64 m_lastShot;

    Camera2D m_mainCamera;
    Menu *m_gameMenu;
    Account m_account;
    GameUpdateData m_gameData;
    UdpClient *m_client;
    Minimap *m_miniMap;

    QHash <quint64, Explosion *> m_activeExplosions;
    QElapsedTimer m_timer;
};

#endif // MAINGAME_H
