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
#include <list>
#include "FastDelegate.h"

using namespace fastdelegate;

struct ALLEGRO_KEY;
struct ALLEGRO_KEYBOARD_STATE;
struct ALLEGRO_KEYBOARD_EVENT;

typedef unsigned char KeyboardKey;
typedef std::vector<bool> KeyboardState;

typedef FastDelegate1<KeyboardKey> OnKeyEvent;
typedef std::list<OnKeyEvent> DelegateList;

class InputHandler {

private:
    KeyboardState oldKeyboardState;
    KeyboardState currentKeyboardState;
    
    DelegateList keyDownDelegateList;
    DelegateList keyUpDelegateList;
    
public:
    InputHandler();
    
    void updateKeyboardState(const ALLEGRO_KEYBOARD_STATE *keyboardState);
    
    bool isKeyDown(const KeyboardKey key) const;
    bool isKeyUp(const KeyboardKey key) const;
    bool isKeyPressed(const KeyboardKey key) const;
    bool isKeyReleased(const KeyboardKey key) const;
    
    void addKeyDownDelegate(OnKeyEvent delegate);
    void addKeyUpDelegate(OnKeyEvent delegate);
    
    void removeKeyDownDelegate(OnKeyEvent delegate);
    void removeKeyUpDelegate(OnKeyEvent delegate);
    
    void onKeyDown(KeyboardKey key);
    void onKeyUp(KeyboardKey key);
};

#endif
