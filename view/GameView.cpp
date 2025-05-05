#include "GameView.h"
#include "GameController.h"

GameView::GameView(int w, int h, const char* title, GameModel* model)
    : Fl_Double_Window(w, h, title), m_model(model) {}

void GameView::draw() 
{
    Fl_Double_Window::draw();

    fl_color(FL_BLACK);
    fl_rectf(0, 0, w(), h());

    if (!m_model->getGameOver()) 
    {
        drawShip();
        drawAsteroids();
        drawBullets();
    }
    else 
    {
        fl_color(FL_WHITE);
        fl_font(FL_HELVETICA_BOLD, 36);
        fl_draw("GAME OVER", w() / 2 - 80, h() / 2 - 18);
        fl_font(FL_HELVETICA, 18);
        fl_draw("Press 'R' to restart", w() / 2 - 70, h() / 2 + 20);
    }

    drawHUD();
}

void GameView::drawShip() const 
{
    Ship* ship = m_model->getShip();
    if (!ship->isActive()) return;

    auto shape = ship->getShape();
    fl_color(FL_WHITE);
    fl_begin_line();
    for (auto& point : shape) 
    {
        fl_vertex(point.getX(), point.getY());
    }
    fl_end_line();
    fl_begin_line();
    fl_vertex(shape.front().getX(), shape.front().getY());
    fl_vertex(shape.back().getX(), shape.back().getY());
    fl_end_line();

    if (ship->getVelocity().magnitude() > 0.1) 
    {
        fl_color(FL_RED);
        fl_begin_line();
        fl_vertex(shape[2].getX(), shape[2].getY());
        fl_vertex(shape[2].getX() - ship->getSize() / 3 * cos(ship->getAngle() * M_PI / 180.0),
            shape[2].getY() - ship->getSize() / 3 * sin(ship->getAngle() * M_PI / 180.0));
        fl_end_line();
    }
}

void GameView::drawAsteroids() const 
{
    for (const auto& asteroid : m_model->getAsteroids()) 
    {
        if (!asteroid->isActive()) continue;

        auto shape = asteroid->getShape();
        fl_color(FL_WHITE);
        fl_begin_line();
        for (auto& point : shape) 
        {
            fl_vertex(point.getX(), point.getY());
        }
        fl_end_line();
        fl_begin_line();
        fl_vertex(shape.front().getX(), shape.front().getY());
        fl_vertex(shape.back().getX(), shape.back().getY());
        fl_end_line();
    }
}

void GameView::drawBullets() const 
{
    for (const auto& bullet : m_model->getBullets()) 
    {
        if (!bullet->isActive()) continue;

        fl_color(FL_WHITE);
        fl_circle(bullet->getPosition().getX(), bullet->getPosition().getY(), bullet->getSize());
    }
}

void GameView::drawHUD() const 
{
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA, 16);

    char scoreStr[50];
    snprintf(scoreStr, sizeof(scoreStr), "Score: %d", m_model->getScore());
    fl_draw(scoreStr, 10, 20);

    if (!m_model->getGameOver()) 
    {
        const Ship* ship = m_model->getShip();
        char livesStr[50];
        snprintf(livesStr, sizeof(livesStr), "Lives: %d", ship->getLives());
        fl_draw(livesStr, 10, 40);
    }
}

int GameView::handle(int event) 
{
    GameController* controller = static_cast<GameController*>(user_data());

    switch (event) 
    {
    case FL_KEYDOWN:
        controller->handleKeyDown(Fl::event_key());
        return 1;
    case FL_KEYUP:
        controller->handleKeyUp(Fl::event_key());
        return 1;
    default:
        return Fl_Double_Window::handle(event);
    }
}
