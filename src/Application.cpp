#include "Application.h"
#include "rlImGui.h"
#include "imgui.h"

void Application::drawUI()
{
    rlImGuiBegin();
    ImGui::Begin("Simulation Telemetry");
    ImGui::Text("#Particles: %zu", sim.getParticleCount());
    if(input.isArmed()){
        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "ARMED");
    } else {
        ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "DISARMED");
    }
    ImGui::SliderFloat("Ballsize", &currentBallSize, 0, 100);
    ImGui::SliderFloat("Mass", &currentBallMass, 0, 100);
    ImGui::SliderFloat("Speed(x)", &currentBallVx, -20, 20);
    ImGui::SliderFloat("Speed(y)", &currentBallVy, -20, 20);
    ImGui::SliderFloat("Spawnrate", &input.interval, 0, 100);
    ImGui::SliderFloat("Friction", &currentBallDrag, 0, 10);
    ImGui::Checkbox("Rainbow Mode", &rainbowMode);
    ImGui::Checkbox("Mouse Gravity", &mouseGravity);
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
        if(input.isArmed()){
            input.cooldown = 1.0/input.interval;
            sim.addBall(mousePos, { currentBallVx, currentBallVy }, currentBallMass, 1.0f, 9.81f, currentBallSize, getColor(), true, currentBallDrag);
        }
    };

    input.onSpacePressed = [this](){
        if(input.isArmed()){
            sim.addBallRandom(10, currentBallMass, currentBallSize);
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

    input.onCPressed = [this](){
        sim.clear();
    };

    input.onLeftHold = [this](Vector2 mousePos, float dt){
        input.cooldown -= dt;
        if(input.cooldown <= 0.0f && input.isArmed()){
            sim.addBall(mousePos, { currentBallVx, currentBallVy }, currentBallMass, 1.0f, 9.81f, currentBallSize, getColor(), true, currentBallDrag);
            input.cooldown = 1.0f/input.interval;
        }
    };
}

void Application::run()
{
    while(!WindowShouldClose()){
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        input.update(dt);

        sim.update(dt);

        DrawFPS(0,0);

        drawUI();

        EndDrawing();
    }
}

Color Application::getColor()
{
    if(rainbowMode){
        static const std::array<Color, 7> colors = { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK };
        static size_t currentIndex = 0;
        return colors[currentIndex++ % colors.size()];
    }
    return RED;
}

Application::~Application()
{
    rlImGuiShutdown();
    CloseWindow();
}
