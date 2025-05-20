#pragma once
#include "../model/GameModel.h"
#include "MenuController.h"
#include "../view/GameView.h"
#include <FL/Fl.H>
#include <memory>

class MenuController;

class GameController 
{
private:
    GameModel m_model;
    std::unique_ptr<GameView> m_view;
    std::unique_ptr<MenuController> m_menuController;
    bool m_isGameActive;

    bool m_keyLeft = false;
    bool m_keyRight = false;
    bool m_keyUp = false;
    bool m_keySpace = false;
    bool m_keyR = false;

    static void timerCallback(void* data);

    void processInput();

public:
    GameController(int width, int height);

    void run();

    void setMenuController(MenuController* menu);
    void returnToMenu();

    void handleKeyDown(int key);
    void handleKeyUp(int key);
};