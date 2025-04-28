// BulletView.h
#pragma once
#include "View.h"
#include "BulletModel.h"
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>

#include <FL/fl_draw.H>

class BulletView : public View {
private:
    BulletModel* model;
    Fl_Box* canvas;

public:
    BulletView(BulletModel* bulletModel, int x, int y, int w, int h);
    ~BulletView();

    void Draw() override;
    void Show() override;
    void Hide() override;
    Fl_Widget* GetWidget() override;
};