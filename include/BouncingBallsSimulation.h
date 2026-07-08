#pragma once
#include "Ball2D.h"
#include <vector>
#include <cstdint>

class BoundingBallsSimulation{

    std::vector<Ball2D> balls;
    float screenHeight;
    float screenWidth;


public:
    BoundingBallsSimulation(float screenHeight, float screenWidth);

    void addBall(Ball2D &ballToAdd);
    void addBall(Vector2 position, Vector2 velocity, float size = 10.0f);
    void addBallRandom(uint32_t amount);

    void update(float dt);

private:

    void checkForWallCollision(Ball2D &ball);
    void checkForCollision(Ball2D &ball);

};