#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QString>

#include "Elements/allegrobutton.h"
#include "Elements/allegrotextbox.h"
#include "Elements/Account.h"
#include "Crypto.h"

class LoginPage
{
public:
    LoginPage(ALLEGRO_FONT *font);
	~LoginPage();

    Account* Update(bool keys[255], ALLEGRO_MOUSE_EVENT *mouse);
    void Draw();

    bool ExitButtonPushed();

private:
    bool CheckAccount(QString username, QString password);

    AllegroButton *m_buttonLogin;
    AllegroButton *m_buttonExit;
    AllegroButton *m_buttonRegister;
    bool m_exitButtonPress;
    bool m_attemptFailed;

    AllegroTextBox *m_textboxUsername;
    AllegroTextBox *m_textboxPassword;

    ALLEGRO_FONT *m_font;
};

#endif // SERVERINFO_H
