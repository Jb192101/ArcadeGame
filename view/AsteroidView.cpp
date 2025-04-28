// AsteroidView.cpp
#include "AsteroidView.h"
#include <FL/fl_draw.H>
# define M_PI           3.14159265358979323846

AsteroidView::AsteroidView(AsteroidModel* asteroidModel, int x, int y, int w, int h)
    : model(asteroidModel) {
    canvas = new Fl_Box(x, y, w, h);
    canvas->box(FL_NO_BOX);
}

AsteroidView::~AsteroidView() {
    delete canvas;
}

void AsteroidView::Draw() {
    float x = model->GetX();
    float y = model->GetY();
    float rotation = model->GetRotation();
    const auto& shape = model->GetShape();

    fl_push_clip(canvas->x(), canvas->y(), canvas->w(), canvas->h());

    int centerX = canvas->x() + canvas->w() / 2;
    int centerY = canvas->y() + canvas->h() / 2;

    int asteroidX = centerX + static_cast<int>(x);
    int asteroidY = centerY + static_cast<int>(y);

    fl_color(FL_WHITE);

    // Преобразуем вращение в радианы
    float radians = rotation * (M_PI / 180.0f);
    float cosA = std::cos(radians);
    float sinA = std::sin(radians);

    // Рисуем астероид
    fl_begin_line();
    for (size_t i = 0; i < shape.size(); ++i) {
        float px = shape[i].first;
        float py = shape[i].second;

        // Поворачиваем точку
        float rx = px * cosA - py * sinA;
        float ry = px * sinA + py * cosA;

        fl_vertex(asteroidX + rx, asteroidY + ry);
    }
    // Замыкаем фигуру
    float px = shape[0].first;
    float py = shape[0].second;
    float rx = px * cosA - py * sinA;
    float ry = px * sinA + py * cosA;
    fl_vertex(asteroidX + rx, asteroidY + ry);

    fl_end_line();

    fl_pop_clip();
}

void AsteroidView::Show() {
    canvas->show();
}

void AsteroidView::Hide() {
    canvas->hide();
}

Fl_Widget* AsteroidView::GetWidget() {
    return canvas;
}