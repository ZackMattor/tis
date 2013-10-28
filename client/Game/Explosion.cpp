#include "Explosion.h"

Explosion::Explosion(int x, int y, ALLEGRO_FONT explosionFont)
    : m_x(x), m_y(y), m_explosionFont(explosionFont), m_rotation(0)
{

}

void Explosion::Draw(Camera2D *camera)
{
    ALLEGRO_TRANSFORM localTrans;
    ALLEGRO_TRANSFORM Identity;

    al_identity_transform(&Identity);

    al_build_transform(&localTrans, m_x, m_y, 1, 1, m_rotation);

    ALLEGRO_TRANSFORM trans = camera->getCamera();

    al_compose_transform(&localTrans, &trans);

    al_use_transform(&localTrans);

    al_draw_text(&m_explosionFont, al_map_rgb(69,214,95), 0, 0-5, ALLEGRO_ALIGN_CENTRE, "!BOOM!");

    al_use_transform(&Identity);
}

void Explosion::Update()
{
    m_rotation += 0.1;
}

void Explosion::setX(int x)
{
    m_x = x;
}

void Explosion::setY(int y)
{
    m_y = y;
}
