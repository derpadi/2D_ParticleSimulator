#include "InputHandler.h"
#include <iostream>

void InputHandler::update()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(onLeftClick){
            onLeftClick(GetMousePosition());
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
        std::cout << "Pressed" << std::endl;
        if(onAPressed){
            onAPressed();
        }
    }

}