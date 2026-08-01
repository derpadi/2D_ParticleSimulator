#include "Ball2D.h"
#include <cmath>

#include <iostream>

float Ball2D::gravity = 9.81f;
float Ball2D::drag = 0.0f;

Ball2D::Ball2D(
    Vector2 position, 
    Vector2 velocity, 
    float mass, 
    float bounciness,
    float radius, 
    Color color, 
    bool visible)
:
position(position), 
velocity(velocity), 
mass(mass), 
bounciness(bounciness),
radius(radius), 
color(color), 
visible(visible)
{
}

void Ball2D::updateVelocity(float dt){    
    velocity.y += gravity * dt;

    float damping = expf(-drag * dt);

    velocity.x *= damping;
    velocity.y *= damping;
}

void Ball2D::updateVelocityWithGravitationalCenter(float dt, Vector2 gravitationalCenter, float gravitationalConstant)
{
    Vector2 dir = { gravitationalCenter.x - position.x, gravitationalCenter.y - position.y };
    float distanceSquared = dir.x * dir.x + dir.y * dir.y;

    // Avoid division by zero and extremeyl high forces when close to center
    if (distanceSquared < 0.0001f) {
        return;
    }

    float distance = sqrtf(distanceSquared);
    float gravityRange = 300.0f;
    float distanceFactor = fminf(distance / gravityRange, 1.0f);
    float forceMagnitude = gravity * distanceFactor;

    velocity.x += forceMagnitude * dir.x / distance * dt;
    velocity.y += forceMagnitude * dir.y / distance * dt;

    // Daming due to drag
    float damping = expf(-drag * dt);
    velocity.x *= damping;
    velocity.y *= damping;
}

void Ball2D::updatePosition(float dt){
    position.x += velocity.x * dt * scale;
    position.y += velocity.y * dt * scale;
}

void Ball2D::draw(){
    //DrawCircleLinesV(position, radius, RED);
    if (visible) {
        DrawCircleV(position, radius, color);
    }
}

float Ball2D::getAbsoluteVelocity() const {
    return sqrtf(velocity.x*velocity.x + velocity.y*velocity.y);
}

float Ball2D::getDistance(const Ball2D &other) const{
    float diffX = other.position.x - position.x;
    float diffY = other.position.y - position.y;
    return sqrtf(diffX * diffX + diffY * diffY);
}