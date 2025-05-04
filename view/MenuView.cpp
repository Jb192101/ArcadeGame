#include "MenuView.h"
#include "GameController.h"
#include <FL/fl_message.H>

MenuView::MenuView(int w, int h, const char* title)
    : Fl_Window(w, h, title) {

    begin();
    // Создаем кнопки с размерами по центру окна
    newGameBtn = new Fl_Button(w / 2 - 100, h / 2 - 60, 200, 40, "New Game");
    aboutBtn = new Fl_Button(w / 2 - 100, h / 2, 200, 40, "About");
    exitBtn = new Fl_Button(w / 2 - 100, h / 2 + 60, 200, 40, "Exit");
    end();
}

void MenuView::setCallbacks(Fl_Callback* newGameCb,
    Fl_Callback* aboutCb,
    Fl_Callback* exitCb,
    void* data) {
    // Устанавливаем callback-функции для каждой кнопки
    newGameBtn->callback(newGameCb, data);
    aboutBtn->callback(aboutCb, data);
    exitBtn->callback(exitCb, data);
}