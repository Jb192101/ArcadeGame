#include "GameController.h"
#include "MenuController.h"

GameController::GameController(int width, int height)
    : m_model(width, height), m_isGameActive(false) 
{
    m_view = new GameView(width, height, "Asteroids", &m_model);
    m_view->user_data(this);
    Fl::add_timeout(0.016, timerCallback, this);
}

GameController::~GameController() 
{
    delete m_view;
}

void GameController::run() 
{
    m_isGameActive = true;
    m_view->show();
    Fl::run();
}

void GameController::returnToMenu() 
{
    m_isGameActive = false;
    m_view->hide();
    if (m_menuController) {
        m_menuController->run();
    }
}

void GameController::timerCallback(void* data) 
{
    GameController* controller = static_cast<GameController*>(data);

    if (controller->m_isGameActive) {
        if (controller->m_model.isGameOver()) 
        {
            controller->returnToMenu();
        }
        else 
        {
            controller->processInput();
            controller->m_model.update();
            controller->m_view->redraw();
        }
        Fl::repeat_timeout(0.016, timerCallback, data);
    }
}

int GameController::handleKey(int event, void* data)
{
    GameController* controller = static_cast<GameController*>(data);

    if (event == FL_KEYDOWN || event == FL_KEYUP) 
    {
        bool pressed = (event == FL_KEYDOWN);

        switch (Fl::event_key()) {
        case FL_Left: controller->m_keyLeft = pressed; break;
        case FL_Right: controller->m_keyRight = pressed; break;
        case FL_Up: controller->m_keyUp = pressed; break;
        case ' ': controller->m_keySpace = pressed; break;
        default: return 0;
        }
        return 1;
    }
    return 0;
}

void GameController::handleKeyDown(int key) 
{
    switch (key) 
    {
    case FL_Left: m_keyLeft = true; break;
    case FL_Right: m_keyRight = true; break;
    case FL_Up: m_keyUp = true; break;
    case ' ': m_keySpace = true; break;
    //case 'r': case 'R':
    //    if (m_model.isGameOver()) m_model.resetGame();
    //    break;
    }
}

void GameController::handleKeyUp(int key) 
{
    switch (key) {
    case FL_Left: m_keyLeft = false; break;
    case FL_Right: m_keyRight = false; break;
    case FL_Up: m_keyUp = false; break;
    case ' ': m_keySpace = false; break;
    }
}

void GameController::processInput()
{
    // ќбработка вращени€
    if (m_keyLeft) m_model.getShip()->rotateLeft();
    if (m_keyRight) m_model.getShip()->rotateRight();

    // ќбработка т€ги
    if (m_keyUp) m_model.getShip()->setThrust(true);
    else m_model.getShip()->setThrust(false);

    // ќбработка стрельбы
    static bool spaceWasPressed = false;
    if (m_keySpace && !spaceWasPressed) {
        m_model.fireBullet();
        spaceWasPressed = true;
    }
    else if (!m_keySpace) {
        spaceWasPressed = false;
    }
}

void GameController::setMenuController(MenuController* menu)
{
    m_menuController = menu;
}