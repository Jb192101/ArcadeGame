// MainMenuView.cpp
#include "MainMenuView.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>

MainMenuView::MainMenuView(int width, int height) {
    window = new Fl_Window(width, height, "Asteroids Game");
    window->begin();

    title = new Fl_Box(width / 2 - 100, height / 4, 200, 50, "ASTEROIDS");
    title->labelfont(FL_BOLD);
    title->labelsize(36);

    newGameButton = new Fl_Button(width / 2 - 50, height / 2 - 25, 100, 50, "New Game");
    aboutButton = new Fl_Button(width / 2 - 50, height / 2 + 50, 100, 50, "About program");
    exitButton = new Fl_Button(width / 2 - 50, height / 2 + 125, 100, 50, "Exit");

    window->end();
    window->color(FL_BLACK);
    title->labelcolor(FL_WHITE);

    newGameButton->callback(OnNewGameCallback, this);
    aboutButton->callback(OnAboutCallback, this);
    exitButton->callback(OnExitCallback, this);
}

MainMenuView::~MainMenuView() {
    delete window;
}

void MainMenuView::Draw() {
    window->redraw();
}

void MainMenuView::Show() {
    window->show();
}

void MainMenuView::Hide() {
    window->hide();
}

Fl_Widget* MainMenuView::GetWidget() {
    return window;
}

void MainMenuView::SetOnNewGame(std::function<void()> callback) {
    onNewGame = callback;
}

void MainMenuView::SetOnAbout(std::function<void()> callback) {
    onAbout = callback;
}

void MainMenuView::SetOnExit(std::function<void()> callback) {
    onExit = callback;
}

void MainMenuView::OnNewGameCallback(Fl_Widget* w, void* data) {
    MainMenuView* menu = static_cast<MainMenuView*>(data);
    if (menu->onNewGame) {
        menu->onNewGame();
    }
}

void MainMenuView::OnAboutCallback(Fl_Widget* w, void* data) {
    MainMenuView* menu = static_cast<MainMenuView*>(data);
    if (menu->onAbout) {
        menu->onAbout();
    }
}

void MainMenuView::OnExitCallback(Fl_Widget* w, void* data) {
    MainMenuView* menu = static_cast<MainMenuView*>(data);
    if (menu->onExit) {
        menu->onExit();
    }
}