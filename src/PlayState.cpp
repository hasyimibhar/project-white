//
//  PlayState.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#include "PlayState.h"
#include <allegro5/allegro_primitives.h>

PlayState::PlayState() {
    x = 50;
}

PlayState::~PlayState() {
    
}

void PlayState::onEnter(GameStateManagerPtr manager) {
    
}

void PlayState::onExit(GameStateManagerPtr manager) {
    
}

void PlayState::handleInput(
                            GameStateManagerPtr manager,
                            InputHandlerPtr     inputHandler) {
    
    if (inputHandler->isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        manager->popState();
    }
    
}

void PlayState::update(
                       GameStateManagerPtr  manager,
                       float                dt) {
    x += 50 * dt;
}

void PlayState::draw(GameStateManagerPtr    manager,
                     ALLEGRO_DISPLAY        *display) {
    
    al_draw_filled_circle(x, 50, 20, al_map_rgb(255, 0, 0));
    
}

GameStatePtr PlayState::GetInstance() {
    static GameStatePtr playState = std::make_shared<PlayState>();
    return playState;
}