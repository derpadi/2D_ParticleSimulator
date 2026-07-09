#pragma once
#include "raylib.h"

typedef struct Ball2D {
    Vector2 position;
    Vector2 velocity;

    float bounciness;
    float gravity;
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
        float gravity = 9.81, 
        float radius = 10.0f, 
        Color color = RED, 
        bool visible = true,
        float drag = 0.0f
    );

    void updateVelocity(float dt);

    void updatePosition(float dt);

    void draw();

    float getAbsoluteVelocity() const;

    float getDistance(const Ball2D &other) const;

} Ball2D;