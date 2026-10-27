#include "Food.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

Food::Food() // constructor
{
	foodShape.setRadius(10.f);
	
	foodShape.setFillColor(sf::Color::Red);

	cellSize = 20;

	font.openFromFile("arial.ttf");

}
void Food::spawn(std::vector<sf::Vector2i> snakeBody, std::vector<sf::Vector2i> occupiedPosition) // spawning the food and checking the position of the snake so food cant spawn on same spot
{
	bool validPosition = false;

	while (!validPosition)
	{
		position.x = rand() % 40;

		position.y = rand() % 30;

		value = rand() % 10 + 1;

		validPosition = true;

		for (auto& segment : snakeBody)
			if (position == segment) validPosition = false;

		for (auto& pos : occupiedPosition)
			if (position == pos) validPosition = false;

	}

}

void Food::draw(sf::RenderWindow& window) // drawing the food on the grid and adding text onto it
{
	foodShape.setPosition({ (float)(position.x * cellSize), (float)(position.y * cellSize) });

	window.draw(foodShape);

	sf::Text foodText(font);

	foodText.setCharacterSize(15);

	foodText.setFillColor(sf::Color::Yellow);

	foodText.setStyle(sf::Text::Bold);

	foodText.setString(std::to_string(value));

	float textX = (float)(position.x * cellSize) + (foodShape.getRadius() - foodText.getLocalBounds().size.x / 2 - 1.f);

	float textY = (float)(position.y * cellSize) + (foodShape.getRadius() - foodText.getLocalBounds().size.y / 2 - 4.f);

	foodText.setPosition({ textX, textY });

	window.draw(foodText);
}

bool Food::isEaten(sf::Vector2i headPosition) // checking the headposition 
{
	if (headPosition == position)
		return true;

	return false;
}

int Food::getValue() // gets the value of food
{
	return value;
}

void Food::setValue(int newValue) // sets the value of food
{
	value = newValue;
}

sf::Vector2i Food::getPosition() // gets the position of food
{
	return position;
}