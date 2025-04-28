// AsteroidView.h
#pragma once
#include "View.h"
#include "AsteroidModel.h"
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>

class AsteroidView : public View {
private:
    AsteroidModel* model;
    Fl_Box* canvas;

public:
    AsteroidView(AsteroidModel* asteroidModel, int x, int y, int w, int h);
    ~AsteroidView();

    void Draw() override;
    void Show() override;
    void Hide() override;
    Fl_Widget* GetWidget() override;
};