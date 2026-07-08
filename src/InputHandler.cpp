#include "InputHandler.h"

void InputHandler::update()
{
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        if(onLeftClick){
            onLeftClick(GetMousePosition());
        }
    }

    if(IsKeyPressed(KEY_SPACE)){
        if(onSpacePressed){
            onSpacePressed();
        }
    }
}