// SpaceShipView.cpp
#include "SpaceShipView.h"
#include <FL/fl_draw.H>
# define M_PI           3.14159265358979323846

SpaceShipView::SpaceShipView(SpaceShipModel* shipModel, int x, int y, int w, int h)
    : model(shipModel) {
    canvas = new Fl_Box(x, y, w, h);
    canvas->box(FL_NO_BOX);
}

SpaceShipView::~SpaceShipView() {
    delete canvas;
}

void SpaceShipView::Draw() {
    fl_push_clip(canvas->x(), canvas->y(), canvas->w(), canvas->h());
    // Получаем данные из модели
    float x = model->GetX();
    float y = model->GetY();
    float angle = model->GetAngle();

    // Рисуем корабль
    fl_push_clip(canvas->x(), canvas->y(), canvas->w(), canvas->h());

    fl_color(FL_WHITE);

    // Преобразуем координаты (FLTK использует y, увеличивающийся вниз)
    int centerX = canvas->x() + canvas->w() / 2;
    int centerY = canvas->y() + canvas->h() / 2;

    int shipX = centerX + static_cast<int>(x);
    int shipY = centerY + static_cast<int>(y);

    // Рисуем треугольник, представляющий корабль
    float radians = model->GetAngle() * (M_PI / 180.0f);
    float cosA = std::cos(radians);
    float sinA = std::sin(radians);

    // Точки треугольника (перед преобразованием)
    int p1x = 0, p1y = -15;  // Нос корабля
    int p2x = -10, p2y = 10; // Левая задняя точка
    int p3x = 10, p3y = 10;  // Правая задняя точка

    // Поворачиваем точки
    int rp1x = static_cast<int>(p1x * cosA - p1y * sinA);
    int rp1y = static_cast<int>(p1x * sinA + p1y * cosA);
    int rp2x = static_cast<int>(p2x * cosA - p2y * sinA);
    int rp2y = static_cast<int>(p2x * sinA + p2y * cosA);
    int rp3x = static_cast<int>(p3x * cosA - p3y * sinA);
    int rp3y = static_cast<int>(p3x * sinA + p3y * cosA);

    // Смещаем точки в позицию корабля
    rp1x += shipX; rp1y += shipY;
    rp2x += shipX; rp2y += shipY;
    rp3x += shipX; rp3y += shipY;

    // Рисуем треугольник
    fl_begin_polygon();
    fl_vertex(rp1x, rp1y);
    fl_vertex(rp2x, rp2y);
    fl_vertex(rp3x, rp3y);
    fl_end_polygon();

    fl_pop_clip();
}

void SpaceShipView::Show() {
    canvas->show();
}

void SpaceShipView::Hide() {
    canvas->hide();
}

Fl_Widget* SpaceShipView::GetWidget() {
    return canvas;
}