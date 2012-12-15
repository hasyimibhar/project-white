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

GameStateManager::GameStateManager() {
    
}

GameStateManager::~GameStateManager() {
    
}

void GameStateManager::pushState(GameStatePtr gameState) {
    
    gameState->onEnter(shared_from_this());
    gameStateList.push_back(gameState);
    
}

void GameStateManager::changeState(GameStatePtr gameState) {
    
    for (auto state : gameStateList) {
        state->onExit(shared_from_this());
    }
    
    gameStateList.clear();
    pushState(gameState);
    
}

void GameStateManager::popState() {
    assert(gameStateList.size() > 0 && "There's no state to pop!");
    
    GameStatePtr topState = getTopState();
    topState->onExit(shared_from_this());
    
    gameStateList.pop_back();
}

void GameStateManager::update(float dt) {
    
    for (auto state : gameStateList) {
        state->update(shared_from_this(), dt);
    }
    
}

void GameStateManager::draw(ALLEGRO_DISPLAY *display) {
    
    for (auto state : gameStateList) {
        state->draw(shared_from_this(), display);
    }
    
}

void GameStateManager::handleInput(InputHandlerPtr inputHandler, float dt) {
    getTopState()->handleInput(shared_from_this(), inputHandler, dt);
}