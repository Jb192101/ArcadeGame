// BulletView.cpp
#include "BulletView.h"

BulletView::BulletView(BulletModel* bulletModel, int x, int y, int w, int h)
    : model(bulletModel) {
    canvas = new Fl_Box(x, y, w, h);
    canvas->box(FL_NO_BOX);
}

BulletView::~BulletView() {
    delete canvas;
}

void BulletView::Draw() {
    float x = model->GetX();
    float y = model->GetY();

    fl_push_clip(canvas->x(), canvas->y(), canvas->w(), canvas->h());

    int centerX = canvas->x() + canvas->w() / 2;
    int centerY = canvas->y() + canvas->h() / 2;

    int bulletX = centerX + static_cast<int>(x);
    int bulletY = centerY + static_cast<int>(y);

    fl_color(FL_YELLOW);
    fl_begin_line();
    fl_circle(bulletX, bulletY, 2);
    fl_end_line();

    fl_pop_clip();
}

void BulletView::Show() {
    canvas->show();
}

void BulletView::Hide() {
    canvas->hide();
}

Fl_Widget* BulletView::GetWidget() {
    return canvas;
}