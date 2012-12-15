//
//  InputHandler.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#include "InputHandler.h"
#include <allegro5/allegro.h>

InputHandler::InputHandler() {
    
    for (int i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        oldKeyboardState.push_back(false);
        currentKeyboardState.push_back(false);
    }
    
}

void InputHandler::updateKeyboardState(const ALLEGRO_KEYBOARD_STATE *keyboardState) {
    
    for (int i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        oldKeyboardState[i] = currentKeyboardState[i];
        currentKeyboardState[i] = al_key_down(keyboardState, i);
    }

}

bool InputHandler::isKeyDown(const KeyboardKey key) const {
    return currentKeyboardState[(int)key];
}

bool InputHandler::isKeyUp(const KeyboardKey key) const {
    return !currentKeyboardState[(int)key];
}

bool InputHandler::isKeyPressed(const KeyboardKey key) const {
    return currentKeyboardState[(int)key] && !oldKeyboardState[(int)key];
}

bool InputHandler::isKeyReleased(const KeyboardKey key) const {
    return !currentKeyboardState[(int)key] && oldKeyboardState[(int)key];
}