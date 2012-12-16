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
#include <memory>
#include <cassert>

struct ALLEGRO_DISPLAY;

class IGameStateManager;
typedef std::shared_ptr<IGameStateManager> GameStateManagerPtr;

class IGameState;
typedef std::shared_ptr<IGameState> GameStatePtr;

class InputHandler;
typedef std::shared_ptr<InputHandler> InputHandlerPtr;

class IGameStateManager {
public:
    virtual ~IGameStateManager() {}
    
    virtual void pushState(GameStatePtr gameState) = 0;
    virtual void changeState(GameStatePtr gameState) = 0;
    virtual void popState() = 0;
    
    virtual void handleInput(InputHandlerPtr inputHandler, float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(ALLEGRO_DISPLAY *display) = 0;
    
    virtual void _setCurrentState(GameStatePtr gameState) = 0;
    virtual void _removeState(GameStatePtr gameState) = 0;
    
    virtual GameStatePtr getTopState() const = 0;
    virtual unsigned int getActiveStateCount() const = 0;
};

typedef std::list<GameStatePtr> GameStateList;

class GameStateManager : public IGameStateManager, public std::enable_shared_from_this<GameStateManager> {
    
private:
    GameStateList gameStateList;
    GameStatePtr queuedState;
    
public:
    GameStateManager();
    ~GameStateManager();
    
    void pushState(GameStatePtr gameState);
    void changeState(GameStatePtr gameState);
    void popState();
    
    void handleInput(InputHandlerPtr inputHandler, float dt);
    void update(float dt);
    void draw(ALLEGRO_DISPLAY *display);
    
    void _onStateTransitionOutOver(GameStatePtr gameState);
    
    GameStatePtr getTopState() const {
        assert(gameStateList.size() > 0 && "There's no states!");
        return gameStateList.back();
    }
    
    unsigned int getActiveStateCount() const {
        return (unsigned int)gameStateList.size();
    }
    
    void _setCurrentState(GameStatePtr gameState);
    void _removeState(GameStatePtr gameState);
};

#endif
