//
//  InputHandler.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#ifndef project_white_InputHandler_h
#define project_white_InputHandler_h

#include <vector>

struct ALLEGRO_KEY;
struct ALLEGRO_KEYBOARD_STATE;

typedef unsigned char KeyboardKey;
typedef std::vector<bool> KeyboardState;

class InputHandler {

private:
    KeyboardState oldKeyboardState;
    KeyboardState currentKeyboardState;
    
public:
    InputHandler();
    
    void updateKeyboardState(const ALLEGRO_KEYBOARD_STATE *keyboardState);
    
    bool isKeyDown(const KeyboardKey key) const;
    bool isKeyUp(const KeyboardKey key) const;
    bool isKeyPressed(const KeyboardKey key) const;
    bool isKeyReleased(const KeyboardKey key) const;
};

#endif
