#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include "GameModel.h"

#define M_PI 3.14

class GameView : public Fl_Double_Window {
private:
    GameModel* m_model;

public:
    GameView(int w, int h, const char* title, GameModel* model);

    void draw() override;
    void drawShip() const;
    void drawAsteroids() const;
    void drawBullets() const;
    void drawHUD() const;

    int handle(int event) override;
};