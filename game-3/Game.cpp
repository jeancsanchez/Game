#include "Game.h"

Game::Game() {
  this->initializeVariables();
  this->initWindow();
  this->initHero();
  this->initEnemies();
}

Game::~Game() { delete this->_window; }

const bool Game::isRunning() const { return this->_window->isOpen(); }

void Game::update() {
  this->updateEvents();
  this->updateMousePosition();
  this->updateHero();
  this->updateEnemies();
}

void Game::render() {
  this->_window->clear();
  this->renderHero();
  this->renderEnemies();
  this->_window->display();
}

void Game::initializeVariables() {
  this->_window = nullptr;
  this->points = 0;
  this->enemySpawnTimer = 0.f;
  this->enemySpawnTimerMax = 1000.f;
  this->maxEnemies = 100;
}

void Game::initWindow() {
  this->_window =
      new sf::RenderWindow(sf::VideoMode(300, 500), "Hello Wolrd Game!",
                           sf::Style::Titlebar | sf::Style::Close);
  this->_window->setFramerateLimit(0);
}

void Game::initHero() {
  // this->hero = sf::CircleShape(30);
  // this->hero.setPosition(sf::Vector2f(10.0f, 10.0f));
  // this->hero.setScale(sf::Vector2f(0.5f, 0.5f));
  // this->hero.setFillColor(sf::Color::White);

  if (!this->heroTexture.loadFromFile("assets/hero-x.png")) {
    std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE"
              << "\n";
  }

  this->hero.setTexture(this->heroTexture);
  this->hero.setScale(0.5f, 0.6f);
  this->hero.setPosition(this->_window->getSize().x /2 , this->_window->getSize().y - this->hero.getGlobalBounds().height);
}

void Game::initEnemies() {
  if (!this->enemyTexture.loadFromFile("assets/rock.png")) {
    std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE"
              << "\n";
  }

  this->enemy.setTexture(this->enemyTexture);
  this->enemy.setTextureRect(sf::IntRect(0, 0, 33, 33));
  this->enemy.setScale(1.3f, 1.3f);
}

void Game::updateMousePosition() {
  this->mousePosition = sf::Mouse::getPosition(*this->_window);
  this->mousePositionInWindow =
      this->_window->mapPixelToCoords(this->mousePosition);
}

void Game::updateEvents() {
  while (this->_window->pollEvent(this->ev)) {
    switch (ev.type) {
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

void Game::updateHero() {
  int speed = 1.f;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    this->hero.move(-0.1f, 0.f);
  }
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      this->hero.move(0.1f, 0.f);
  }
}

void Game::updateEnemies() {
  if (this->enemies.size() < this->maxEnemies) {
    if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
      this->spawnEnemy();
      this->enemySpawnTimer = 0.f;
    } else {
      this->enemySpawnTimer += 1.f;
    }
  }

  for (int i = 0; i < this->enemies.size(); i++) {
    this->enemies[i].move(0.f, 0.2f);

    if (this->enemies[i].getGlobalBounds().intersects(
            this->hero.getGlobalBounds())) {
      this->enemies.erase(this->enemies.begin() + i);
    }
  }
}

void Game::renderHero() { this->_window->draw(this->hero); }

void Game::renderEnemies() {
  for (auto &e : this->enemies) {
    this->_window->draw(e);
  }
}

void Game::spawnEnemy() {
  int randomX = rand() % static_cast<int>((this->_window->getSize().x));
  int enemyX = this->enemy.getTextureRect().width;
  int newPosition = randomX - enemyX;

  this->enemy.setPosition(newPosition, 0.f);
  this->enemies.push_back(this->enemy);
}
