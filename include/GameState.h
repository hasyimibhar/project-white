//
//  GameState.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#ifndef project_white_GameState_h
#define project_white_GameState_h

#include <memory>
#include "InputHandler.h"

struct ALLEGRO_DISPLAY;
class IGameState;
typedef std::shared_ptr<IGameState> GameStatePtr;

class InputHandler;
typedef std::shared_ptr<InputHandler> InputHandlerPtr;

class IGameState {
public:
    virtual ~IGameState() {}
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    
    virtual void update(float dt) = 0;
    virtual void draw(ALLEGRO_DISPLAY *display) = 0;
    virtual void handleInput(InputHandlerPtr inputHandler) = 0;
};

#endif
