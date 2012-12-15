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
    
}

PlayState::~PlayState() {
    
}

void PlayState::onEnter() {
    
}

void PlayState::onExit() {
    
}

void PlayState::handleInput(InputHandlerPtr inputHandler) {
    
    if (inputHandler->isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        
    }
    
}

void PlayState::update(float dt) {
    
}

void PlayState::draw(ALLEGRO_DISPLAY *display) {
    
    al_draw_filled_circle(50, 50, 20, al_map_rgb(255, 0, 0));
    
}

GameStatePtr PlayState::GetInstance() {
    static GameStatePtr playState = std::make_shared<PlayState>();
    return playState;
}