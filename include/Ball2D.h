#pragma once
#include "raylib.h"

typedef struct Ball2D {
    Vector2 position;
    Vector2 velocity;
    float bounciness;
    float gravity;
    float radius;
    Color color;
    float scale = 10.0f;
    float mass = 1.0f; // Mass in kg, used for collision calculations

    Ball2D(Vector2 position, Vector2 velocity, float bounciness = 1.0f, float gravity = 9.81, float radius = 10.0f, Color color = RED);

    void updateVelocity(float dt);

    void updatePosition(float dt);

    void draw();

    float getAbsoluteVelocity();

    float getDistance(Ball2D &other);

} Ball2D;