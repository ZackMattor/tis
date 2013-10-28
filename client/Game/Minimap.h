#ifndef MINIMAP_H
#define MINIMAP_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class Minimap
{
public:
    Minimap(int globalWidth, int globalHeight, int miniMapHeight, int miniMapWidth, ALLEGRO_DISPLAY *display);

    void ChangeMapSie(int width, int height);

    void Draw(int x, int y, float Opacity);
    void ClearMap(ALLEGRO_COLOR backgroundColor);
    void AddPlayer(int globalX, int globalY, ALLEGRO_COLOR shipColor);
    void AddBullet(int globalX, int globalY);
private:
    ALLEGRO_BITMAP *m_theMap;
    ALLEGRO_DISPLAY *m_display;
    int m_miniMapHeight, m_miniMapWidth;
    int m_globalWidth, m_globalHeight;
};

#endif // MINIMAP_H
