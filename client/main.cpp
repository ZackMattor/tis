#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtCore/QTime>
#include <QDebug>

#include <allegro5/allegro.h>

#include "DisplayGlobals.h"
#include "UdpClient.h"
#include "ProtocolGlobals.h"
#include "Menu.h"
#include "ServerList/ServerList.h"
#include "ServerList/ServerInfo.h"
#include "GameUpdateData.h"
#include "SoundPlayer.h"

#include "Pages/AboutPage.h"
#include "Pages/LoginPage.h"
#include "Game/MainGame.h"
#include "Pages/DisconnectPage.h"

ServerInfo *serverInfo;
Account *account;
int gameState = LOADING;
QList<Packet> packets;
UdpClient client;
SoundPlayer *soundPlayer;
quint64 currentGameDataTimestamp = 0;
QTime gameTimeout;


/**Pages and such**/
LoginPage *loginPage;
Menu *mainMenu;
ServerList *serverList;
MainGame *game;
DisconnectPage *dcPage;
AboutPage *aboutPage;

bool keys[255] = {false};
ALLEGRO_MOUSE_EVENT mouse;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_FONT *listFont;
ALLEGRO_FONT *playerFont;

void LoadSounds();
void Update();
void Draw();
void DrawMainGame();
ALLEGRO_BITMAP * makeStarfield(int numStars);

int main(int argc, char *argv[])
{
    //Allegro Setup
    if(!al_init())
    {
        qDebug() << "Allegro Init is failing!";
        return -1;
    }

    QCoreApplication app(argc, argv);
    app.setApplicationName("Triangles in Space");

    LoadSounds();

    QThread thread;
    client.moveToThread(&thread);
    thread.start();

    qDebug() << "Welcome!" << endl;
    //primitive variable
    bool redraw = true;
    const int FPS = 60;

    //Allegro variables

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(ScreenWidth, ScreenHeight);
    al_set_window_title(display, "Triangles in Space");

    if(!display)
    {
        qDebug() << "Display is failing!";
        return -1;
    }

    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    qsrand(QTime::currentTime().msec());

    QString tifax = "TIFAX.ttf";
    QString arial = "arial.ttf";

#ifndef Q_OS_WIN
    tifax.prepend("/usr/share/tis/");
    arial.prepend("/usr/share/tis/");
#endif

    listFont = al_load_font(tifax.toLocal8Bit().data(), 20, 0);
    playerFont = al_load_font(arial.toLocal8Bit().data(), 12, 0);

    serverList = new ServerList(listFont);
    aboutPage = new AboutPage(listFont);

    al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE*)al_get_keyboard_event_source());
    al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE*)al_get_mouse_event_source());
    al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE*)al_get_timer_event_source(timer));
    al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE*)al_get_display_event_source(display));
    al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE*)display);

    al_start_timer(timer);

    while(gameState != CLOSE)
    {
        QCoreApplication::processEvents();
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        switch(ev.type)
        {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                Update();
            break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                gameState = CLOSE;
            break;

            case ALLEGRO_EVENT_KEY_DOWN:
                keys[ev.keyboard.keycode] = true;
            break;

            case ALLEGRO_EVENT_KEY_UP:
                keys[ev.keyboard.keycode] = false;
            break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            case ALLEGRO_EVENT_MOUSE_AXES:
                mouse = ev.mouse;
            break;
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            //cout << "Drawing";
            redraw = false;
            Draw();

            //FLIP BUFFERS
            al_flip_display();

            if(gameState != GAME) //game takes care of it's own background
            {
                if(background != NULL)
                {
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(background, 0, 0, 0);
                }
                else
                {
                    al_clear_to_color(al_map_rgb(0, 191, 255));
                }
            }
        }
    }

    soundPlayer->stopAll();

    return 1;
}

void LoadSounds()
{
    soundPlayer = new SoundPlayer();
    QString prefix;

#ifndef Q_OS_WIN
    prefix = "/usr/share/tis/";
#endif
    // Load bgm
    soundPlayer->addSong(prefix + "repeatnoss.ogg");
    soundPlayer->addSong(prefix + "bitsisisis.ogg");
    soundPlayer->addSong(prefix + "onetrickpony.ogg");

    // Load sound effects/looping bgm
    soundPlayer->addSound(prefix + "onetrickpony.ogg", "themeloop", true);
    soundPlayer->addSound(prefix + "pewpew.ogg", "fire");
    soundPlayer->addSound(prefix + "explode.ogg", "explode");
    soundPlayer->addSound(prefix + "rocket.ogg", "rocket", true);
}

void Update()
{
    switch(gameState)
    {
    case LOADING:
        qDebug() << "Entered the LOADING state" << endl;

        //Maim Menu Setup
        mainMenu = new Menu(ScreenWidth/3,300, listFont);

        mainMenu->AddItem("Server List", LOADSERVERLIST);
        mainMenu->AddItem("About", ABOUT);
        mainMenu->AddItem("Exit", CLOSE);
        mainMenu->SetSpacing(90);

        loginPage = new LoginPage(listFont);

        background = makeStarfield(100);
        gameState = LOGIN;
        break;

    case LOGIN:
        account = loginPage->Update(keys, &mouse);

        if(account != 0)
        {
            gameState = MENU;
            soundPlayer->playSound("themeloop");
        }
        if(loginPage->ExitButtonPushed())
        {
            gameState = CLOSE;
        }
        break;

    case MENU: {
        int ret = mainMenu->Update(keys, &mouse);
        if (ret > 0)
            gameState = ret;
        break;
    }
    case ABOUT:
        //cout << "Entered the ABOUT state" << endl;
        if (aboutPage->Update(&mouse))
            gameState = MENU;
        break;

    case LOADSERVERLIST:
        //cout << "Entered the LOADSERVERLIST state" << endl;
        qDebug() << "Refreshing list";
        serverList->RefreshList();
        gameState = SERVERLIST;
        break;

    case SERVERLIST:
    {
        //cout << "Entered the SERVERLIST state" << endl;
        serverInfo = serverList->Update(&mouse);

        if(serverList->BackPushed())
        {
            delete serverList;
            gameState = MENU;
        }

        if(serverInfo != 0)
        {
            gameState = CONNECTINIT;
        }
    }
        break;

    case CONNECTINIT:
    {
        qDebug() << "Entered the CONNECTING state";
        qDebug() << "Conncting to: " << serverInfo->ipAddr;
        client.setServer(serverInfo->ipAddr, 50000);
        QMetaObject::invokeMethod(&client, "init", Qt::BlockingQueuedConnection);
        Packet packet;
        packet.setCommandId(Protocol::PlayerConnect);

        QByteArray args;
        args.append(account->Username).append('\0');
        args.append(account->Password).append('\0');
        packet.setArgs(args);

        client.sendPacket(packet);

        background = makeStarfield(300);
        gameState = CONNECTING;
        gameTimeout = QTime::currentTime().addMSecs(5000);
    }
        break;

    case CONNECTING:
    {
        if(gameTimeout < QTime::currentTime())
        {
            dcPage = new DisconnectPage("Could not connect.", *listFont);

            gameState = DISCONNECT;
        }

        packets = client.receivedPackets();

        foreach (Packet p, packets)
        {
            if(p.commandId() == Protocol::PlayerConnectResponse)
            {
                if(p.args()[0] == (char)Protocol::Successful)
                {
                    game = new MainGame(*playerFont, &client, background, display);
                    game->setAccount(*account);
                    gameState = GAME;
                    break;
                }
                else if(p.args()[0] == (char)Protocol::ServerFull)
                {
                    dcPage = new DisconnectPage("Server Full", *listFont);

                    gameState = DISCONNECT;
                }
                else
                {
                    dcPage = new DisconnectPage(QString("Unknown"), *listFont);

                    gameState = DISCONNECT;
                }
            }
        }

        packets.clear();
    }
        break;

    case GAME:
    {
        packets = client.receivedPackets();
        bool running = true;

        if(gameTimeout < QTime::currentTime())
        {
            dcPage = new DisconnectPage("Lost connection to the server", *listFont);

            gameState = DISCONNECT;
        }

        foreach (Packet p, packets)
        {
            switch(p.commandId())
            {
                case Protocol::GameUpdate: //The game data
                {
                    GameUpdateData newData(p.args());

                    if(newData.timestamp() > currentGameDataTimestamp || currentGameDataTimestamp == 0)
                    {
                        game->Update(newData, keys, mouse);
                        currentGameDataTimestamp = newData.timestamp();
                        gameTimeout = QTime::currentTime().addSecs(1);
                    }
                }
                break;

                case Protocol::PlayerDisconnected:
                {
                    QMetaObject::invokeMethod(&client, "stop", Qt::QueuedConnection);
                    bool running = game->Update(GameUpdateData(0), keys, mouse);

                    dcPage = new DisconnectPage(QString(p.args()), *listFont);

                    gameState = DISCONNECT;
                }
                break;
            }
        }

        client.clearReceivedPackets();
    }
        break;
     case DISCONNECT:
        currentGameDataTimestamp = 0;

        if( dcPage->Update(&mouse) ) //if we are done here
        {
            delete dcPage;
            background = makeStarfield(100);
            gameState = LOADSERVERLIST;
        }
        break;
     case CLOSE:

        break;
    }
}

void Draw()
{
    switch(gameState)
    {
    case LOADING:
        break;

    case LOGIN:
        loginPage->Draw();
        break;

    case MENU:
        mainMenu->Draw();
        break;

    case ABOUT:
        aboutPage->Draw();
        break;

    case SERVERLIST:
        serverList->Draw();
        break;

     case CONNECTING:

        break;

     case GAME:
        if(currentGameDataTimestamp != 0)
        {
            game->Draw();
        }
        break;
     case DISCONNECT:
        dcPage->Draw();
        break;
     case CLOSE:

        break;
    }
}

ALLEGRO_BITMAP *makeStarfield(int numStars)
{
    ALLEGRO_BITMAP * bit = al_create_bitmap(ScreenWidth, ScreenHeight);

    al_set_target_bitmap(bit);

    //al_clear_to_color(al_map_rgb(0, 0, 0));

    for(int i = 0; i < numStars; i++)
        al_put_pixel(qrand() % ScreenWidth, qrand() % ScreenHeight, al_map_rgb(255,255,255));

    al_set_target_bitmap(al_get_backbuffer(display));

    return bit;
}
