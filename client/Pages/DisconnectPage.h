#ifndef DISCONNECT_H
#define DISCONNECT_H

#include <QString>

#include "Elements/allegrobutton.h"

class DisconnectPage
{
public:
    DisconnectPage(QString reason, ALLEGRO_FONT pageFont);

    bool Update(ALLEGRO_MOUSE_EVENT *mouse);
    void Draw();
private:
    QString m_reason;
    AllegroButton *m_buttonBack;
    ALLEGRO_FONT m_pageFont;
};

#endif // DISCONNECT_H
