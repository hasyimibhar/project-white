//
//  Character.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#include "Character.h"
#include "InputHandler.h"
#include "World.h"
#include "Camera.h"
#include "Elves.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace AllegroFighters;

const float Character::JumpSpeed = -1000;
const float Character::MoveSpeed = 400;

Character::Character()
: BaseEntity(Vector2(), MakeSize(140, 200))
, velocity(Vector2())
, isJumping(false) {
    
}

Character::~Character() {
    
}

void Character::update(float dt) {
    velocity.y += World::GravityAcceleration * dt;
    position += velocity * dt;
    
    if (position.y + size.second / 2 > World::FloorY) {
        velocity.y = 0;
        position.y = World::FloorY - size.second / 2;
        isJumping = false;
    }
    
    if (position.x - size.first / 2 < -world->getSize().first / 2) {
        position.x = (-world->getSize().first / 2) + (size.first / 2);
    } else if (position.x + size.first / 2 > world->getSize().first / 2) {
        position.x = (world->getSize().first / 2) - (size.first / 2);
    }
}

void Character::draw(ALLEGRO_DISPLAY *display, CameraPtr camera) {
    
    Rect rect = OffsetRect(getRect(), camera->getOffset());
    al_draw_filled_rectangle(
                             rect.getLeft(),
                             rect.getTop(),
                             rect.getRight(),
                             rect.getBottom(),
                             al_map_rgb(255, 0, 0));
    
}

void Character::jump() {
    if (!isJumping) {
        velocity.y = JumpSpeed;
        isJumping = true;
    }
}

void Character::move(Direction direction) {
    velocity.x = (int)direction * MoveSpeed;
}

void Character::stop() {
    velocity.x = 0;
}