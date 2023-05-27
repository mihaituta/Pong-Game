#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape; 
    sf::Vector2f velocity;

public:
    Ball(float startX, float startY);
    void update(float deltaTime); 
    void reverseXVelocity(); 
    void reverseYVelocity(); 
    sf::CircleShape getShape() ; 
};

#endif