// GameController.h
#pragma once
#include "MainMenuView.h"
#include "SpaceShipModel.h"
#include "SpaceShipView.h"
#include "BulletModel.h"
#include "BulletView.h"
#include "AsteroidModel.h"
#include "AsteroidView.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <vector>
#include <memory>
#include <string>
#include <FL/fl_message.H>
#include <ctime>

# define M_PI           3.14159265358979323846

class GameController {
private:
    Fl_Window* mainWindow;
    MainMenuView* mainMenu;

    SpaceShipModel* shipModel;
    SpaceShipView* shipView;

    std::vector<std::unique_ptr<BulletModel>> bullets;
    std::vector<std::unique_ptr<BulletView>> bulletViews;

    std::vector<std::unique_ptr<AsteroidModel>> asteroids;
    std::vector<std::unique_ptr<AsteroidView>> asteroidViews;

    bool gameRunning;
    int fireCooldown;
    int asteroidSpawnTimer;

    int score;

    void ProcessInput();
    void UpdateGame();
    void SpawnAsteroids();
    void CheckCollisions();

public:
    GameController(int width, int height);
    ~GameController();

    void Run();
    void StartNewGame();
    void ShowAbout();
    void ExitGame();

    static void TimerCallback(void* data);

    int GetScore() const { return score; }

    void GameOver();
    void SplitAsteroid(size_t index);
    void DrawHUD();
};