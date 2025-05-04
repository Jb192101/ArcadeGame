#pragma once
#include <FL/Fl.H>
#include "MenuView.h"

class GameController;

class MenuController {
private:
    MenuView* menuView;
    GameController* gameController;

    static void onNewGame(Fl_Widget* w, void* data);
    static void onAbout(Fl_Widget* w, void* data);
    static void onExit(Fl_Widget* w, void* data);

public:
    MenuController();
    ~MenuController();

    void run();
    void returnToMenu();
};