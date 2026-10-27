#include "Snake.h"
#include <SFML/Window/Keyboard.hpp>

Snake::Snake()
{
	cellSize = 20;

	newDirection = RIGHT;

	sf::Vector2i startPosition(10, 10);

	body.push_back(sf::Vector2i(startPosition));
	
	body.push_back(sf::Vector2i(9, 10));
	
	body.push_back(sf::Vector2i(8, 10));

}
void Snake::update() // Updates the snake 
{
	sf::Vector2i newHead = body[0];

	switch (newDirection)
	{
		case UP:
			
			newHead.y -= 1;

			break;
		
		case DOWN:
			
			newHead.y += 1;
			
			break;
		
		case LEFT:
			
			newHead.x -= 1;
			
			break;
		
		
		case RIGHT:
			
			newHead.x += 1;
			
			break;
	}
	body.insert(body.begin(), newHead);

	body.pop_back();

	currentDirection = newDirection;
}

void Snake::draw(sf::RenderWindow& window) // Draws the snake 
{
	sf::RectangleShape SnakeHead(sf::Vector2f(20, 20));

	SnakeHead.setFillColor(sf::Color::Cyan);

	SnakeHead.setOutlineThickness(1.f);

	SnakeHead.setOutlineColor(sf::Color::White);

	for (auto& segment : body)
	{

		SnakeHead.setPosition({ (float)(segment.x * cellSize), (float)(segment.y * cellSize) });
		
		window.draw(SnakeHead);
	}
}

void Snake::handleInput() // Handles directional input
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
	{
		if (currentDirection != direction::LEFT)
		{
			newDirection = direction::RIGHT;
		}
	
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (currentDirection != direction::RIGHT)
		{
			newDirection = direction::LEFT;
		}
		
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (currentDirection != direction::DOWN)
		{
			newDirection = direction::UP;
		}
		
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (currentDirection != direction::UP)
		{
			newDirection = direction::DOWN;
		}
		
	}

}

bool Snake::checkCollision() // Wall and self collision check
{
	if (body[0].x < 0 || body[0].x > 39 || body[0].y > 29 || body[0].y < 0) {

		return true;
	}
	
	for (int i = 1; i < body.size(); i++)
	{
		if (body[0] == body[i])
			{
			return true;
			}
	}
	return false;
}

void Snake::reset() // function to reset the snake back to its starting position
{
	body.clear();

	body.push_back(sf::Vector2i(10, 10));
	
	body.push_back(sf::Vector2i(9, 10));
	
	body.push_back(sf::Vector2i(8, 10));

	newDirection = direction::RIGHT;
}

sf::Vector2i Snake::getHeadPosition()
{
	return body[0];
}

void Snake::grow()
{
	body.push_back(body.back());
}

void Snake::shrink()
{
	if (body.size() >= 1)
		body.pop_back();
}

int Snake::getBodySize()
{
	return body.size();
}

std::vector<sf::Vector2i> Snake::getBody()
{
	return body;
}