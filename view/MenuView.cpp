#include "MenuView.h"
#include "GameController.h"
#include <FL/fl_message.H>

MenuView::MenuView(int w, int h, const char* title)
    : Fl_Window(w, h, title) 
{

    begin();
    m_newGameBtn = new Fl_Button(w / 2 - 100, h / 2 - 60, 200, 40, "New Game");
    m_aboutBtn = new Fl_Button(w / 2 - 100, h / 2, 200, 40, "About");
    m_exitBtn = new Fl_Button(w / 2 - 100, h / 2 + 60, 200, 40, "Exit");
    end();
}

// Установка callback-ов
void MenuView::setCallbacks(Fl_Callback* newGameCb,
    Fl_Callback* aboutCb,
    Fl_Callback* exitCb,
    void* data) 
{
    m_newGameBtn->callback(newGameCb, data);
    m_aboutBtn->callback(aboutCb, data);
    m_exitBtn->callback(exitCb, data);
}