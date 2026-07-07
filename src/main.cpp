#include <iostream>
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

} Ball2D;




int main() {
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "C++ refresher");
    SetTargetFPS(60);
    rlImGuiSetup(true);

    Ball2D ball1 = Ball2D({ 300.0f, 200.0f }, {20.0f, 0.0f});



    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // -------------------------------------- CODE GOES HERE --------------------------------------

        float dt = GetFrameTime();

        ball1.updateVelocity(dt);
        ball1.updatePosition(dt);

        // Checking for wall collisions
        if(ball1.position.y+ball1.radius >= screenHeight){
            ball1.velocity.y *= -ball1.bounciness;
            ball1.position.y = screenHeight-ball1.radius;
        } else if(ball1.position.y-ball1.radius <= 0){
            ball1.velocity.y *= -ball1.bounciness;
            ball1.position.y = 0 + ball1.radius;
        }

        if(ball1.position.x-ball1.radius <= 0){
            ball1.velocity.x *= -ball1.bounciness;
            ball1.position.x = 0 + ball1.radius;
        } else if(ball1.position.x+ball1.radius >= screenWidth){
            ball1.velocity.x *= -ball1.bounciness;
            ball1.position.x = screenWidth - ball1.radius;
        }

        ball1.draw();


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