#include "Ball2D.h"
#include <cmath>

Ball2D::Ball2D(Vector2 position, Vector2 velocity, float mass, float bounciness, float gravity, float radius, Color color, bool visible)
:position(position), velocity(velocity), mass(mass), bounciness(bounciness), gravity(gravity), radius(radius), color(color), visible(visible)
{
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
    if (visible) {
        DrawCircleV(position, radius, { 255, 0, 0, 255 });
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