#include "DisconnectPage.h"

DisconnectPage::DisconnectPage(QString reason, ALLEGRO_FONT pageFont) : m_reason(reason), m_pageFont(pageFont)
{
   m_buttonBack = new AllegroButton(280, 300, 40, 310, &m_pageFont, al_map_rgb(0,0,0), al_map_rgb(40,40,40), "Back to Serverlist" );
}

bool DisconnectPage::Update(ALLEGRO_MOUSE_EVENT *mouse)
{
    if(m_buttonBack->Update(mouse))
        return true;
    return false;
}

void DisconnectPage::Draw()
{
    al_draw_text(&m_pageFont, al_map_rgb(69,214,95), 400, 200, ALLEGRO_ALIGN_CENTRE, QString("Disconnected from server: " + m_reason).toLocal8Bit().data());
    m_buttonBack->Draw();
}
