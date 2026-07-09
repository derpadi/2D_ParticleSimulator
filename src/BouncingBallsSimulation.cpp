#include "BouncingBallsSimulation.h"
#include <random>


BoundingBallsSimulation::BoundingBallsSimulation(float screenHeight, float screenWidth)
:screenHeight(screenHeight), screenWidth(screenWidth){

}

void BoundingBallsSimulation::addBall(Ball2D &ballToAdd){
    balls.push_back(ballToAdd);
}

void BoundingBallsSimulation::addBall(Vector2 position, Vector2 velocity, float size){
    Ball2D ball = Ball2D(position, velocity);
    ball.radius = size;
    balls.push_back(ball);
}

void BoundingBallsSimulation::addBall(Vector2 position, Vector2 velocity, float mass, float bounciness, float gravity, float size, Color color, bool vis, float drag)
{
    Ball2D ball = Ball2D(position, velocity, mass, bounciness, gravity, size, color, vis, drag);
    balls.push_back(ball);
}

void BoundingBallsSimulation::addBallRandom(uint32_t amount, float mass, float size){
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(20, screenWidth-20.0f);
    std::uniform_real_distribution<float> distY(20, screenHeight-20.0f);

    std::uniform_real_distribution<float> velDist(-50.0f, 50.0f);

    for(uint32_t i = 0; i < amount; i++)
        balls.push_back(Ball2D({distX(gen), distY(gen)}, {velDist(gen), velDist(gen)}, mass, 1.0f, 0.0f, size, RED, true));
}

void BoundingBallsSimulation::clear()
{
    balls.clear();
}

void BoundingBallsSimulation::update(float dt){
    for(Ball2D &ball : balls){
        ball.updateVelocity(dt);
        ball.updatePosition(dt);
        checkForCollision(ball);
        ball.draw();
    }
}


void BoundingBallsSimulation::checkForWallCollision(Ball2D &ball){
    if(ball.position.y+ball.radius >= screenHeight){
        ball.velocity.y *= -ball.bounciness;
        ball.position.y = screenHeight-ball.radius;
    } else if(ball.position.y-ball.radius <= 0){
        ball.velocity.y *= -ball.bounciness;
        ball.position.y = 0 + ball.radius;
    }

    if(ball.position.x-ball.radius <= 0){
        ball.velocity.x *= -ball.bounciness;
        ball.position.x = 0 + ball.radius;
    } else if(ball.position.x+ball.radius >= screenWidth){
        ball.velocity.x *= -ball.bounciness;
        ball.position.x = screenWidth - ball.radius;
    }
}

void BoundingBallsSimulation::checkForCollision(Ball2D &ball){
    checkForWallCollision(ball);

    for(Ball2D &otherBall : balls){
        if(&ball == &otherBall) continue;
        if(CheckCollisionCircles(ball.position, ball.radius, otherBall.position, otherBall.radius)){

            // Normal and Tangential of Collision
            float distance = ball.getDistance(otherBall);
            Vector2 normal = { (otherBall.position.x - ball.position.x) / distance, (otherBall.position.y - ball.position.y) / distance };
            Vector2 tangential = {- normal.y, normal.x };

            // Normal speeds
            float v1n = ball.velocity.x * normal.x + ball.velocity.y * normal.y;
            float v2n = otherBall.velocity.x * normal.x + otherBall.velocity.y * normal.y;

            if(v1n - v2n <= 0.0f)
                continue;

            // Tangential speeds
            float v1t = ball.velocity.x * tangential.x + ball.velocity.y * tangential.y;
            float v2t = otherBall.velocity.x * tangential.x + otherBall.velocity.y * tangential.y;

            float v1new = ((ball.mass - otherBall.mass)/(ball.mass + otherBall.mass)) * v1n + ((2.0f * otherBall.mass)/(ball.mass + otherBall.mass)) * v2n;
            float v2new = ((2.0f * ball.mass)/(ball.mass + otherBall.mass)) * v1n + ((otherBall.mass - ball.mass)/(ball.mass + otherBall.mass)) * v2n;

            Vector2 b1_new_norm_vel = { v1new * normal.x, v1new * normal.y};
            Vector2 b2_new_norm_vel = { v2new * normal.x, v2new * normal.y};

            // Note Tangential speeds remain unchanged
            Vector2 b1_new_tan_vel = { v1t * tangential.x, v1t * tangential.y};
            Vector2 b2_new_tan_vel = { v2t * tangential.x, v2t * tangential.y};

            ball.velocity = { b1_new_norm_vel.x + b1_new_tan_vel.x, b1_new_norm_vel.y + b1_new_tan_vel.y };
            otherBall.velocity = { b2_new_norm_vel.x + b2_new_tan_vel.x, b2_new_norm_vel.y + b2_new_tan_vel.y };

            // Resolve superposition
            float overlap = (ball.radius + otherBall.radius) - distance;

            float ball1_part = (1.0f/ball.mass)/((1.0f/ball.mass) + (1.0f/otherBall.mass));
            float ball2_part = (1.0f/otherBall.mass)/((1.0f/ball.mass) + (1.0f/otherBall.mass));

            // Correct balls positions
            ball.position.x -= ball1_part * overlap * normal.x;
            ball.position.y -= ball1_part * overlap * normal.y;

            otherBall.position.x += ball2_part * overlap * normal.x;
            otherBall.position.y += ball2_part * overlap * normal.y;
        }
    }
}
