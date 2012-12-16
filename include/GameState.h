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
#include "DeltaTimer.h"

class IGameState {
public:
    virtual ~IGameState() {}
    virtual void onEnter(GameStateManagerPtr manager) = 0;
    virtual void _onEnter(GameStateManagerPtr manager) = 0;
    virtual void onEnterTransitionFinished(GameStateManagerPtr manager) {};
    virtual void onExit(GameStateManagerPtr manager) = 0;
    virtual void _onExit(GameStateManagerPtr manager) = 0;
    virtual void onExitTransitionStarted(GameStateManagerPtr manager) {};
    
    virtual float getTransitionInInterval() const = 0;
    virtual float getTransitionOutInterval() const = 0;
    
    virtual void exit(GameStateManagerPtr manager) = 0;
    
    virtual void handleInput(GameStateManagerPtr manager, InputHandlerPtr inputHandler, float dt) = 0;
    virtual void update(GameStateManagerPtr manager, float dt) = 0;
    virtual void _update(GameStateManagerPtr manager, float dt) = 0;
    virtual void draw(GameStateManagerPtr manager, ALLEGRO_DISPLAY *display) = 0;
};

class BaseGameState : public IGameState, public std::enable_shared_from_this<BaseGameState> {
private:
    
protected:
    float transitionInInterval;
    float transitionOutInterval;
    DeltaTimer transitionTimer;
    
    enum State {
        TransitionIn,
        Active,
        TransitionOut,
        Inactive
    };
    
    State currentState;
    
public:
    BaseGameState()
    : transitionInInterval(1.0f)
    , transitionOutInterval(1.0f)
    , currentState(Inactive)
    {}
    
    float getTransitionInInterval() const {
        return transitionInInterval;
    }
    
    float getTransitionOutInterval() const {
        return transitionOutInterval;
    }
    
    void _onEnter(GameStateManagerPtr manager) {
        assert(currentState == Inactive);
        currentState = TransitionIn;
        transitionTimer.setTimeInterval(transitionInInterval);
        onEnter(manager);
    }
    
    void _onExit(GameStateManagerPtr manager) {
        assert(currentState == Active);
        currentState = TransitionOut;
        transitionTimer.setTimeInterval(transitionOutInterval);
        onExitTransitionStarted(manager);
    }
    
    void _update(GameStateManagerPtr manager, float dt) {
        
        transitionTimer.update(dt);
        update(manager, dt);
        if (currentState == TransitionIn && transitionTimer.isOver()) {
            onEnterTransitionFinished(manager);
            currentState = Active;
        } else if (currentState == TransitionOut && transitionTimer.isOver()) {
            onExit(manager);
            currentState = Inactive;
            manager->_removeState(shared_from_this());
        }
        
    }
    
    void exit(GameStateManagerPtr manager) {
        _onExit(manager);
    }
};

#endif
