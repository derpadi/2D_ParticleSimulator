#include "Ball2D.h"
#include <cmath>

#include <iostream>

Ball2D::Ball2D(
    Vector2 position, 
    Vector2 velocity, 
    float mass, 
    float bounciness, 
    float gravity, 
    float radius, 
    Color color, 
    bool visible,
    float drag)
:
position(position), 
velocity(velocity), 
mass(mass), 
bounciness(bounciness), 
gravity(gravity), 
radius(radius), 
color(color), 
visible(visible),
drag(drag)
{
}

void Ball2D::updateVelocity(float dt, bool mouseGravity, Vector2 mousePos){    
    velocity.y += gravity * dt;

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