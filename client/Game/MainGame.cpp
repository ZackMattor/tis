#include "MainGame.h"

#include <gluon/audio/sound.h>

#include "SoundPlayer.h"

extern SoundPlayer *soundPlayer;

MainGame::MainGame(ALLEGRO_FONT playerFont, UdpClient *client, ALLEGRO_BITMAP *bg, ALLEGRO_DISPLAY *display)
    : m_gameData(0), m_menuOpen(false), m_client(client), m_playerFont(playerFont), m_background(bg), m_lastShot(0)
{
    //need to add
    m_fieldHeight = 2000;
    m_fieldWidth = 2000;

    m_gameMenu = new Menu(100, 100, &m_playerFont);

    m_gameMenu->SetSpacing(10);

    m_gameMenu->AddItem("Disconnect From Server", 0);
    m_gameMenu->AddItem("Back to game", 1);

    m_miniMap = new Minimap(m_fieldWidth, m_fieldHeight, 100,100, display);

    soundPlayer->stopAll();
    soundPlayer->setVolume(0.6);
    soundPlayer->playLoop();
    m_timer.start();
}

bool MainGame::Update(const GameUpdateData &data, bool keys[255], ALLEGRO_MOUSE_EVENT mouse)
{
    // Takes a shallow copy that becomes deep when newData goes out of scope
    m_gameData = data;

    if(keys[ALLEGRO_KEY_LEFT] || keys[ALLEGRO_KEY_A])
    {
        RotateShip(ROT_LEFT);
    }
    else if(keys[ALLEGRO_KEY_RIGHT] || keys[ALLEGRO_KEY_D])
    {
        RotateShip(ROT_RIGHT);
    }

    if(keys[ALLEGRO_KEY_UP] || keys[ALLEGRO_KEY_W])
    {
        ThrustFoward();
        StartRocketSound();
    }
    else if(keys[ALLEGRO_KEY_DOWN] || keys[ALLEGRO_KEY_S])
    {
        ThrustReverse();
        StartRocketSound();
    }
    else
        StopRocketSound();

    if (keys[ALLEGRO_KEY_SPACE])
    {
        FireWeapon();
    }

    if (keys[ALLEGRO_KEY_ESCAPE])
    {
        m_menuOpen = true;
    }

    if(m_menuOpen)
    {
        int selectedItem = m_gameMenu->Update(keys, &mouse);

        switch(selectedItem)
        {
        case 0:
            Disconnect();
            return false;
            break;
        case 1:
            m_menuOpen = false;
            break;
        }
    }

    //caculate local entities
    //Check for new explosions to register
    foreach(NetExplosion explosion, m_gameData.explosions())
    {
        if(!m_activeExplosions.contains(explosion.ID()))
        {
            //soundPlayer->playSound("explode");
            m_activeExplosions[explosion.ID()] = new Explosion(explosion.X(), explosion.Y(), m_playerFont);
        }
    }

    //Check for stale explosions, and update those who are still alive
    foreach(quint64 localExplosionID, m_activeExplosions.keys())
    {
        bool found = false;

        foreach(NetExplosion currentExplosion, m_gameData.explosions())
        {
            if(currentExplosion.ID() == localExplosionID)
            {
                m_activeExplosions[localExplosionID]->Update();
                m_activeExplosions[localExplosionID]->setX(currentExplosion.X());
                m_activeExplosions[localExplosionID]->setY(currentExplosion.Y());
                found = true;
                break;
            }
        }

        if(!found)
        {
            qDebug("Explosion Expired");
            delete m_activeExplosions.take(localExplosionID);
        }
    }

    return true;
}

void MainGame::StartRocketSound()
{
    if (soundPlayer->soundsPlaying().contains("rocket"))
        return;

    soundPlayer->playSound("rocket");
}

void MainGame::StopRocketSound()
{
    if (soundPlayer->soundsPlaying().contains("rocket"))
        soundPlayer->stopSound("rocket");
}

void MainGame::Draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //al_draw_bitmap(m_background, m_localX, , 0);

    m_mainCamera.startCamera();

    //draw background
    int xOffset = ((m_localX - (qFloor(m_localX/800)*800)) < 400 ) ? -1 : 1;
    int yOffset = ((m_localY - (qFloor(m_localY/600)*600)) < 300 ) ? -1 : 1;

    al_draw_bitmap(m_background, qFloor(m_localX/800)*800, qFloor(m_localY/600)*600, 0); //On Player
    al_draw_bitmap(m_background, (qFloor(m_localX/800)+xOffset)*800, qFloor(m_localY/600)*600, 0); //Left or right of player
    al_draw_bitmap(m_background, (qFloor(m_localX/800))*800, (qFloor(m_localY/600) + yOffset)*600, 0); //Above or below player
    al_draw_bitmap(m_background, (qFloor(m_localX/800)+xOffset)*800, (qFloor(m_localY/600) + yOffset)*600, 0); //Corners

    al_draw_rectangle(0,0,m_fieldWidth,m_fieldHeight,al_map_rgb(255,0,0), 2);

    foreach(NetShip ship, m_gameData.ships())
    {
        if (QString (ship.name().toLower()) == m_account.Username.toLower())
        {
            m_localX = ship.X();
            m_localY = ship.Y();

            m_mainCamera.setX(400-m_localX);
            m_mainCamera.setY(300-m_localY);
            m_mainCamera.startCamera();
            m_miniMap->AddPlayer(ship.X(), ship.Y(), al_map_rgb(0,255,0));
        }
        else
        {
            m_miniMap->AddPlayer(ship.X(), ship.Y(), al_map_rgb(255,0,0));
        }

        //Add player to the mini map
        DrawShip(ship.X(), ship.Y(), ship.rotation(), ((QString (ship.name().toLower()) == m_account.Username.toLower()) ? al_map_rgb(69,214,95) : al_map_rgb(255,0,0)) );
        DrawHealth(ship.X(), ship.Y(), ship.health(), QString(ship.name()));
    }

    foreach(NetBullet bullet, m_gameData.bullets())
    {
        DrawBullet(bullet.X(), bullet.Y());
        m_miniMap->AddBullet(bullet.X(), bullet.Y());
    }

    Explosion *expl = 0;
    foreach(NetExplosion explosion, m_gameData.explosions())
    {
        expl = m_activeExplosions[explosion.ID()];
        if (expl)
            expl->Draw(&m_mainCamera);
    }

    m_mainCamera.stopCamera();

    //Stuff that stays static on the screen
    m_miniMap->Draw(650,20, 0.5);
    m_miniMap->ClearMap(al_map_rgb(50,50,50));

    if(m_menuOpen)
    {
        m_gameMenu->Draw();
    }
}

void MainGame::setAccount(Account account)
{
    m_account = account;
}

ALLEGRO_FONT MainGame::getPlayerFont()
{
    return m_playerFont;
}

GameUpdateData MainGame::GetGameDate() const
{
    return m_gameData;
}

/////////////////////////PRIVATE//////////////////////////

void MainGame::DrawShip(int X, int Y, float rotation, ALLEGRO_COLOR color)
{
    ALLEGRO_TRANSFORM ShipTrans;
    al_build_transform(&ShipTrans, X, Y, 1, 1, rotation);

    ALLEGRO_TRANSFORM trans = m_mainCamera.getCamera();
    al_compose_transform(&ShipTrans, &trans);
    al_use_transform(&ShipTrans);

    al_draw_triangle(12, 0, -12, 10, -12, -10, color, 2);

    trans = m_mainCamera.getCamera();
    al_use_transform(&trans);
}

void MainGame::DrawBullet(int X, int Y)
{
    al_draw_filled_circle(X, Y, 2, al_map_rgb(255,0,0));
}

void MainGame::DrawExplosion(int X, int Y)
{
    al_draw_text(&m_playerFont, al_map_rgb(69,214,95), X, Y-5, ALLEGRO_ALIGN_CENTRE, "!BOOM!");
}


void MainGame::DrawHealth(int X, int Y, int health, QString name)
{
    QString stringHealth = QString::number(health);
    al_draw_text(&m_playerFont, al_map_rgb(69,214,95), X, Y-35, ALLEGRO_ALIGN_CENTRE, (name + " (" + stringHealth + ")").toLocal8Bit().data());
}

void MainGame::RotateShip(const qint8 dir)
{
    Packet p;
    p.setCommandId((dir == ROT_LEFT) ? Protocol::PlayerRotateLeft : Protocol::PlayerRotateRight);
    p.setArgs(QByteArray("foo"));

    m_client->sendPacket(p);
}

void MainGame::ThrustFoward()
{
    Packet p;
    p.setCommandId(Protocol::PlayerThrustFoward);

    m_client->sendPacket(p);
}

void MainGame::ThrustReverse()
{
    Packet p;
    p.setCommandId(Protocol::PlayerThrustReverse);

    m_client->sendPacket(p);
}

void MainGame::FireWeapon()
{
    Packet p;
    p.setCommandId(Protocol::PlayerFireWeapon);

    m_client->sendPacket(p);

    if (!soundPlayer->soundsPlaying().contains("fire") && (m_lastShot + 250 < m_timer.elapsed()))
    {
        m_lastShot = m_timer.elapsed();
        //soundPlayer->playSound("fire");
    }
}

void MainGame::Disconnect()
{
    Packet p;
    p.setCommandId(Protocol::PlayerDisconnect);

    m_client->sendPacket(p);
}
