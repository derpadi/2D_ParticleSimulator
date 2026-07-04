#include <iostream>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"


int main() {
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "C++ refresher");
    SetTargetFPS(60);
    rlImGuiSetup(true);


    float radius = 10.0f;

    Vector2 position = { 300.0f, 200.0f };
    Vector2 velocity = { 20.0f, 0.0f};
    float bounciness = 1.0f;

    float scale = 10.0f;
    //float timescale = 0.1f;


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // -------------------------------------- CODE GOES HERE --------------------------------------

        float dt = GetFrameTime();

        // Updating physics
        velocity.y += 9.81f * dt;

        position.x += velocity.x * dt * scale;
        position.y += velocity.y * dt * scale;

        // Checking for wall collisions
        if(position.y+radius >= screenHeight){
            velocity.y *= -bounciness;
            position.y = screenHeight-radius;
        } else if(position.y-radius <= 0){
            velocity.y *= -bounciness;
            position.y = 0 + radius;
        }

        if(position.x-radius <= 0){
            velocity.x *= -bounciness;
            position.x = 0 + radius;
        } else if(position.x+radius >= screenWidth){
            velocity.x *= -bounciness;
            position.x = screenWidth - radius;
        }

        DrawCircleLinesV(position, radius, RED);



        // -------------------------------------- CODE GOES HERE --------------------------------------

        rlImGuiBegin();
        ImGui::Begin("Hello, world!");
        ImGui::Text("This in my control panel!");
        ImGui::Text("Velocity (x,y): (%.2f, %.2f) m/s", velocity.x, velocity.y);
        ImGui::Text("Position (x,y): (%.2f,%.2f) m", position.x, position.y);
        ImGui::End();
        rlImGuiEnd();

        EndDrawing();
    }
    
}
    
    return 0;
}