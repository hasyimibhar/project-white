//
//  PlayState.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#ifndef project_white_PlayState_h
#define project_white_PlayState_h

#include "GameState.h"

class PlayState : public IGameState, public std::enable_shared_from_this<PlayState> {

public:
    PlayState();
    ~PlayState();
    
    void onEnter();
    void onExit();
    
    void handleInput(InputHandlerPtr inputHandler);
    void update(float dt);
    void draw(ALLEGRO_DISPLAY *display);
    
    static GameStatePtr GetInstance();
};

#endif
