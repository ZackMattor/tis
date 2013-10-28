#include "Minimap.h"

Minimap::Minimap(int globalWidth, int globalHeight, int miniMapWidth, int miniMapHeight, ALLEGRO_DISPLAY *display)
    : m_display(display)
    , m_miniMapHeight(miniMapHeight)
    , m_miniMapWidth(miniMapWidth)
    , m_globalWidth(globalWidth)
    , m_globalHeight(globalHeight)
{
    m_theMap = al_create_bitmap(miniMapWidth, miniMapHeight);
}


void Minimap::ChangeMapSie(int width, int height)
{
    m_miniMapWidth = width;
    m_miniMapHeight = height;
}

void Minimap::Draw(int x, int y, float Opacity)
{
    al_draw_tinted_bitmap(m_theMap, al_map_rgba_f(1, 1, 1, Opacity), x, y, 0);
}

void Minimap::ClearMap(ALLEGRO_COLOR backgroundColor)
{
    al_set_target_bitmap(m_theMap);

    al_clear_to_color(backgroundColor);

    al_set_target_bitmap(al_get_backbuffer(m_display));
}

void Minimap::AddPlayer(int globalX, int globalY, ALLEGRO_COLOR shipColor)
{
    al_set_target_bitmap(m_theMap);
    int xOnMap = ((globalX * m_miniMapWidth) / m_globalWidth);
    int yOnMap = ((globalY * m_miniMapHeight) / m_globalHeight);

    al_draw_circle(xOnMap, yOnMap, 2, shipColor, 1);

    al_set_target_bitmap(al_get_backbuffer(m_display));
}

void Minimap::AddBullet(int globalX, int globalY)
{
    al_set_target_bitmap(m_theMap);
    int xOnMap = ((globalX * m_miniMapWidth) / m_globalWidth);
    int yOnMap = ((globalY * m_miniMapHeight) / m_globalHeight);

    al_draw_circle(xOnMap, yOnMap, 1, al_map_rgb(255,255,255), 1);

    al_set_target_bitmap(al_get_backbuffer(m_display));
}
