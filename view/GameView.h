#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include "../model/GameModel.h"


class GameView : public Fl_Double_Window 
{
private:
    std::unique_ptr<GameModel> m_model = nullptr;

    static void timerCallback(void* data);

public:
    GameView(int w, int h, const char* title, GameModel* model);

    void draw() override;
    void drawShip() const;
    void drawAsteroids() const;
    void drawBullets() const;
    void drawHUD() const;

    int handle(int event) override;
};