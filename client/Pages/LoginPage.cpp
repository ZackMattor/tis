#include "LoginPage.h"
#include <iostream>

#include <QtCore/QUrl>
#include <QtGui/QDesktopServices>

using namespace std;

LoginPage::LoginPage(ALLEGRO_FONT *font) : m_font(font)
{
    m_buttonExit = new AllegroButton(100, 500, 40, 95, m_font, al_map_rgb(0,0,0), al_map_rgb(40,40,40), "Exit" );
    m_buttonLogin = new AllegroButton(250, 500, 40, 110, m_font, al_map_rgb(0,0,0), al_map_rgb(40,40,40), "Login" );
    m_buttonRegister = new AllegroButton(400, 500, 40, 170, m_font, al_map_rgb(0,0,0), al_map_rgb(40,40,40), "Register" );

    m_textboxUsername = new AllegroTextBox(200,200,200,40,m_font);
    m_textboxPassword = new AllegroTextBox(200,300,200,40,m_font);
    m_textboxPassword->SetPasswordMode(true);
    m_exitButtonPress = false;
    m_attemptFailed = false;
}

LoginPage::~LoginPage()
{
	delete m_buttonExit;
	delete m_buttonLogin;
	delete m_textboxUsername;
	delete m_textboxPassword;
}

Account* LoginPage::Update(bool keys[], ALLEGRO_MOUSE_EVENT *mouse)
{
    Account *account = 0;

    if(m_buttonLogin->Update(mouse))
    {
        account = new Account();
        account->Password = Crypto::passwordHash(m_textboxPassword->GetValue());
        account->Username = m_textboxUsername->GetValue();

        cout << account->Username.toStdString() << endl;

        if(!CheckAccount(account->Username, account->Password))
        {
			delete account;
            account = 0;

            //Clear the password because this was a failed attempt
            m_textboxPassword->SetValue("");

            m_attemptFailed = true; //mark this as a failed attempt
        }
    }

    if (m_buttonRegister->Update(mouse))
    {
        QDesktopServices::openUrl(QUrl("http://foxx.arksaw.com/tis/website/?Page=register"));
    }


    m_exitButtonPress = m_buttonExit->Update(mouse);

    m_textboxUsername->Update(keys, mouse);
    m_textboxPassword->Update(keys, mouse);

    return account;
}

void LoginPage::Draw()
{
    m_buttonLogin->Draw();
    m_buttonExit->Draw();
    m_buttonRegister->Draw();

    m_textboxUsername->Draw();
    m_textboxPassword->Draw();

    al_draw_text(m_font, al_map_rgb(69,214,95), 195, 205, ALLEGRO_ALIGN_RIGHT, "Username:");
    al_draw_text(m_font, al_map_rgb(69,214,95), 195, 305, ALLEGRO_ALIGN_RIGHT, "Password:");

    if(m_attemptFailed)
    {
        al_draw_text(m_font, al_map_rgb(255,0,0), 300, 100, ALLEGRO_ALIGN_RIGHT, "LOGIN FAILED");
    }
}

bool LoginPage::ExitButtonPushed()
{
    return m_exitButtonPress;
}

bool LoginPage::CheckAccount(QString username, QString password)
{

    return true;
}
