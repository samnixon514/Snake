/*
    Snake - Start Project

    This project is set up to link to SFML (a library supporting 2D graphics, sound, user input and networing)
    There is a subdirectory in the project called SFML-3.0.0 containing SFML headers and libraries
    The project settings are configured to look for these files

    SFML reference: https://www.sfml-dev.org/documentation/3.0.0/
    SFML Tutorials: https://www.sfml-dev.org/tutorials/3.0/
*/

#include <SFML/Graphics.hpp>
#include <vector>
#include "Snake.h"
#include "Food.h"
#include <ctime>
#include "Game.h"

struct Particle
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float lifetime;
};

std::vector<Particle> particles;

void spawnParticles(sf::Vector2i position) // function to spawn particles as if the snake is actually eating the food
{
    for (int p = 0; p < 15; p++)
    {
        Particle particle;
       
        particle.position = sf::Vector2f(position.x * 20, position.y * 20);
        
        particle.velocity = sf::Vector2f((rand() % 200 - 100) / 100.f * 6.f, (rand() % 200 - 100) / 100.f * 3.f);
       
        particle.lifetime = 0.3f;
        
        particles.push_back(particle);
    }
}

int main()
{
    Snake snake;

    Game game;

    sf::Clock clock; // timer 

    srand(time(nullptr)); // makes the seed random every time 

    std::vector<Food> foods(3); // makes 3 food appear on screen

    for (int i = 0; i < foods.size(); i++) // food spawn and ensuring its not an occupied spot
    {
        std::vector<sf::Vector2i> occupiedPosition;
        for (int s = 0; s < i; s++)
        {
            occupiedPosition.push_back(foods[s].getPosition());
        }
        foods[i].spawn(snake.getBody(), occupiedPosition);
    }

    float timer = 0, delay = 0.1f; // snake move speed

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SnakeGameWindow"); // making window

    while (window.isOpen()) // game loop
    {
        float time = clock.restart().asSeconds();
        timer += time;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is < sf::Event::Closed>())
            {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>())
            {
                if (game.currentGameState == game.GameStates::GAME_OVER && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)
                {
                    snake.reset();

                    game.reset();

                    delay = 0.1f;

                    for (int i = 0; i < foods.size(); i++)
                    {
                        std::vector<sf::Vector2i> occupiedPosition;
                        for (int s = 0; s < i; s++)
                        {
                            occupiedPosition.push_back(foods[s].getPosition());
                        }
                        foods[i].spawn(snake.getBody(), occupiedPosition);
                    }

                    game.currentGameState = game.GameStates::GAME_PLAYING;
                }
            }
        }

        snake.handleInput(); // move key handler

        if (timer > delay)
        {
            timer = 0;

            snake.update(); // updates snake with push_backs

            if (snake.checkCollision()) // checks if the snake has wall or self collision
            {
                game.updateHighScore();

                game.currentGameState = game.GameStates::GAME_OVER;

               
            }
        }

        for (int i = 0; i < particles.size(); i++)
        {
            particles[i].lifetime -= time;

            particles[i].position += particles[i].velocity;

            if (particles[i].lifetime <= 0)
            {
                particles.erase(particles.begin() + i);

                    i--;
            }
        }
        
        window.clear(sf::Color(170, 215, 81)); // makes window a certain colour

        for (int row = 0; row < 600; row += 20)
        {
            for (int col = 0; col < 800; col += 20)
            {
                sf::RectangleShape cell(sf::Vector2f(20.f, 20.f));

                if ((row / 20 + col / 20) % 2 == 0)
                {
                    cell.setFillColor(sf::Color(170, 215, 81));
                }
                else
                {
                    cell.setFillColor(sf::Color(162, 209, 73));
                }

                cell.setPosition(sf::Vector2f(col, row));

                window.draw(cell);
            }
        }

        
        if (game.currentGameState == game.GameStates::GAME_PLAYING)
        {

            snake.draw(window); // draws snake 

            for (auto& food : foods)
            {
                food.draw(window); // draws food

                for (int i = 0; i < particles.size(); i++)
                {
                    sf::RectangleShape particle(sf::Vector2f(4.f, 4.f));

                    particle.setFillColor(sf::Color(255, 165, 0));

                    particle.setPosition(particles[i].position);

                    window.draw(particle);
                }

                if (food.isEaten(snake.getHeadPosition())) // checks if that the snake has eaten the correct answer on the right state it will shrink or grow 
                {
                    if (game.getState() == Game::QuestionState::AWAITING_ANSWER)
                    {
                        if (game.checkAnswer(food.getValue()))
                        {
                            snake.grow();

                            delay *= 0.95f;

                            spawnParticles(food.getPosition());
                        }
                        else
                        {
                            snake.shrink();

                            delay *= 1.05f;

                            spawnParticles(food.getPosition());
                        }
                    }
                    else
                    {
                        game.eatsFood(food.getValue());

                        spawnParticles(food.getPosition());
                    }

                    for (int i = 0; i < foods.size(); i++) // food spawn
                    {
                        std::vector<sf::Vector2i> occupiedPosition;
                        for (int s = 0; s < i; s++)
                        {
                            occupiedPosition.push_back(foods[s].getPosition());
                        }
                        foods[i].spawn(snake.getBody(), occupiedPosition);
                    }

                    if (delay < 0.05f)
                    {
                        delay = 0.05f;
                    }

                    if (game.getState() == Game::QuestionState::AWAITING_ANSWER) // makes one of the final foods on the awaiting answer state correct and the other 2 higher values similar
                    {
                        foods[0].setValue(game.getCorrectAnswer());

                        foods[1].setValue(game.getCorrectAnswer() + rand() % 15 + 1);

                        foods[2].setValue(game.getCorrectAnswer() - rand() % 15 + 1);
                    }
                    break;
                }
            }

            if (snake.getBodySize() <= 1) // if snake is 1 or 0 then it resets
            {
                snake.reset();

                game.reset();

                for (int i = 0; i < foods.size(); i++) // food spawn
                {
                    std::vector<sf::Vector2i> occupiedPosition;
                    for (int s = 0; s < i; s++)
                    {
                        occupiedPosition.push_back(foods[s].getPosition());
                    }
                    foods[i].spawn(snake.getBody(), occupiedPosition);
                }
            }

            game.display(window);
        }

        else
        {
            game.drawGameOver(window);
        }

        window.display(); // displays
    }
} 
