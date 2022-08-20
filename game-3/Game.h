#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <vector>

class Game {
private:
  sf::RenderWindow *_window;
  sf::Event ev;

  void initializeVariables();
  void initWindow();
  void initHero();
  void initEnemies();

public:
  // Constructors / Desctructors
  Game();
  virtual ~Game();

  // Game Objects
  std::vector<sf::RectangleShape> enemies;
  sf::RectangleShape enemy;
  sf::Sprite hero;
  sf::Texture heroTexture;
  sf::Vector2i mousePosition;
  sf::Vector2f mousePositionInWindow;

  int points;
  float enemySpawnTimer;
  float enemySpawnTimerMax;
  int maxEnemies;

  // Accessors
  const bool isRunning() const;

  // Functions
  void update();
  void render();

  void updateMousePosition();
  void updateEvents();

  void updateHero();
  void renderHero();

  void updateEnemies();
  void renderEnemies();
  void spawnEnemy();
};
