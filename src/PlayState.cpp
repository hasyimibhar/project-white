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
#include "World.h"
#include "Camera.h"
#include "Character.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

using namespace AllegroFighters;

PlayState::PlayState() : world(nullptr) {
    transitionInInterval = 2.0f;
    transitionOutInterval = 2.0f;
}

PlayState::~PlayState() {
    
}

void PlayState::onEnter(GameStateManagerPtr manager) {
    
    world = std::make_shared<World>(MakeSize(1600, 600));
    camera = std::make_shared<Camera>(world, MakeSize(Application::GetInstance()->getWindowWidth(), Application::GetInstance()->getWindowHeight()));
    
    background = al_load_bitmap("./data/textures/backgrounds/01.png");
    if (background == NULL) {
        throw std::runtime_error("Missing texture!");
    }
    
    CharacterPtr character1 = std::make_shared<Character>();
    character1->setPosition(Vector2(-150, 200));
    world->addEntity(character1);
    
    CharacterPtr character2 = std::make_shared<Character>();
    character2->setPosition(Vector2(150, 200));
    world->addEntity(character2);
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
    } else if (inputHandler->isKeyPressed(ALLEGRO_KEY_LEFT)) {
        camera->moveBy(Vector2(100, 0));
    } else if (inputHandler->isKeyPressed(ALLEGRO_KEY_RIGHT)) {
        camera->moveBy(Vector2(-100, 0));
    }
    
    world->handleInput(inputHandler, dt);
}

void PlayState::update(
                       GameStateManagerPtr  manager,
                       float                dt) {
    world->update(dt);
    camera->update(dt);
}

void PlayState::draw(GameStateManagerPtr    manager,
                     ALLEGRO_DISPLAY        *display) {
    
    al_draw_bitmap(background, (Application::GetInstance()->getWindowWidth() - 1600) / 2 + camera->getPosition().x, 0, 0);
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