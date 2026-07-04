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


    float v_x = 20.0f;
    float v_y = 0.0f;
    float pos_x = 300.0f;
    float pos_y = 200.0f;

    float scale = 10.0f;
    //float timescale = 0.1f;


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // -------------------------------------- CODE GOES HERE --------------------------------------

        float dt = GetFrameTime();
        v_y += 9.81f * dt;
        pos_y += v_y * dt * scale;

        //v_x *= 0.9f;
        pos_x += v_x * dt * scale;

        if(pos_y+10 >= screenHeight){
            v_y *= -1.0f;
            pos_y = screenHeight-10.0f;
        }

        if(pos_y-10 <= 0){
            v_y *= -1.0f;
            pos_y = 0 + 10.0f;
        }

        if(pos_x-10 <= 0){
            v_x *= -1.0f;
            pos_x = 0 + 10.0f;
        }

        if(pos_x+10 >= screenWidth){
            v_x *= -1.0f;
            pos_x = screenWidth - 10.0f;
        }

        Vector2 test = { pos_x, pos_y };
        DrawCircleLinesV(test, 10, RED);



        // -------------------------------------- CODE GOES HERE --------------------------------------

        rlImGuiBegin();
        ImGui::Begin("Hello, world!");
        ImGui::Text("This in my control panel!");
        ImGui::Text("Velocity (x,y): (%.2f, %.2f) m/s", v_x, v_y);

        ImGui::Text("Position (x,y): (%.2f,%.2f) m", pos_x, pos_y);
        ImGui::End();
        rlImGuiEnd();

        EndDrawing();
    }
    
}
    
    return 0;
}