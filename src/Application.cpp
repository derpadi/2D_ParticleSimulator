#include "Application.h"
#include "rlImGui.h"
#include "imgui.h"

void Application::drawUI()
{
    rlImGuiBegin();
    ImGui::Begin("Simulation Telemetry");
    ImGui::Text("#Particles: %zu", sim.getParticleCount());
    ImGui::End();
    rlImGuiEnd();
}

Application::Application(int width, int height)
    : screenWidth(width), screenHeight(height), sim(height, width)
{
    InitWindow(screenWidth, screenHeight, "Bouncing Balls");
    SetTargetFPS(120);
    rlImGuiSetup(true);

    input.onLeftClick = [this](Vector2 mousePos){
        sim.addBall(mousePos, {50.0f, -50.0f}, 3.0f);
    };

    input.onSpacePressed = [this](){
        sim.addBallRandom(10);
    };
}

void Application::run()
{
    while(!WindowShouldClose()){
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        input.update();

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
