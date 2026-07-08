#include <iostream>
#include <random>
#include <vector>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"


typedef struct Ball2D {
    Vector2 position;
    Vector2 velocity;
    float bounciness;
    float gravity;
    float radius;
    Color color;
    float scale = 10.0f;
    float mass = 1.0f; // Mass in kg, used for collision calculations

    Ball2D(Vector2 position, Vector2 velocity, float bounciness = 1.0f, float gravity = 9.81, float radius = 10.0f, Color color = RED){
        this->position = position;
        this->velocity = velocity;
        this->bounciness = bounciness;
        this->gravity = gravity;
        this->radius = radius;
        this->color = color;
    }

    void updateVelocity(float dt){
        velocity.y += gravity * dt;

        //velocity.x *= 0.99f; // Friction
        //velocity.y *= 0.99f; // Friction
    }

    void updatePosition(float dt){
        position.x += velocity.x * dt * scale;
        position.y += velocity.y * dt * scale;
    }

    void draw(){
        //DrawCircleLinesV(position, radius, RED);
        DrawCircleV(position, radius, { 255, 0, 0, 255 });
    }

    float getAbsoluteVelocity(){
        return sqrtf(velocity.x*velocity.x + velocity.y*velocity.y);
    }

    float getDistance(Ball2D &other){
        float diffX = other.position.x - position.x;
        float diffY = other.position.y - position.y;
        return sqrtf(diffX * diffX + diffY * diffY);
    }

} Ball2D;


class BoundingBallsSimulation{

    std::vector<Ball2D> balls;
    float screenHeight;
    float screenWidth;


public:
    BoundingBallsSimulation(float screenHeight, float screenWidth){
        this->screenHeight = screenHeight;
        this->screenWidth = screenWidth;
    }

    void addBall(Ball2D &ballToAdd){
        balls.push_back(ballToAdd);
    }

    void addBall(Vector2 position, Vector2 velocity){
        Ball2D ball = Ball2D(position, velocity);
        balls.push_back(ball);
    }

    void addBallRandom(uint32_t amount){
        static std::random_device rd;
        static std::mt19937 gen(rd());

        std::uniform_real_distribution<float> distX(20, screenWidth-20.0f);
        std::uniform_real_distribution<float> distY(20, screenHeight-20.0f);

        std::uniform_real_distribution<float> velDist(-50.0f, 50.0f);

        for(uint32_t i = 0; i < amount; i++)
            balls.push_back(Ball2D({distX(gen), distY(gen)}, {velDist(gen), velDist(gen)}, 1.0f, 0.0f, 5.0f));
    }

    void update(float dt){
        for(Ball2D &ball : balls){
            ball.updateVelocity(dt);
            ball.updatePosition(dt);
            checkForCollision(ball);
            ball.draw();
        }
    }

private:

    void checkForWallCollision(Ball2D &ball){
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

    void checkForCollision(Ball2D &ball){
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

};




int main() {
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "C++ refresher");
    SetTargetFPS(120);
    rlImGuiSetup(true);

    Ball2D ball1 = Ball2D({ 600.0f, 200.0f }, {0.0f, 0.0f}, 1.0f, 0.0f, 10.0f);
    Ball2D ball2 = Ball2D({ 400.0f, 400.0f }, {6.0f, -6.0f}, 1.0f, 0.0f, 30.0f);


    ball2.mass = 1000.0f;

    BoundingBallsSimulation sim = BoundingBallsSimulation(screenHeight, screenWidth);

    sim.addBall(ball1);
    sim.addBall(ball2);
    
    //sim.addBallRandom(100);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // -------------------------------------- CODE GOES HERE --------------------------------------

        float dt = GetFrameTime();

        sim.update(dt*1.0f);


        // -------------------------------------- CODE GOES HERE --------------------------------------

        rlImGuiBegin();
        ImGui::Begin("Hello, world!");
        ImGui::Text("This in my control panel!");
        ImGui::Text("Velocity (x,y): (%.2f, %.2f) m/s", ball1.velocity.x, ball1.velocity.y);
        ImGui::Text("Position (x,y): (%.2f,%.2f) m", ball1.position.x, ball1.position.y);
        ImGui::End();
        rlImGuiEnd();

        EndDrawing();
    }
    
}
    
    return 0;
}