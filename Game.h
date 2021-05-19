#pragma once

#include <iostream>
#include <vector>
#include <ctime>


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Game engine class
*/
class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event evt;

	//Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int MaxEnemies;

	//bool mapUpdate;

	//Map
	std::vector< std::pair <sf::RectangleShape, int>> map;
	sf::RectangleShape mapSqr;
	sf::RectangleShape blueSqr;
	int xSquares, ySquares;
	std::pair<int,int> Start;
	int xFinish, yFinish;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	
	//Private function
	void initVariables();
	void initWindow();
	void initEnemies();
	void initMap();

public:
	//Constructors, Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool getWindowIsOpen() const;

	//Funtions
	void spawnEnemies();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void updateMove();
	void updateMap();
	void update();
	void renderEnemies();
	void renderMap();
	void renderMove();
	void render();
};

