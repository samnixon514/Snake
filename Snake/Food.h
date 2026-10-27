#pragma once
#include <SFML/Graphics.hpp>

class Food
{
private:

	sf::Vector2i position;

	sf::CircleShape foodShape;

	int value;

	int cellSize = 20;

	sf::Font font;

public:

	Food();

	void draw(sf::RenderWindow& window);

	void spawn(std::vector<sf::Vector2i> snakeBody, std::vector<sf::Vector2i> occupiedPosition);

	bool isEaten(sf::Vector2i headPosition);

	int getValue();

	void setValue(int newValue);

	sf::Vector2i getPosition();
};

