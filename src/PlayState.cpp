//
//  PlayState.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#include "PlayState.h"
#include "Interpolation.h"
#include <allegro5/allegro_primitives.h>
#include "Application.h"
#include "World.h"

using namespace AllegroFighters;

PlayState::PlayState() : world(nullptr) {
    transitionInInterval = 2.0f;
    transitionOutInterval = 2.0f;
}

PlayState::~PlayState() {
    
}

void PlayState::onEnter(GameStateManagerPtr manager) {
    world = std::make_shared<World>();
}

void PlayState::onExit(GameStateManagerPtr manager) {
    world.reset();
}

void PlayState::handleInput(
                            GameStateManagerPtr manager,
                            InputHandlerPtr     inputHandler,
                            float               dt) {
    
    if (inputHandler->isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        exit(manager);
    }
    
    world->handleInput(inputHandler, dt);
}

void PlayState::update(
                       GameStateManagerPtr  manager,
                       float                dt) {
    world->update(dt);
}

void PlayState::draw(GameStateManagerPtr    manager,
                     ALLEGRO_DISPLAY        *display) {
    
    world->draw(display);
    
    if (currentState == TransitionIn) {
        al_draw_filled_rectangle(0,
                                 0,
                                 Application::GetInstance()->getWindowWidth(),
                                 Application::GetInstance()->getWindowHeight(),
                                 al_map_rgba_f(0, 0, 0, Interpolation<float>::Linear(transitionTimer.getNormalizedTime(), 1, 0)));
    } else if (currentState == TransitionOut) {
        al_draw_filled_rectangle(0,
                                 0,
                                 Application::GetInstance()->getWindowWidth(),
                                 Application::GetInstance()->getWindowHeight(),
                                 al_map_rgba_f(0, 0, 0, Interpolation<float>::Linear(transitionTimer.getNormalizedTime(), 0, 1)));
    }
}

GameStatePtr PlayState::GetInstance() {
    static GameStatePtr playState = std::make_shared<PlayState>();
    return playState;
}