#pragma once
#include "raylib.h"
#include <functional>

class InputHandler {
public:
    std::function<void(Vector2)> onLeftClick;
    std::function<void(Vector2)> onLeftHold;

    std::function<void()> onUpPressed;
    std::function<void()> onDownPressed;
    std::function<void()> onSpacePressed;
    std::function<void()> onAPressed;


    void update();
    void toggleArmed(){
        armed = !armed;
    }
    bool getArmed(){
        return armed;
    }

private:
    bool armed = false;
};