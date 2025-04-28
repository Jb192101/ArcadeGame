#pragma once
#include "View.h"
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <functional>

class MainMenuView : public View {
private:
    Fl_Window* window;
    Fl_Box* title;
    Fl_Button* newGameButton;
    Fl_Button* aboutButton;
    Fl_Button* exitButton;

    std::function<void()> onNewGame;
    std::function<void()> onAbout;
    std::function<void()> onExit;

    static void OnNewGameCallback(Fl_Widget* w, void* data);
    static void OnAboutCallback(Fl_Widget* w, void* data);
    static void OnExitCallback(Fl_Widget* w, void* data);

public:
    MainMenuView(int width, int height);
    ~MainMenuView();

    void Draw() override;
    void Show() override;
    void Hide() override;
    Fl_Widget* GetWidget() override;

    Fl_Button* GetNewGameButton() const { return newGameButton; }
    Fl_Button* GetAboutButton() const { return aboutButton; }
    Fl_Button* GetExitButton() const { return exitButton; }

    void SetOnNewGame(std::function<void()> callback);
    void SetOnAbout(std::function<void()> callback);
    void SetOnExit(std::function<void()> callback);
};