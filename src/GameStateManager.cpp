//
//  GameStateManager.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#include "GameStateManager.h"
#include "InputHandler.h"
#include <cassert>

GameStateManager::GameStateManager() {
    
}

GameStateManager::~GameStateManager() {
    
}

void GameStateManager::pushState(GameStatePtr gameState) {
    
    gameState->onEnter();
    gameStateList.push_back(gameState);
    
}

void GameStateManager::changeState(GameStatePtr gameState) {
    
    for (auto state : gameStateList) {
        state->onExit();
    }
    
    gameStateList.clear();
    pushState(gameState);
    
}

void GameStateManager::popState() {
    assert(gameStateList.size() > 0 && "There's no state to pop!");
    
    GameStatePtr topState = getTopState();
    topState->onExit();
    
    gameStateList.pop_back();
}

void GameStateManager::update(float dt) {
    
    for (auto state : gameStateList) {
        state->update(dt);
    }
    
}

void GameStateManager::draw(ALLEGRO_DISPLAY *display) {
    
    for (auto state : gameStateList) {
        state->draw(display);
    }
    
}

void GameStateManager::handleInput(InputHandlerPtr inputHandler) {
    getTopState()->handleInput(inputHandler);
}