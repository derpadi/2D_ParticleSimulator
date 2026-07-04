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

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // -------------------------------------- CODE GOES HERE --------------------------------------





        // -------------------------------------- CODE GOES HERE --------------------------------------

        rlImGuiBegin();
        ImGui::Begin("Hello, world!");
        ImGui::Text("This in my control panel!");
        ImGui::End();
        rlImGuiEnd();

        EndDrawing();
    }
    
}
    
    return 0;
}