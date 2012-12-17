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
struct ALLEGRO_BITMAP;

namespace AllegroFighters {
    class World;
    class Camera;
    class Character;
}

typedef std::shared_ptr<AllegroFighters::World> WorldPtr;
typedef std::shared_ptr<AllegroFighters::Camera> CameraPtr;
typedef std::shared_ptr<AllegroFighters::Character> CharacterPtr;

class PlayState : public BaseGameState {

private:
    WorldPtr        world;
    CameraPtr       camera;
    ControlsManagerPtr controlsManager;
    ALLEGRO_BITMAP  *background;
    ComboManagerPtr comboManager;
    
    CharacterPtr    player1, player2;
    
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
