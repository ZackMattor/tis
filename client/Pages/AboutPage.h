#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <allegro5/allegro_font.h>

class AllegroButton;

class AboutPage
{
public:
    AboutPage(ALLEGRO_FONT *font);

    bool Update(ALLEGRO_MOUSE_EVENT *mouse);
    void Draw();

private:
    ALLEGRO_FONT *m_font;
    AllegroButton *m_buttonBack;
};

#endif // ABOUTPAGE_H
