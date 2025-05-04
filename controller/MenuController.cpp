#include "MenuController.h"
#include "GameController.h"
#include <FL/fl_message.H>

MenuController::MenuController() {
    menuView = new MenuView(400, 300, "Asteroids Menu");
    menuView->setCallbacks(onNewGame, onAbout, onExit, this);
}

MenuController::~MenuController() {
    delete menuView;
    if (gameController) delete gameController;
}

void MenuController::run() {
    menuView->show();
}

void MenuController::returnToMenu() {
    if (gameController) {
        delete gameController;
        gameController = nullptr;
    }
    menuView->show();
}

void MenuController::onNewGame(Fl_Widget* w, void* data) {
    MenuController* controller = static_cast<MenuController*>(data);
    controller->menuView->hide();

    controller->gameController = new GameController(800, 600);
    controller->gameController->setMenuController(controller);
    controller->gameController->run();
}

void MenuController::onAbout(Fl_Widget* w, void* data) {
    fl_message("Asteroids Game\nVersion 1.0\nCreated with FLTK");
}

void MenuController::onExit(Fl_Widget* w, void* data) {
    exit(0);
}