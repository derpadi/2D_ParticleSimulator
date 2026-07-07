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
    }

    void updatePosition(float dt){
        position.x += velocity.x * dt * scale;
        position.y += velocity.y * dt * scale;
    }

    void draw(){
        DrawCircleLinesV(position, radius, RED);
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
            balls.push_back(Ball2D({distX(gen), distY(gen)}, {velDist(gen), velDist(gen)}, 1.0f, 0.0f, 10.0f));
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
                Vector2 dir = { otherBall.position.x - ball.position.x,
                                otherBall.position.y - ball.position.y  };

                float length = sqrtf(dir.x*dir.x + dir.y * dir.y);
                dir.x /= length;
                dir.y /= length;
                float radiuses = ball.radius + otherBall.radius;
                float dist = ball.getDistance(otherBall);
                float overlap = radiuses - dist;

                float partBall1 = ball.radius / radiuses;
                float partBall2 = ball.radius / radiuses;

                ball.position.x -= overlap * partBall1 * dir.x;
                ball.position.y -= overlap * partBall2 * dir.y;

                float absVel = ball.getAbsoluteVelocity();

                ball.velocity.x = -absVel * ball.bounciness*dir.x;
                ball.velocity.y = -absVel * ball.bounciness*dir.y;
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
    Ball2D ball2 = Ball2D({ 585.0f, 400.0f }, {0.0f, -20.0f}, 1.0f, 0.0f, 10.0f);

    BoundingBallsSimulation sim = BoundingBallsSimulation(screenHeight, screenWidth);

    //sim.addBall(ball1);
    //sim.addBall(ball2);

    sim.addBallRandom(100);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // -------------------------------------- CODE GOES HERE --------------------------------------

        float dt = GetFrameTime();

        sim.update(dt*0.5f);


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