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

PlayState::PlayState() {
}

PlayState::~PlayState() {
    
}

void PlayState::onEnter(GameStateManagerPtr manager) {
    timer.setTimeInterval(2.0f);
}

void PlayState::onExit(GameStateManagerPtr manager) {
    
}

void PlayState::handleInput(
                            GameStateManagerPtr manager,
                            InputHandlerPtr     inputHandler,
                            float               dt) {
    
    if (inputHandler->isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        manager->popState();
    }
    
}

void PlayState::update(
                       GameStateManagerPtr  manager,
                       float                dt) {
    timer.update(dt);
    
    if (timer.isOver()) {
        manager->changeState(PlayState::GetInstance());
    }
}

void PlayState::draw(GameStateManagerPtr    manager,
                     ALLEGRO_DISPLAY        *display) {
    
    al_draw_filled_circle(Interpolation<float>::Exponential(timer.getNormalizedTime(), 50, 400, EaseInOut),
                          50,
                          20,
                          al_map_rgb(Interpolation<unsigned char>::Exponential(timer.getNormalizedTime(), 255, 0, EaseInOut),
                                     Interpolation<unsigned char>::Exponential(timer.getNormalizedTime(), 0, 255, EaseInOut),
                                     0));
    
    al_draw_filled_rectangle(0,
                             0,
                             Application::GetInstance()->getWindowWidth(),
                             Application::GetInstance()->getWindowHeight(),
                             al_map_rgba_f(0, 0, 0, Interpolation<float>::Linear(timer.getNormalizedTime(), 1, 0)));
    
}

GameStatePtr PlayState::GetInstance() {
    static GameStatePtr playState = std::make_shared<PlayState>();
    return playState;
}