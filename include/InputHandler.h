#pragma once
#include "raylib.h"
#include <functional>

class InputHandler {
public:
    std::function<void(Vector2)> onLeftClick;
    std::function<void()> onSpacePressed;


    void update();
};