#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Snake
{

private:

	enum direction { UP, DOWN, LEFT, RIGHT };

	direction currentDirection = RIGHT;

	int cellSize = 20;

	std::vector<sf::Vector2i> body;

	direction newDirection = RIGHT;

public:
	Snake();
	
	void update();
	
	void draw(sf::RenderWindow& window);
	
	void handleInput();

	bool checkCollision();

	void reset();
	
	sf::Vector2i getHeadPosition();

	void grow();

	void shrink();

	int getBodySize();

std::vector<sf::Vector2i> getBody();

};

