#pragma once
#include "BouncingBallsSimulation.h"

class Application {

private:
    float screenHeight;
    float screenWidth;

    BoundingBallsSimulation sim;

    void drawUI();

public:
    Application(int width = 800, int height = 600);
    ~Application();

    void run();


};