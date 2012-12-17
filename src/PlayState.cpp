//
//  PlayState.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#include "PlayState.h"
#include "Interpolation.h"
#include "Application.h"
#include "GameControls.h"
#include "ComboRecognition.h"

#include <allegro5/allegro_primitives.h>
#include <iostream>

using namespace AllegroFighters;

PlayState::PlayState() {
    transitionInInterval = 2.0f;
    transitionOutInterval = 2.0f;
}

PlayState::~PlayState() {
    
}

void Test(const std::string &comboName) {
    std::cout << "Combo triggered!" << std::endl;
}

void PlayState::onEnter(GameStateManagerPtr manager) {
    controlsManager = std::make_shared<ControlsManager>("./data/config.ini");
    comboManager = std::make_shared<ComboManager>(Application::GetInstance()->getInputHandler());
    
    ComboPtr combo1 = comboManager->addCombo(
        std::make_shared<Combo>("Combo1", 0.2f)
           ->key(controlsManager->getKey(GameCommandMoveDown))
           ->key(controlsManager->getKey(GameCommandMoveLeft))
           ->key(controlsManager->getKey(GameCommandMoveRight))
           ->key(controlsManager->getKey(GameCommandPunch))
           ->key(controlsManager->getKey(GameCommandKick))
                           );
    combo1->addDelegate(&Test);
    
    timer.setTimeInterval(2.0f);
    testTimer.setTimeInterval(5.0f);
}

void PlayState::onExit(GameStateManagerPtr manager) {

}

void PlayState::handleInput(
                            GameStateManagerPtr manager,
                            InputHandlerPtr     inputHandler,
                            float               dt) {
    
    if (inputHandler->isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        exit(manager);
    }
    
}

void PlayState::update(
                       GameStateManagerPtr  manager,
                       float                dt) {
    timer.update(dt);
    testTimer.update(dt);
    comboManager->update(dt);
}

void PlayState::draw(GameStateManagerPtr    manager,
                     ALLEGRO_DISPLAY        *display) {
    
    al_draw_filled_circle(Interpolation<float>::Exponential(timer.getNormalizedTime(), 50, 400, EaseInOut),
                          50,
                          20,
                          al_map_rgb(Interpolation<unsigned char>::Exponential(timer.getNormalizedTime(), 255, 0, EaseInOut),
                                     Interpolation<unsigned char>::Exponential(timer.getNormalizedTime(), 0, 255, EaseInOut),
                                     0));
    
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