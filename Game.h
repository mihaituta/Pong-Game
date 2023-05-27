#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

class Game {
private:
    sf::RenderWindow window; // SFML window
    Paddle playerPaddle; 
    Paddle enemyPaddle; 
    Ball ball;
    int playerScore; 
    int enemyScore;
    sf::Font font; 
    sf::Text playerScoreText; 
    sf::Text enemyScoreText; 

public:
    Game();
    bool isRunning();
    void processEvents();
    void update(float deltaTime);
    void handlePaddleCollisions();
    void handleBallCollisions();
    void updateScoreText();
    void render();
    void run();
};

#endif