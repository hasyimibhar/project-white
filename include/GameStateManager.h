//
//  GameStateManager.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#ifndef project_white_GameStateManager_h
#define project_white_GameStateManager_h

#include <list>
#include "GameState.h"

class IGameStateManager {
public:
    virtual ~IGameStateManager() {}
    
    virtual void pushState(GameStatePtr gameState) = 0;
    virtual void changeState(GameStatePtr gameState) = 0;
    virtual void popState() = 0;
    
    virtual void update(float dt) = 0;
    virtual void draw(ALLEGRO_DISPLAY *display) = 0;
    virtual void handleInput(InputHandlerPtr inputHandler) = 0;
    
    virtual GameStatePtr getTopState() const = 0;
};

typedef std::list<GameStatePtr> GameStateList;

class GameStateManager : public IGameStateManager {
    
private:
    GameStateList gameStateList;
    
public:
    GameStateManager();
    ~GameStateManager();
    
    void pushState(GameStatePtr gameState);
    void changeState(GameStatePtr gameState);
    void popState();
    
    void update(float dt);
    void draw(ALLEGRO_DISPLAY *display);
    void handleInput(InputHandlerPtr inputHandler);
    
    GameStatePtr getTopState() const {
        return gameStateList.back();
    }
};

#endif
