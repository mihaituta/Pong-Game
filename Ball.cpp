#include "Ball.h"

Ball::Ball(float startX, float startY) {
    shape.setRadius(10);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(startX, startY);
    velocity = sf::Vector2f(-400, 400);
}

void Ball::update(float deltaTime) {
    shape.move(velocity * deltaTime);
}

void Ball::reverseXVelocity() {
    velocity.x = -velocity.x;
}

void Ball::reverseYVelocity() {
    velocity.y = -velocity.y;
}

sf::CircleShape Ball::getShape() {
    return shape;
}