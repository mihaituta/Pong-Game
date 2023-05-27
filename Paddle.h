#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
class Ball;

class Paddle {
private:
    sf::RectangleShape shape; 
    sf::Vector2f velocity; 

public:
    Paddle(float startX, float startY); 
    void update(float deltaTime, int windowSize);
    void updateAI(float deltaTime, Ball& ball); 
    void moveUp(); 
    void moveDown(); 
    void stop();
    sf::RectangleShape getShape();
};

#endif