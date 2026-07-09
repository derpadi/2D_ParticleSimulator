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
    void addBall(Vector2 position, Vector2 velocity, float mass, float bounciness, float gravity, float size, Color color, bool vis, float drag);
    void addBallRandom(uint32_t amount, float mass = 1.0f, float size = 10.0f);

    void clear();

    void update(float dt);

    size_t getParticleCount() const{
        return balls.size();
    }

private:

    void checkForWallCollision(Ball2D &ball);
    void checkForCollision(Ball2D &ball);

};