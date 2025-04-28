#pragma once

// SpaceShipView.h
#pragma once
#include "View.h"
#include "SpaceShipModel.h"
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>

class SpaceShipView : public View {
private:
    SpaceShipModel* model;
    Fl_Box* canvas;

public:
    SpaceShipView(SpaceShipModel* shipModel, int x, int y, int w, int h);
    ~SpaceShipView();

    void Draw() override;
    void Show() override;
    void Hide() override;
    Fl_Widget* GetWidget() override;
};
