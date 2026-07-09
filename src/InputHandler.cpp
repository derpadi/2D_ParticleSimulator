#include "InputHandler.h"

void InputHandler::update(float dt)
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(onLeftClick){
            onLeftClick(GetMousePosition());
        }
    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        if(onLeftHold){
            onLeftHold(GetMousePosition(), dt);
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

}