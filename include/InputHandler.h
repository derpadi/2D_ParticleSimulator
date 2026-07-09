#pragma once
#include "raylib.h"
#include <functional>

class InputHandler {
public:
    std::function<void(Vector2)> onLeftClick;
    std::function<void(Vector2, float)> onLeftHold;

    std::function<void()> onUpPressed;
    std::function<void()> onDownPressed;
    std::function<void()> onSpacePressed;
    std::function<void()> onAPressed;
    std::function<void()> onCPressed;

    float interval = 0.1f;
    float cooldown = 0.0f;


    void update(float dt);
    void toggleArmed(){
        armed = !armed;
    }
    bool getArmed(){
        return armed;
    }

private:
    bool armed = false;
};