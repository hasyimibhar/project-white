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

#include <allegro5/allegro.h>
#include <algorithm>

using namespace AllegroFighters;

const float World::FloorY   = 500.0f;

World::World(const Size &size) : size(size) {
    
}

World::~World() {
    
}

void World::handleInput(InputHandlerPtr inputHandler, float dt) {
    
    for (auto entity : activeEntityList) {
        entity->handleInput(inputHandler, dt);
    }
    
}

void World::update(float dt) {
    
    processQueuedEntities();
    
    for (auto entity : activeEntityList) {
        entity->update(dt);
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
    
    for (auto entity : activeEntityList) {
        entity->draw(display, camera);
    }
    
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