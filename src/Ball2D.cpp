#include "Ball2D.h"
#include <cmath>

Ball2D::Ball2D(Vector2 position, Vector2 velocity, float bounciness, float gravity, float radius, Color color){
    this->position = position;
    this->velocity = velocity;
    this->bounciness = bounciness;
    this->gravity = gravity;
    this->radius = radius;
    this->color = color;
}

void Ball2D::updateVelocity(float dt){
    velocity.y += gravity * dt;

    //velocity.x *= 0.99f; // Friction
    //velocity.y *= 0.99f; // Friction
}

void Ball2D::updatePosition(float dt){
    position.x += velocity.x * dt * scale;
    position.y += velocity.y * dt * scale;
}

void Ball2D::draw(){
    //DrawCircleLinesV(position, radius, RED);
    DrawCircleV(position, radius, { 255, 0, 0, 255 });
}

float Ball2D::getAbsoluteVelocity(){
    return sqrtf(velocity.x*velocity.x + velocity.y*velocity.y);
}

float Ball2D::getDistance(Ball2D &other){
    float diffX = other.position.x - position.x;
    float diffY = other.position.y - position.y;
    return sqrtf(diffX * diffX + diffY * diffY);
}