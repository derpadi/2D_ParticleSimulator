#pragma once
#include "raylib.h"

struct Ball2D {
    Vector2 position;
    Vector2 velocity;

    float bounciness;
    static float gravity;
    float radius;
    float mass = 1.0f; // Mass in kg, used for collision calculations
    float drag = 0.0f;

    Color color;
    float scale = 100.0f;
    bool visible = true;

    Ball2D(
        Vector2 position, 
        Vector2 velocity, 
        float mass = 1.0f,
        float bounciness = 1.0f,
        float radius = 10.0f, 
        Color color = RED, 
        bool visible = true,
        float drag = 0.0f
    );

    /**
     * @brief Updates the ball's position and velocity based on the time step.
     * @param dt The time step in seconds.
     */
    void updateVelocity(float dt);

    void updateVelocityWithGravitationalCenter(float dt, Vector2 gravitationalCenter, float gravitationalConstant);

    /**
     * @brief Updates the ball's position based on the time step.
     * @param dt The time step in seconds.
     */
    void updatePosition(float dt);

    /**
     * @brief Draws the ball on the screen.
     */
    void draw();

    /**
     * @brief Gets the absolute velocity of the ball.
     * @return The absolute velocity.
     */
    float getAbsoluteVelocity() const;

    /**
     * @brief Gets the distance to another ball.
     * @param other The other ball.
     * @return The distance.
     */
    float getDistance(const Ball2D &other) const;

};