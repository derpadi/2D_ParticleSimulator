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


    /**
     * @brief Updates the input handler based on the time step.
     * @param dt The time step in seconds.
     * @return The current mouse position as a Vector2.
     */
    Vector2 update(float dt);

    /**
     * @brief Toggles the armed state. (Arming mouse interaction)
     */
    void toggleArmed(){
        armed = !armed;
    }

    /**
     * @brief Checks if the input handler is armed.
     * @return True if armed, false otherwise.
     */
    bool isArmed(){
        return armed;
    }

private:
    bool armed = false;
};