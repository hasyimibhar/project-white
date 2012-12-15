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
#include "GameStateManager.h"

class IGameState {
public:
    virtual ~IGameState() {}
    virtual void onEnter(GameStateManagerPtr manager) = 0;
    virtual void onExit(GameStateManagerPtr manager) = 0;
    
    virtual void handleInput(GameStateManagerPtr manager, InputHandlerPtr inputHandler, float dt) = 0;
    virtual void update(GameStateManagerPtr manager, float dt) = 0;
    virtual void draw(GameStateManagerPtr manager, ALLEGRO_DISPLAY *display) = 0;
};

#endif
