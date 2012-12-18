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
#include "GameControls.h"
#include "ComboRecognition.h"

#include "World.h"
#include "Camera.h"
#include "Character.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

using namespace AllegroFighters;

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

using namespace AllegroFighters;

PlayState::PlayState() : world(nullptr) {
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
    
    camera = std::make_shared<Camera>(MakeSize(Application::GetInstance()->getWindowWidth(), Application::GetInstance()->getWindowHeight()), MakeSize(1600, 600));
    world = std::make_shared<World>(MakeSize(1600, 600), camera);
    
    background = al_load_bitmap("./data/textures/backgrounds/01.png");
    if (background == NULL) {
        throw std::runtime_error("Missing texture!");

    }
    
    player1 = std::make_shared<Character>();
    player1->setPosition(Vector2(0, World::FloorY));
    world->setPlayer1(player1);
    
    player2 = std::make_shared<Character>();
    player2->setPosition(Vector2(200, World::FloorY));
    world->setPlayer2(player2);
}

void PlayState::onExit(GameStateManagerPtr manager) {
    al_destroy_bitmap(background);
    world.reset();
}

void PlayState::handleInput(
                            GameStateManagerPtr manager,
                            InputHandlerPtr     inputHandler,
                            float               dt) {
    
    if (inputHandler->isKeyPressed(ALLEGRO_KEY_ESCAPE)) {
        exit(manager);
    }
    
    if (controlsManager->isKeyPressed(inputHandler, GameCommandJump)) {
        player1->jump();
    }
    
    if (controlsManager->isKeyDown(inputHandler, GameCommandMoveLeft)) {
        player1->move(Left);
    } else if (controlsManager->isKeyDown(inputHandler, GameCommandMoveRight)) {
        player1->move(Right);
    } else {
        player1->stop();
    }
    
    if (inputHandler->isKeyPressed(ALLEGRO_KEY_I)) {
        player2->jump();
    }
    
    if (inputHandler->isKeyDown(ALLEGRO_KEY_J)) {
        player2->move(Left);
    } else if (inputHandler->isKeyDown(ALLEGRO_KEY_L)) {
        player2->move(Right);
    } else {
        player2->stop();
    }
    
    world->handleInput(inputHandler, dt);
}

void PlayState::update(
                       GameStateManagerPtr  manager,
                       float                dt) {
    world->update(dt);
    camera->update(dt);
    comboManager->update(dt);
}

void PlayState::draw(GameStateManagerPtr    manager,
                     ALLEGRO_DISPLAY        *display) {
    
    al_draw_bitmap(background, camera->getOffset().x - al_get_bitmap_width(background) / 2, 0, 0);
    world->draw(display, camera);
    
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