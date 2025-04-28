#include "GameController.h"

GameController::GameController(int width, int height)
    : gameRunning(false), fireCooldown(0), asteroidSpawnTimer(0) {
    std::srand(std::time(nullptr));

    mainWindow = new Fl_Window(width, height, "Asteroids Game");
    mainWindow->color(FL_BLACK);
    mainMenu = new MainMenuView(width, height);

    mainMenu->SetOnNewGame([this]() { StartNewGame(); });
    mainMenu->SetOnAbout([this]() { ShowAbout(); });
    mainMenu->SetOnExit([this]() { ExitGame(); });

    shipModel = new SpaceShipModel(0, 0);
    shipView = new SpaceShipView(shipModel, 0, 0, width, height);
}

GameController::~GameController() {
    delete mainMenu;
    delete shipView;
    delete shipModel;
    delete mainWindow;
}

void GameController::Run() {
    mainMenu->Show();
    mainWindow->end();
    mainWindow->show();
    
    Fl::add_timeout(1.0 / 60.0, TimerCallback, this);
}

void GameController::StartNewGame() {
    mainMenu->Hide();
    gameRunning = true;
    score = 0;

    shipModel->SetPosition(0, 0);
    shipModel->SetVelocity(0, 0);

    bullets.clear();
    bulletViews.clear();
    asteroids.clear();
    asteroidViews.clear();

    fireCooldown = 0;
    asteroidSpawnTimer = 0;

    shipView->Show();

    mainWindow->take_focus();

    //mainWindow->redraw();
}

void GameController::ShowAbout() {
    fl_message("Asteroids Game\nВерсия 1.0\nАвтор: Барышев Григорий");
}

void GameController::ExitGame() {
    mainWindow->hide();
    GameController::~GameController();
}

void GameController::TimerCallback(void* data) {
    GameController* controller = static_cast<GameController*>(data);

    if (controller->gameRunning) {
        controller->ProcessInput();
        controller->UpdateGame();
        controller->CheckCollisions();
        controller->SpawnAsteroids();
    }

    Fl::repeat_timeout(1.0 / 60.0, TimerCallback, data);
}

void GameController::ProcessInput() {
    if (Fl::event_key(FL_Left)) {
        shipModel->RotateLeft();
    }
    if (Fl::event_key(FL_Right)) {
        shipModel->RotateRight();
    }
    if (Fl::event_key(FL_Up)) {
        shipModel->Accelerate();
    }
    if (Fl::event_key(FL_Down)) {
        shipModel->Decelerate();
    }

    // Автоматическая стрельба
    if (fireCooldown <= 0) {
        bullets.push_back(std::make_unique<BulletModel>(
            shipModel->GetX(),
            shipModel->GetY(),
            shipModel->GetAngle()
        ));

        bulletViews.push_back(std::make_unique<BulletView>(
            bullets.back().get(),
            0, 0,
            mainWindow->w(), mainWindow->h()
        ));

        bulletViews.back()->Show();

        fireCooldown = 10;
    }
    else {
        fireCooldown -= 2;
    }
}

void GameController::UpdateGame() {
    shipModel->Update();
    shipView->Draw();

    for (size_t i = 0; i < bullets.size(); ) {
        bullets[i]->Update();
        bulletViews[i]->Draw();

        if (bullets[i]->IsExpired()) {
            bulletViews[i]->Hide();
            bullets.erase(bullets.begin() + i);
            bulletViews.erase(bulletViews.begin() + i);
        }
        else {
            ++i;
        }
    }

    for (size_t i = 0; i < asteroids.size(); ++i) {
        asteroids[i]->Update();
        asteroidViews[i]->Draw();
    }

    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA, 16);
    fl_draw(("Score: " + std::to_string(score)).c_str(), 10, 20);

    mainWindow->redraw();
}

void GameController::SpawnAsteroids() {
    if (asteroidSpawnTimer <= 0) {
        int side = rand() % 4; // 0 - верх, 1 - право, 2 - низ, 3 - лево
        float x = 0, y = 0;

        switch (side) {
        case 0: // Верх
            x = (rand() % mainWindow->w()) - mainWindow->w() / 2;
            y = -mainWindow->h() / 2 - 50;
            break;
        case 1: // Право
            x = mainWindow->w() / 2 + 50;
            y = (rand() % mainWindow->h()) - mainWindow->h() / 2;
            break;
        case 2: // Низ
            x = (rand() % mainWindow->w()) - mainWindow->w() / 2;
            y = mainWindow->h() / 2 + 50;
            break;
        case 3: // Лево
            x = -mainWindow->w() / 2 - 50;
            y = (rand() % mainWindow->h()) - mainWindow->h() / 2;
            break;
        }

        asteroids.push_back(std::make_unique<AsteroidModel>(
            x, y,
            AsteroidModel::LARGE
        ));

        asteroidViews.push_back(std::make_unique<AsteroidView>(
            asteroids.back().get(),
            0, 0,
            mainWindow->w(), mainWindow->h()
        ));

        asteroidViews.back()->Show();

        asteroidSpawnTimer = 120;
    }
    else {
        asteroidSpawnTimer -= 5;
    }
}

void GameController::CheckCollisions() {
    for (size_t i = 0; i < bullets.size(); ) {
        bool bulletHit = false;

        for (size_t j = 0; j < asteroids.size(); ) {
            if (asteroids[j]->CheckCollisions(
                bullets[i]->GetX(),
                bullets[i]->GetY(),
                bullets[i]->GetCollisionRadius())) {

                switch (asteroids[j]->GetSize()) {
                case AsteroidModel::LARGE: score += 20; break;
                case AsteroidModel::MEDIUM: score += 50; break;
                case AsteroidModel::SMALL: score += 100; break;
                }

                AsteroidModel::Size newSize;
                switch (asteroids[j]->GetSize()) {
                case AsteroidModel::LARGE:
                    newSize = AsteroidModel::MEDIUM;
                    break;
                case AsteroidModel::MEDIUM:
                    newSize = AsteroidModel::SMALL;
                    break;
                case AsteroidModel::SMALL:
                    newSize = AsteroidModel::SMALL; // Не разбиваем дальше
                    break;
                }

                if (asteroids[j]->GetSize() != AsteroidModel::SMALL) {
                    for (int k = 0; k < 3; k++) {
                        asteroids.push_back(std::make_unique<AsteroidModel>(
                            asteroids[j]->GetX(),
                            asteroids[j]->GetY(),
                            newSize
                        ));

                        asteroidViews.push_back(std::make_unique<AsteroidView>(
                            asteroids.back().get(),
                            0, 0,
                            mainWindow->w(), mainWindow->h()
                        ));

                        asteroidViews.back()->Show();
                    }
                }

                asteroidViews[j]->Hide();
                asteroids.erase(asteroids.begin() + j);
                asteroidViews.erase(asteroidViews.begin() + j);

                bulletHit = true;
                break;
            }
            else {
                j++;
            }
        }

        if (bulletHit) {
            bulletViews[i]->Hide();
            bullets.erase(bullets.begin() + i);
            bulletViews.erase(bulletViews.begin() + i);
        }
        else {
            i++;
        }
    }

    for (size_t j = 0; j < asteroids.size(); ) {
        if (asteroids[j]->CheckCollisions(
            shipModel->GetX(),
            shipModel->GetY(),
            shipModel->GetCollisionRadius())) {

            gameRunning = false;
            mainMenu->Show();
            shipView->Hide();

            bullets.clear();
            bulletViews.clear();
            asteroids.clear();
            asteroidViews.clear();

            fl_message("Game Over! Your ship has destroyed.");
            break;
        }
        else {
            j++;
        }
    }

    float halfWidth = mainWindow->w() / 2.0f;
    float halfHeight = mainWindow->h() / 2.0f;

    if (shipModel->GetX() < -halfWidth) shipModel->SetPosition(halfWidth, shipModel->GetY());
    if (shipModel->GetX() > halfWidth) shipModel->SetPosition(-halfWidth, shipModel->GetY());
    if (shipModel->GetY() < -halfHeight) shipModel->SetPosition(shipModel->GetX(), halfHeight);
    if (shipModel->GetY() > halfHeight) shipModel->SetPosition(shipModel->GetX(), -halfHeight);

    for (size_t i = 0; i < bullets.size(); ) {
        if (bullets[i]->GetX() < -halfWidth || bullets[i]->GetX() > halfWidth ||
            bullets[i]->GetY() < -halfHeight || bullets[i]->GetY() > halfHeight) {
            bulletViews[i]->Hide();
            bullets.erase(bullets.begin() + i);
            bulletViews.erase(bulletViews.begin() + i);
        }
        else {
            i++;
        }
    }

    for (size_t i = 0; i < asteroids.size(); ) {
        if (asteroids[i]->GetX() < -halfWidth - 50 || asteroids[i]->GetX() > halfWidth + 50 ||
            asteroids[i]->GetY() < -halfHeight - 50 || asteroids[i]->GetY() > halfHeight + 50) {
            asteroidViews[i]->Hide();
            asteroids.erase(asteroids.begin() + i);
            asteroidViews.erase(asteroidViews.begin() + i);
        }
        else {
            i++;
        }
    }
}

void GameController::SplitAsteroid(size_t index) {
    AsteroidModel::Size currentSize = asteroids[index]->GetSize();
    if (currentSize == AsteroidModel::SMALL) return;

    AsteroidModel::Size newSize;
    switch (currentSize) {
    case AsteroidModel::LARGE: newSize = AsteroidModel::MEDIUM; break;
    case AsteroidModel::MEDIUM: newSize = AsteroidModel::SMALL; break;
    default: return;
    }

    // Создаем 2 новых астероида
    for (int i = 0; i < 2; i++) {
        float angle = rand() % 360;
        float speed = 1.0f + (rand() % 10) / 5.0f;

        asteroids.push_back(std::make_unique<AsteroidModel>(
            asteroids[index]->GetX(),
            asteroids[index]->GetY(),
            newSize
        ));

        float radians = angle * (M_PI / 180.0f);
        asteroids.back()->SetVelocity(
            std::sin(radians) * speed,
            -std::cos(radians) * speed
        );

        asteroidViews.push_back(std::make_unique<AsteroidView>(
            asteroids.back().get(),
            0, 0,
            mainWindow->w(), mainWindow->h()
        ));

        asteroidViews.back()->Show();
    }
}

void GameController::GameOver() {
    gameRunning = false;
    mainMenu->Show();
    shipView->Hide();

    bullets.clear(); // <- в модель
    bulletViews.clear(); // <- во view
    asteroids.clear();
    asteroidViews.clear();

    fl_message("Game Over! Your score: %d", score);
}

// Во View
void GameController::DrawHUD() {
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA_BOLD, 16);

    // Очки
    std::string scoreText = "Score: " + std::to_string(score);
    fl_draw(scoreText.c_str(), 10, 25);

    // Жизни
    //std::string livesText = "Lives: " + std::to_string(lives);
    //fl_draw(livesText.c_str(), mainWindow->w() - 80, 25);
}