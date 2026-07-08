#include "Application.h"
#include "rlImGui.h"
#include "imgui.h"

void Application::drawUI()
{
    rlImGuiBegin();
    ImGui::Begin("Simulation Telemetry");
    ImGui::Text("#Particles: %zu", sim.getParticleCount());

    if(input.getArmed()){
        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "ARMED");
    } else {
        ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "DISARMED");
    }
    ImGui::SliderFloat("ballsize", &currentBallSize, 0, 100);
    ImGui::SliderFloat("mass", &currentBallMass, 0, 100);
    ImGui::SliderFloat("vx", &currentBallVx, -100, 100);
    ImGui::SliderFloat("vy", &currentBallVy, -100, 100);
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
        if(input.getArmed()){
            //sim.addBall(mousePos, {50.0f, -50.0f}, currentBallSize);
            sim.addBall(mousePos, { currentBallVx, currentBallVy }, currentBallMass, 1.0f, 9.81f, currentBallSize, RED, true);
        }
    };

    input.onSpacePressed = [this](){
        if(input.getArmed()){
            sim.addBallRandom(10);
        }
    };

    input.onUpPressed = [this](){
        currentBallSize += 1.0f;
    };

    input.onDownPressed = [this](){
        if(currentBallSize >= 2.0f)
            currentBallSize -= 1.0f;
    };

    input.onAPressed = [this](){
        input.toggleArmed();
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
