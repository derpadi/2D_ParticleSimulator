#include "InputHandler.h"

Vector2 InputHandler::update(float dt)
{
    Vector2 mousePos = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(onLeftClick){
            onLeftClick(mousePos);
        }
    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        if(onLeftHold){
            onLeftHold(mousePos, dt);
        }
    }

    if(IsKeyPressed(KEY_SPACE)){
        if(onSpacePressed){
            onSpacePressed();
        }
    }

    if(IsKeyPressed(KEY_UP)){
        if(onUpPressed){
            onUpPressed();
        }
    }

    if(IsKeyPressed(KEY_DOWN)){
        if(onDownPressed){
            onDownPressed();
        }
    }

    if(IsKeyPressed(KEY_A)){
        if(onAPressed){
            onAPressed();
        }
    }

    if(IsKeyPressed(KEY_C)){
        if(onCPressed){
            onCPressed();
        }
    }
    
    return mousePos;
}