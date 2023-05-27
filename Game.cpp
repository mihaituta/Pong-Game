#include "Game.h"
#include <time.h>

Game::Game() : window(sf::VideoMode(800, 600), "Pong Game", sf::Style::Titlebar | sf::Style::Close),
playerPaddle(10, window.getSize().y / 2),
enemyPaddle(window.getSize().x - 10 - playerPaddle.getShape().getSize().x, window.getSize().y / 2),
ball(window.getSize().x / 2, window.getSize().y / 2),
playerScore(0),
enemyScore(0) {}

bool Game::isRunning() {
	return window.isOpen();
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		// Handle keyboard events
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::W) {
				playerPaddle.moveUp();
			}
			if (event.key.code == sf::Keyboard::S) {
				playerPaddle.moveDown();
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S) {
				playerPaddle.stop();
			}
		}
	}
}

void Game::update(float deltaTime) {
	playerPaddle.update(deltaTime, window.getSize().y);
	ball.update(deltaTime);
	enemyPaddle.updateAI(deltaTime, ball);

	handlePaddleCollisions();
	handleBallCollisions();

	updateScoreText();
}

// Handle collisions between the ball and player/enemy paddles
void Game::handlePaddleCollisions() {

	// Check if the bounding rectangle of the ball intersects with the bounding rectangle of the player paddle
	if (ball.getShape().getGlobalBounds().intersects(playerPaddle.getShape().getGlobalBounds())) {
		ball.reverseXVelocity();
		// Move the ball slightly to the right (away from) of the player paddle to prevent immediate collision with the paddle
		ball.getShape().setPosition(playerPaddle.getShape().getPosition().x + playerPaddle.getShape().getSize().x,
			ball.getShape().getPosition().y);
	}
	if (ball.getShape().getGlobalBounds().intersects(enemyPaddle.getShape().getGlobalBounds())) {
		ball.reverseXVelocity();
		// Move the ball slightly to the left (away from) of the enemy paddle to prevent immediate collision with the paddle
		ball.getShape().setPosition(enemyPaddle.getShape().getPosition().x - ball.getShape().getRadius() * 2,
			ball.getShape().getPosition().y);
	}
}

// Handle collisions between the ball and window boundaries
void Game::handleBallCollisions() {
	// Check if the ball hits the left boundary of the window and reverses the velocity
	if (ball.getShape().getPosition().x <= 0) {
		ball.reverseXVelocity();
		enemyScore++;
	}

	// Check if the ball hits the right boundary of the window and reverses the velocity
	if (ball.getShape().getPosition().x >= window.getSize().x - ball.getShape().getRadius() * 2) {
		ball.reverseXVelocity();
		playerScore++;
	}
	// Reverse the ball's vertical velocity when it hits the top or bottom of the window
	if (ball.getShape().getPosition().y <= 0 || ball.getShape().getPosition().y >= window.getSize().y - ball.getShape().getRadius() * 2) {
		ball.reverseYVelocity();
	}
}

void Game::updateScoreText() {
	playerScoreText.setString("Player: " + std::to_string(playerScore));
	enemyScoreText.setString("Enemy: " + std::to_string(enemyScore));

	playerScoreText.setPosition(10, 10);
	enemyScoreText.setPosition(window.getSize().x - enemyScoreText.getLocalBounds().width - 10, 10);
}

void Game::render() {
	window.clear(sf::Color::Black);

	window.draw(playerPaddle.getShape());
	window.draw(enemyPaddle.getShape());
	window.draw(ball.getShape());
	window.draw(playerScoreText);
	window.draw(enemyScoreText);

	window.display();
}

void Game::run() {
	// Load font
	if (!font.loadFromFile("arial.ttf")) {
		// Handle font loading error
	}

	playerScoreText.setFont(font);
	playerScoreText.setCharacterSize(30);
	playerScoreText.setFillColor(sf::Color::White);

	enemyScoreText.setFont(font);
	enemyScoreText.setCharacterSize(30);
	enemyScoreText.setFillColor(sf::Color::White);

	sf::Clock clock;
	while (isRunning()) {
		processEvents();

		sf::Time deltaTime = clock.restart();

		update(deltaTime.asSeconds());

		render();
	}
}