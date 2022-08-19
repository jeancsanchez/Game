#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>


class Game
{
private	:
	sf::RenderWindow* _window;
	sf::Event ev;

	void initializeVariables();
	void initWindow();
	void initEnemies();
public:
	// Constructors / Desctructors
	Game();
	virtual ~Game();

	// Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	sf::Vector2i mousePosition;

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

	void updateEnemies();
	void renderEnemies();
	void spawnEnemy();
};

