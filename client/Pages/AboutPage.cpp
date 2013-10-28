#include "AboutPage.h"

#include <QtCore/QString>

#include "Elements/allegrobutton.h"

AboutPage::AboutPage(ALLEGRO_FONT *font)
    : m_font(font)
{
    m_buttonBack = new AllegroButton(100, 500, 40, 222, m_font, al_map_rgb(0,0,0), al_map_rgb(40,40,40), "Back" );
}

bool AboutPage::Update(ALLEGRO_MOUSE_EVENT *mouse)
{
    if(m_buttonBack->Update(mouse))
        return true;
    return false;
}

void AboutPage::Draw()
{
    QString aboutText = "Triangles in Space was made by:\n" +
                        QString("Jonathan Thomas - Server Architecture, Netcode\n") +
                        QString("Zach Mattor - Client, Server-Side Game Loop\n") +
                        QString("Adam Cumings - Database Design and Implementation");
    al_draw_text(m_font, al_map_rgb(69,214,95), 400, 200, ALLEGRO_ALIGN_CENTRE, aboutText.toAscii().data());

    m_buttonBack->Draw();
}
