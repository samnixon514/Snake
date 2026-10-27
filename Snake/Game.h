#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

class Game
{

private:
	int firstOperand;

	int secondOperand;

	int correctAnswer;

	int score;

	int correctCount;

	int highScore;

	sf::Font font;

	sf::SoundBuffer eatBuffer;

	sf::SoundBuffer correctBuffer;

	sf::Sound eatSound;

	sf::Sound correctSound;

public:

	Game();

	enum QuestionState { COLLECTING_FIRST, COLLECTING_SECOND, AWAITING_ANSWER };
	
	enum GameStates{ GAME_PLAYING, GAME_OVER };

	QuestionState currentState;

	GameStates currentGameState;

	void generateQuestion();

	void display(sf::RenderWindow& window);

	void drawGameOver(sf::RenderWindow& window);

	bool checkAnswer(int answer);

	int getScore();

	void eatsFood(int foodValue);

	int getCorrectAnswer();

	QuestionState getState();

	void reset();

	void loadHighScore();

	void saveHighScore();

	void updateHighScore();
};