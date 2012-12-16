//
//  GameStateManager.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#include "GameStateManager.h"
#include "InputHandler.h"
#include "GameState.h"
#include <algorithm>

GameStateManager::GameStateManager() : queuedState(nullptr) {
    
}

GameStateManager::~GameStateManager() {
    
}

void GameStateManager::pushState(GameStatePtr gameState) {
    
    gameState->_onEnter(shared_from_this());
    gameStateList.push_back(gameState);
    
}

void GameStateManager::changeState(GameStatePtr gameState) {
    
    for (auto state : gameStateList) {
        state->_onExit(shared_from_this());
    }
    
    queuedState = gameState;
}

void GameStateManager::popState() {
    assert(gameStateList.size() > 0 && "There's no state to pop!");
    
    GameStatePtr topState = getTopState();
    topState->_onExit(shared_from_this());
}

void GameStateManager::_setCurrentState(GameStatePtr gameState) {
    assert(gameStateList.empty());
    pushState(gameState);
}

void GameStateManager::_removeState(GameStatePtr gameState) {
    assert(std::find(gameStateList.begin(), gameStateList.end(), gameState) != gameStateList.end());
    gameStateList.remove(gameState);
}

void GameStateManager::update(float dt) {
    
    for (auto state : gameStateList) {
        state->_update(shared_from_this(), dt);
    }
    
    if (queuedState != nullptr && gameStateList.empty()) {
        pushState(queuedState);
        queuedState = nullptr;
    }
    
}

void GameStateManager::_onStateTransitionOutOver(GameStatePtr gameState) {
    gameStateList.remove(gameState);
}

void GameStateManager::draw(ALLEGRO_DISPLAY *display) {
    
    for (auto state : gameStateList) {
        state->draw(shared_from_this(), display);
    }
    
}

void GameStateManager::handleInput(InputHandlerPtr inputHandler, float dt) {
    getTopState()->handleInput(shared_from_this(), inputHandler, dt);
}