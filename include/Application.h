#pragma once
#include "BouncingBallsSimulation.h"
#include "InputHandler.h"

class Application {

private:
    float screenHeight;
    float screenWidth;
    BoundingBallsSimulation sim;
    InputHandler input;

    void drawUI();

public:
    Application(int width = 800, int height = 600);
    ~Application();

    void run();


};