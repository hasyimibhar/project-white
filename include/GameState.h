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

struct ALLEGRO_DISPLAY;
class IGameState;
typedef std::shared_ptr<IGameState> GameStatePtr;

class IGameState {
public:
    virtual ~IGameState() {}
    virtual void onEnter() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(ALLEGRO_DISPLAY *display) = 0;
    virtual void onExit() = 0;
};

#endif
