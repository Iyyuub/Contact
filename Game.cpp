#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->enemySpawnTimerMax = 100.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->MaxEnemies = 1;
	this->xSquares = 10;
	this->ySquares = 10;
	this->Start =std::make_pair(2, 4);
	this->xFinish = 3;
	this->yFinish = 7;


}

void Game::initWindow()
{
	this->videoMode.height = 480;
	this->videoMode.width = 480;
	this->window = new sf::RenderWindow(this->videoMode, "Contact", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(this->window->getSize().x/10, this->window->getSize().y / 10));
	this->enemy.setFillColor(sf::Color::Blue);
	this->enemy.setOutlineThickness(2.f);
}

void Game::initMap()
{


	//Init Map Square object
	this->mapSqr.setSize(sf::Vector2f(this->window->getSize().x / this->xSquares, this->window->getSize().y / this->ySquares));
	this->mapSqr.setOutlineColor(sf::Color::Black);
	this->mapSqr.setOutlineThickness(1.f);

	//Init Starting position
	this->blueSqr.setPosition(this->Start.first * this->mapSqr.getSize().x, this->Start.second * this->mapSqr.getSize().y);
	this->blueSqr.setSize(sf::Vector2f(this->window->getSize().x / 10, this->window->getSize().y / 10));
	this->blueSqr.setFillColor(sf::Color::Blue);
	this->blueSqr.setOutlineColor(sf::Color::Transparent);
	this->blueSqr.setOutlineThickness(1.f);

	//Filling the map
	std::pair <sf::RectangleShape, int> temp;
	for (int i = 0; i < this->xSquares; i++) {
		for (int j = 0; j < this->ySquares; j++) {
			this->mapSqr.setPosition(
				static_cast<float>( i  * this->mapSqr.getSize().x),
				static_cast<float>( j  * this->mapSqr.getSize().y)
			);
			
			//Black Squares random
			if (rand()%4) {
				if (i == this->xFinish && j == this->yFinish) {
					this->mapSqr.setFillColor(sf::Color::Red);
					temp = std::make_pair(this->mapSqr, 2);
				}
				else {
					this->mapSqr.setFillColor(sf::Color::White);
					temp = std::make_pair(this->mapSqr, 0);
				}
			}
			else{
				this->mapSqr.setFillColor(sf::Color::Black);
				temp = std::make_pair(this->mapSqr, 1);
			}
			this->map.push_back(temp);

			//Add map square

		}
	}
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	//this->initEnemies();
	this->initMap();



}

Game::~Game()
{
	delete this->window;
}

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::update()
{
	this->pollEvents();
	this->updateMousePositions();
	//this->updateEnemies();
	//this->updateMap();
	this->updateMove();
}




void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->evt))
	{
		switch (this->evt.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			this->updateMove();
			break;

		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	if (this->enemies.size() < this->MaxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}
	
	//Move enemies
	for (auto& e : this->enemies)
	{
		e.move(0.f, 1.f);
	}
}

void Game::updateMove()
{

	switch (this->evt.key.code)
	{
	case sf::Keyboard::Down:
		if (this->Start.second < this->ySquares - 1) {
			if (this->map.begin()[this->Start.first * this->xSquares + this->Start.second+1 ].second==0) {
				this->blueSqr.move(0, this->blueSqr.getSize().y);
				this->Start.second++;
			}
		}
		break;
	case sf::Keyboard::Up:
		if (this->Start.second > 0) {
			if (this->map.begin()[this->Start.first * this->xSquares + this->Start.second-1 ].second==0) {
				this->blueSqr.move(0, -this->blueSqr.getSize().y);
				this->Start.second--;
			}
		}

		break;
	case sf::Keyboard::Left:
		if (this->Start.first > 0) {
			if (this->map.begin()[(this->Start.first - 1) * this->ySquares + this->Start.second ].second == 0) {
				this->blueSqr.move(-this->blueSqr.getSize().x, 0);
				this->Start.first--;
			}
		}
		break;
	case sf::Keyboard::Right:
		if (this->Start.first < this->xSquares - 1) {
			if (this->map.begin()[(this->Start.first+1)* this->ySquares + this->Start.second ].second==0) {
			this->blueSqr.move(this->blueSqr.getSize().x, 0);
			this->Start.first++;
			}
		}
		break;
	}

}

void Game::updateMap()
{

}

void Game::renderEnemies()
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::renderMap()
{
	for (auto& sqr : this->map)
	{
		this->window->draw(sqr.first);
	}
}

void Game::renderMove()
{
	this->window->draw(this->blueSqr);
}

void Game::spawnEnemies()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
		);
	this->enemy.setFillColor(sf::Color::Blue);

	//Spawn Enemy
	this->enemies.push_back(this->enemy);
}

void Game::render()
{
	this->window->clear();

	//Draw game objects
	this->renderMap();
	//this->renderEnemies();
	this->renderMove();
	this->window->display();
}
