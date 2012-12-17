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
#include "DeltaTimer.h"

namespace AllegroFighters {
    class ControlsManager;
    class Combo;
    class ComboManager;
}

typedef std::shared_ptr<AllegroFighters::ControlsManager> ControlsManagerPtr;
typedef std::shared_ptr<AllegroFighters::Combo> ComboPtr;
typedef std::shared_ptr<AllegroFighters::ComboManager> ComboManagerPtr;

class PlayState : public BaseGameState {

private:
    DeltaTimer timer;
    DeltaTimer testTimer;
    ControlsManagerPtr controlsManager;
    ComboManagerPtr comboManager;
    
public:
    PlayState();
    ~PlayState();
    
    void onEnter(GameStateManagerPtr manager);
    void onExit(GameStateManagerPtr manager);
    
    void handleInput(GameStateManagerPtr manager, InputHandlerPtr inputHandler, float dt);
    void update(GameStateManagerPtr manager, float dt);
    void draw(GameStateManagerPtr manager, ALLEGRO_DISPLAY *display);
    
    static GameStatePtr GetInstance();
};

#endif
