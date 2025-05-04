#pragma once
#include <FL/Fl.H>
#include "GameModel.h"
#include "GameView.h"
#include "MenuView.h"

class MenuController;

class GameController 
{
private:
    GameModel m_model;
    GameView* m_view;
    MenuController* m_menuController;
    bool m_isGameActive;

    // Флаги состояния клавиш
    bool m_keyLeft = false;
    bool m_keyRight = false;
    bool m_keyUp = false;
    bool m_keySpace = false;
    bool m_keyR = false;

    static void timerCallback(void* data);
    static int handleKey(int event, void* data);

    void processInput();

public:
    GameController(int width, int height);
    ~GameController();

    void run();
    void setMenuController(MenuController* menu);
    void returnToMenu();

    void handleKeyDown(int key);
    void handleKeyUp(int key);
};