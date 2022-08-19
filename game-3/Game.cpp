#include "Game.h"

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
    this->initEnemies();
}

Game::~Game()
{
	delete this->_window;
}

void Game::initializeVariables()
{
    this->_window = nullptr;
    this->points = 0;
    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 1000.f;
    this->maxEnemies = 100;
}

void Game::initWindow()
{
    this->_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Hello Wolrd Game!", sf::Style::Titlebar | sf::Style::Close);
    this->_window->setFramerateLimit(0);
}

void Game::initEnemies()
{
    this->enemy.setPosition(sf::Vector2f(10.0f, 10.0f));
    this->enemy.setSize(sf::Vector2f(50.0f, 50.0f));
    this->enemy.setScale(sf::Vector2f(0.2f, 0.2f));
    this->enemy.setFillColor(sf::Color::Blue);
    this->enemy.setOutlineColor(sf::Color::White);
    this->enemy.setOutlineThickness(3.f);
}

const bool Game::isRunning() const
{
	return this->_window->isOpen();
}

void Game::update()
{
    this->updateEvents();
    this->updateMousePosition();
    this->updateEnemies();
}

void Game::render()
{
    this->_window->clear();
    this->renderEnemies();
    this->_window->display();
}

void Game::updateMousePosition()
{
    this->mousePosition = sf::Mouse::getPosition(*this->_window);
}

void Game::updateEvents()
{
    while (this->_window->pollEvent(this->ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            this->_window->close();
            break;

        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape) {
                this->_window->close();
                break;
            }
        }
    }
}

void Game::updateEnemies()
{
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
        {
            this->enemySpawnTimer += 1.f;
        }
    }


    for (auto& e : this->enemies)
    {
        e.move(0.f, 0.1f);
    }
}

void Game::renderEnemies()
{
    for (auto& e : this->enemies)
    {
        this->_window->draw(e);
    }
}

void Game::spawnEnemy()
{
    this->enemy.setPosition(
        rand() % static_cast<int>((this->_window->getSize().x) - this->enemy.getSize().x),
       0.f
    );

    // this->enemy.setFillColor(sf::Color::Magenta);
    this->enemies.push_back(this->enemy);
}
