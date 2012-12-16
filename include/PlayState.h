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

struct ALLEGRO_BITMAP;

namespace AllegroFighters {
    class World;
    class Camera;
}

typedef std::shared_ptr<AllegroFighters::World> WorldPtr;
typedef std::shared_ptr<AllegroFighters::Camera> CameraPtr;

class PlayState : public BaseGameState {

private:
    WorldPtr        world;
    CameraPtr       camera;
    ALLEGRO_BITMAP  *background;
    
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
