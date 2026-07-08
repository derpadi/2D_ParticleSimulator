#include "Application.h"
#include "rlImGui.h"
#include "imgui.h"

void Application::drawUI()
{
    rlImGuiBegin();
    ImGui::Begin("Hello, world!");
    ImGui::Text("This in my control panel!");
    ImGui::End();
    rlImGuiEnd();
}

Application::Application(int width, int height)
    : screenWidth(width), screenHeight(height), sim(height, width)
{
    InitWindow(screenWidth, screenHeight, "Bouncing Balls");
    SetTargetFPS(120);
    rlImGuiSetup(true);

    Ball2D ball1 = Ball2D({ 600.0f, 200.0f }, {0.0f, 0.0f}, 1.0f, 0.0f, 10.0f);
    Ball2D ball2 = Ball2D({ 400.0f, 400.0f }, {6.0f, -6.0f}, 1.0f, 0.0f, 30.0f);

    ball2.mass = 1000.0f;
    sim.addBall(ball1);
    sim.addBall(ball2);
}

void Application::run()
{
    while(!WindowShouldClose()){
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        sim.update(dt);
        DrawFPS(0,0);

        drawUI();

        EndDrawing();
    }
}

Application::~Application()
{
    rlImGuiShutdown();
    CloseWindow();
}
