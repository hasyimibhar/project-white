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
    timer.setTimeInterval(5);
}

PlayState::~PlayState() {
    
}

void PlayState::onEnter(GameStateManagerPtr manager) {
    
}

void PlayState::onExit(GameStateManagerPtr manager) {
    
}

void PlayState::handleInput(
                            GameStateManagerPtr manager,
                            InputHandlerPtr     inputHandler,
                            float               dt) {
    
    if (inputHandler->isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        manager->popState();
    } else if (inputHandler->isKeyDown(ALLEGRO_KEY_RIGHT)) {
        x += 50 * dt;
    }
    
}

void PlayState::update(
                       GameStateManagerPtr  manager,
                       float                dt) {
    timer.update(dt);
}

void PlayState::draw(GameStateManagerPtr    manager,
                     ALLEGRO_DISPLAY        *display) {
    
    ALLEGRO_COLOR color;
    if (!timer.isOver()) {
        color = al_map_rgb(255, 0, 0);
    } else {
        color = al_map_rgb(0, 255, 0);
    }
    
    al_draw_filled_circle(x, 50, 20, color);
    
}

GameStatePtr PlayState::GetInstance() {
    static GameStatePtr playState = std::make_shared<PlayState>();
    return playState;
}