#pragma once
#include "BouncingBallsSimulation.h"
#include "InputHandler.h"

class Application {

private:
    float screenHeight;
    float screenWidth;
    BoundingBallsSimulation sim;
    InputHandler input;

    float currentBallSize = 10.f;
    float currentBallMass = 1.0f;
    float currentBallVx = 10.0f;
    float currentBallVy = -10.0f;
    float currentBallDrag = 0.0f;

    bool rainbowMode = true;

    void drawUI();

public:
    Application(int width = 800, int height = 600);
    ~Application();

    void run();
    Color getColor();


};