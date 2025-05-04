#include "MenuController.h"
#include "GameController.h"
#include <FL/fl_message.H>

MenuController::MenuController() {
    m_menuView = new MenuView(400, 300, "Asteroids Menu");
    m_menuView->setCallbacks(onNewGame, onAbout, onExit, this);
}

MenuController::~MenuController() {
    delete m_menuView;
    if (m_gameController) delete m_gameController;
}

void MenuController::run() 
{
    m_menuView->show();
}

void MenuController::onNewGame(Fl_Widget* w, void* data) 
{
    MenuController* controller = static_cast<MenuController*>(data);
    controller->m_menuView->hide();

    controller->m_gameController = new GameController(800, 600);
    controller->m_gameController->setMenuController(controller);
    controller->m_gameController->run();
}

void MenuController::onAbout(Fl_Widget* w, void* data) {
    fl_message("Asteroids Game\nHandle control:\nLeft - rotate ship left\nRigth - rotate ship right\nUp - moving ship forward\nWhitespace - shooting");
}

void MenuController::onExit(Fl_Widget* w, void* data) {
    exit(0);
}