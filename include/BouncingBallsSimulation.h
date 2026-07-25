#pragma once
#include "Ball2D.h"
#include <vector>
#include <cstdint>

class BoundingBallsSimulation{

    std::vector<Ball2D> balls;
    float screenHeight;
    float screenWidth;

    bool rainbowMode = false;


public:
    /**
     * @brief Constructs a new Bounding Balls Simulation object.
     * 
     * @param screenHeight The height of the simulation screen.
     * @param screenWidth The width of the simulation screen.
     */
    BoundingBallsSimulation(float screenHeight, float screenWidth);

    void addBall(Ball2D &ballToAdd);
    void addBall(Vector2 position, Vector2 velocity, float size = 10.0f);
    void addBall(Vector2 position, Vector2 velocity, float mass, float bounciness, float gravity, float size, Color color, bool vis, float drag);
    void addBallRandom(uint32_t amount, float mass = 1.0f, float size = 10.0f);

    void clear();

    /**
     * @brief Updates the simulation based on a time step. (1. Update ball-state/wall collisions, 2. Ball/Ball collisions, 3. Draw)
     * 
     * @param dt The time step in seconds.
     */
    void update(float dt);

    /**
     * @brief Gets the number of balls in the simulation.
     * 
     * @return The number of balls.
     */
    size_t getParticleCount() const{
        return balls.size();
    }

private:

    /**
     * @brief Checks for collisions with the walls.
     * 
     * @param ball The ball to check.
     */
    void checkForWallCollision(Ball2D &ball);
    /**
     * @brief Checks for collisions with other balls.
     * 
     * @note Deprecated! Not used anymore!
     * 
     * @param ball The ball to check.
     */
    void checkForCollision(Ball2D &ball);

    /**
     * @brief Resolves the collision between two balls.
     * 
     * @param ball1 The first ball.
     * @param ball2 The second ball.
     */
    void resolveCollision(Ball2D &ball1, Ball2D &ball2);
};