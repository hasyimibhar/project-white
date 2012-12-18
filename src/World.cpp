//
//  World.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#include "World.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Camera.h"
#include "Application.h"
#include "Character.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include <iostream>

using namespace AllegroFighters;

const float World::FloorY   = 550.0f;
const float World::GravityAcceleration = 2000.0f;

World::World(const Size &size, CameraPtr camera)
: size(size)
, player1(nullptr)
, player2(nullptr)
, camera(camera) {
    assert(camera != nullptr);
}

World::~World() {
    
}

void World::setPlayer1(CharacterPtr player1) {
    assert(player1 != nullptr);
    assert(player1->getWorld() == nullptr);
    this->player1 = player1;
    this->player1->setWorld(shared_from_this());
}

void World::setPlayer2(CharacterPtr player2) {
    assert(player2 != nullptr);
    assert(player2->getWorld() == nullptr);
    this->player2 = player2;
    this->player2->setWorld(shared_from_this());
}

void World::handleInput(InputHandlerPtr inputHandler, float dt) {
    
    player1->handleInput(inputHandler, dt);
    player2->handleInput(inputHandler, dt);
    
    for (auto entity : activeEntityList) {
        entity->handleInput(inputHandler, dt);
    }
    
}

void World::update(float dt) {
    
    processQueuedEntities();
    
    for (auto entity : activeEntityList) {
        entity->update(dt);
    }
    
    CharacterPtr playerArray[] = { player1, player2 };
    
    for (auto player : playerArray) {
        
        player->update(dt);
        
        float diff = player1->getPosition().x - player2->getPosition().x;
        float maxDistance = camera->getSize().first - (player1->getSize().first / 2) - (player2->getSize().first / 2);
        
        if (fabs(diff) > maxDistance) {
        
            if (fabs(player->getVelocity().x) > 0) {
                float penetration;
                if (diff < 0) {
                    penetration = -(diff + maxDistance);
                } else {
                    penetration = -(diff - maxDistance);
                }
                
                player->eject(Vector2(penetration * (player == player2 ? -1 : 1), 0));
            }
            
        }
        
        if (player->getPosition().x < camera->getPosition().x - camera->getSize().first / 2 + player->getSize().first / 2) {
            camera->moveBy(Vector2(player->getPosition().x - (camera->getPosition().x - camera->getSize().first / 2 + player->getSize().first / 2), 0));
        } else if (player->getPosition().x > camera->getPosition().x + camera->getSize().first / 2 - player->getSize().first / 2) {
            
            camera->moveBy(Vector2(player->getPosition().x - (camera->getPosition().x + camera->getSize().first / 2 - player->getSize().first / 2), 0));
        }
    }
}

void World::processQueuedEntities() {
    
    for (auto deadEntity : deadEntityList) {
        deadEntity->onRemove();
        activeEntityList.remove(deadEntity);
    }
    deadEntityList.clear();
    
    for (auto newEntity : newEntityList) {
        newEntity->setWorld(shared_from_this());
        activeEntityList.push_back(newEntity);
        newEntity->onAdd();
    }
    newEntityList.clear();
}

void World::draw(ALLEGRO_DISPLAY *display, CameraPtr camera) {
    
    player1->draw(display, camera);
    player2->draw(display, camera);
    
    for (auto entity : activeEntityList) {
        entity->draw(display, camera);
    }
    
    //al_draw_line(0, FloorY, Application::GetInstance()->getWindowWidth(), FloorY, al_map_rgb(0, 0, 255), 2.0f);
}

void World::addEntity(EntityPtr entity) {
    assert(entity != nullptr);
    assert(entity->getWorld() == nullptr);
    assert(std::find(newEntityList.begin(), newEntityList.end(), entity) == newEntityList.end() && "This entity is being added (queued)!");
    assert(std::find(activeEntityList.begin(), activeEntityList.end(), entity) == activeEntityList.end() && "This entity has already been added!");
    
    newEntityList.push_back(entity);
}

void World::removeEntity(EntityPtr entity) {
    assert(entity != nullptr);
    assert(entity->getWorld() == shared_from_this());
    assert(std::find(deadEntityList.begin(), deadEntityList.end(), entity) == deadEntityList.end() && "This entity is being removed (queued)!");
    assert(std::find(activeEntityList.begin(), activeEntityList.end(), entity) != activeEntityList.end() && "This entity doesn't exist in this world!");
    
    deadEntityList.push_back(entity);
}