#include "GameController.h"
#include <iostream>

GameController::GameController(int width, int height)
    : m_model(width, height), m_isGameActive(false), m_view(std::make_unique<GameView>(width, height, "Asteroids", &m_model))
{
    m_view->user_data(this);
}

void GameController::run() 
{
    m_isGameActive = true;
    m_view->show();
    m_model.start();

    m_keyLeft = false;
    m_keyRight = false;
    m_keyUp = false;
    m_keySpace = false;
    m_keyR = false;

    Fl::add_timeout(0.016, timerCallback, this);
}

void GameController::returnToMenu() 
{
    m_model.stop();
    m_view->hide();
    m_model.resetGame();
    if (m_menuController) 
    {
        m_menuController->run();
    }
}

void GameController::timerCallback(void* data) 
{
    GameController* controller = static_cast<GameController*>(data);

    if (controller->m_isGameActive) 
    {
        if (controller->m_model.getGameOver()) 
        {
            controller->m_isGameActive = false;
            controller->returnToMenu();
        }
        else 
        {
            controller->processInput();
            Fl::repeat_timeout(0.016, timerCallback, data);
        }
    }
}

void GameController::handleKeyDown(int key) 
{
    switch (key) 
    {
    case FL_Left: m_keyLeft = true; break;
    case FL_Right: m_keyRight = true; break;
    case FL_Up: m_keyUp = true; break;
    case ' ': m_keySpace = true; break;
    }
}

void GameController::handleKeyUp(int key) 
{
    switch (key) 
    {
    case FL_Left: m_keyLeft = false; break;
    case FL_Right: m_keyRight = false; break;
    case FL_Up: m_keyUp = false; break;
    case ' ': m_keySpace = false; break;
    }
}

void GameController::processInput()
{
    if (m_keyLeft) m_model.getShip()->rotateLeft();
    if (m_keyRight) m_model.getShip()->rotateRight();

    if (m_keyUp) m_model.getShip()->setThrust(true);
    else m_model.getShip()->setThrust(false);

    static bool spaceWasPressed = false;
    if (m_keySpace && !spaceWasPressed) 
    {
        m_model.fireBullet();
        spaceWasPressed = true;
    }
    else if (!m_keySpace) 
    {
        spaceWasPressed = false;
    }
}

void GameController::setMenuController(MenuController* menu)
{
    m_menuController = std::unique_ptr<MenuController>(menu);
}