#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "Camera2D.h"

class Explosion
{
public:
    Explosion(int x, int y, ALLEGRO_FONT explosionFont);

    void Update();
    void Draw(Camera2D *camera);

    void setX(int x);
    void setY(int y);

private:
    int m_x;
    int m_y;

    float m_rotation;
    ALLEGRO_FONT m_explosionFont;
};

#endif // EXPLOSION_H
