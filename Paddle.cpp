#include "Paddle.h"
#include "Ball.h" 

Paddle::Paddle(float startX, float startY) {
	shape.setSize(sf::Vector2f(10, 80));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(startX, startY);
	velocity = sf::Vector2f(0, 0);
}

void Paddle::update(float deltaTime, int windowSize) {
	shape.move(velocity * deltaTime);

	// Adjust the paddle's position to stay within the window bounds
	if (shape.getPosition().y < 0) {
		shape.setPosition(shape.getPosition().x, 0);
	}
	if (shape.getPosition().y + shape.getSize().y > windowSize) {
		shape.setPosition(shape.getPosition().x, windowSize - shape.getSize().y);
	}
}

// Very simple AI for the enemy, adjust the paddle's movement based on the position of the ball
void Paddle::updateAI(float deltaTime, Ball& ball) {
	sf::Vector2f ballPosition = ball.getShape().getPosition();
	sf::Vector2f paddlePosition = shape.getPosition();

	if (ballPosition.y < paddlePosition.y + shape.getSize().y / 2) {
		moveUp();
	}
	else if (ballPosition.y > paddlePosition.y + shape.getSize().y / 2) {
		moveDown();
	}
	else {
		stop();
	}
	shape.move(velocity * deltaTime);
}

void Paddle::moveUp() {
	velocity.y = -300;
}

void Paddle::moveDown() {
	velocity.y = 300;
}

void Paddle::stop() {
	velocity.y = 0;
}

sf::RectangleShape Paddle::getShape() {
	return shape;
}