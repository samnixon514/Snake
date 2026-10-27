#include "Game.h"

Game::Game() : eatSound(eatBuffer), correctSound(correctBuffer) // constructor
{
	score = 0;

	currentState = COLLECTING_FIRST;

	firstOperand = 0;

	secondOperand = 0;

	correctAnswer = 0;

	font.openFromFile("arial.ttf");

	correctCount = 0;

	currentGameState = GAME_PLAYING;

	eatBuffer.loadFromFile("EatingFood.wav");

	correctBuffer.loadFromFile("CorrectFood.wav");

	eatSound.setBuffer(eatBuffer);

	correctSound.setBuffer(correctBuffer);

	highScore = 0;

	loadHighScore();
}

void Game::generateQuestion() // generates numbers and creates the question
{
	correctAnswer = firstOperand * secondOperand;
	
	currentState = AWAITING_ANSWER;
}

void Game::display(sf::RenderWindow& window) // creating the question and making it appear on the screen
{

	sf::Text text(font);
	
	text.setCharacterSize(18);

	text.setOutlineThickness(1.f);

	text.setOutlineColor(sf::Color::Black);
	
	text.setFillColor(sf::Color::White);
	
	text.setPosition({ 270.f, 5.f });

	std::string question = std::to_string(firstOperand) + " x " +

		std::to_string(secondOperand) + " = ?";

	if (currentState == COLLECTING_FIRST)
		text.setString("Eat The First Number You Want");

	else if (currentState == COLLECTING_SECOND)
		text.setString("Eat The Second Number You Want");

	else if (currentState == AWAITING_ANSWER)
		text.setString(question);

	float textX = (800 / 2) - (text.getLocalBounds().size.x / 2);
	
	text.setPosition({ textX, text.getPosition().y });

	window.draw(text);

	sf::Text scoreText(font);

	scoreText.setCharacterSize(18);

	scoreText.setOutlineThickness(1.f);

	scoreText.setOutlineColor(sf::Color::Black);

	scoreText.setFillColor(sf::Color::White);

	scoreText.setPosition({ 680.f, 5.f });

	scoreText.setString("Score: " + std::to_string(score));

	window.draw(scoreText);

	sf::Text multiplierText(font);

	multiplierText.setOutlineThickness(1.f);

	multiplierText.setOutlineColor(sf::Color::Black);

	multiplierText.setCharacterSize(18);

	multiplierText.setFillColor(sf::Color::White);

	multiplierText.setPosition({ 650.f, 5.f });

	if (correctCount >= 10)
	{
		multiplierText.setString("x3");
	}

	else if (correctCount >= 5)
	{
		multiplierText.setString("x2");
	}

	else
	{
		multiplierText.setString("x1");
	}

	window.draw(multiplierText);

	sf::Text HighScoreText(font);

	HighScoreText.setCharacterSize(18);

	HighScoreText.setOutlineThickness(1.f);

	HighScoreText.setOutlineColor(sf::Color::Black);

	HighScoreText.setFillColor(sf::Color::White);

	HighScoreText.setPosition({ 50.f, 5.f });

	HighScoreText.setString("High Score: " + std::to_string(highScore));

	window.draw(HighScoreText);
}

void Game::eatsFood(int foodValue) // generating question states due to operand being eaten
{
	if (currentState == COLLECTING_FIRST)
	{
		firstOperand = foodValue;
		currentState = COLLECTING_SECOND;
		eatSound.play();
	}

	else if (currentState == COLLECTING_SECOND)
	{
		secondOperand = foodValue;
		generateQuestion();
		eatSound.play();
	}
}

int Game::getCorrectAnswer() // sending the info on correct answer
{
	return correctAnswer;
}

Game::QuestionState Game::getState() // gives the state of the game (enums)
{
	return currentState;
}

bool Game::checkAnswer(int Answer) // checking the correct answer and score multiplier system
{
	if (Answer == correctAnswer)
	{

		correctCount++;

		if (correctCount >= 11)
		{
			score += 300;
		}

		else if (correctCount >= 6)
		{
			score += 200;
		}

		else
		{
			score += 100;
		}

		currentState = COLLECTING_FIRST;

		correctSound.play();

		return true;
	}
	else
	{
		score -= 100;

		currentState = COLLECTING_FIRST;

		correctCount = 0;

		eatSound.play();

		return false;
	}
}

void Game::reset() // resets the game and makes everything go back to 0 or its original state
{
	score = 0;

	currentState = COLLECTING_FIRST;

	firstOperand = 0;

	secondOperand = 0;

	correctAnswer = 0;

	correctCount = 0;

}

int Game::getScore() // gives the score amount
{
	return score;
}

void Game::drawGameOver(sf::RenderWindow& window)
{
	sf::Text gameOverText(font); // game over text

	gameOverText.setCharacterSize(35);

	gameOverText.setOutlineThickness(1.f);

	gameOverText.setOutlineColor(sf::Color::Black);

	gameOverText.setFillColor(sf::Color::White);

	gameOverText.setString("Game Over");

	float gameOverX = (800 / 2) - (gameOverText.getLocalBounds().size.x / 2) - gameOverText.getLocalBounds().position.x;

	gameOverText.setPosition(sf::Vector2f(gameOverX, 100.f ));

	window.draw(gameOverText);

	sf::Text scoreText(font); // final score text

	scoreText.setCharacterSize(35.f);

	scoreText.setOutlineThickness(1.f);

	scoreText.setOutlineColor(sf::Color::Black);

	scoreText.setFillColor(sf::Color::White);

	scoreText.setString("Your final score was: " + std::to_string(score));

	float scoreTextX = (800 / 2) - (scoreText.getLocalBounds().size.x / 2) - scoreText.getLocalBounds().position.x;

	scoreText.setPosition(sf::Vector2f(scoreTextX, 250.f ));

	window.draw(scoreText);

	sf::Text restartPromptText(font); // restart Prompt

	restartPromptText.setCharacterSize(35.f);

	restartPromptText.setOutlineThickness(1.f);

	restartPromptText.setOutlineColor(sf::Color::Black);

	restartPromptText.setFillColor(sf::Color::White);

	restartPromptText.setString("Press Space To Restart");

	float restartPromptX = (800 / 2) - (restartPromptText.getLocalBounds().size.x / 2) - restartPromptText.getLocalBounds().position.x;

	restartPromptText.setPosition(sf::Vector2f (restartPromptX, 400.f ));

	window.draw(restartPromptText);
}

void Game::loadHighScore()
{
	std::ifstream file("highscore.txt");

	if (file.is_open())
	{
		file >> highScore;
	}
}

void Game::saveHighScore()
{
	std::ofstream file("highscore.txt");

	if (file.is_open())
	{
		file << highScore;
	}
}

void Game::updateHighScore()
{
	if (score > highScore)
	{
		highScore = score;

		saveHighScore();
	}
}