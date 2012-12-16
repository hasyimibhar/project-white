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

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace AllegroFighters;

Character::Character()
: BaseEntity(Vector2(), MakeSize(140, 200)) {
    
}

Character::~Character() {
    
}

void Character::handleInput(InputHandlerPtr inputHandler, float dt) {
    
}

void Character::update(float dt) {
    
}

void Character::draw(ALLEGRO_DISPLAY *display, CameraPtr camera) {
    
    Rect rect = OffsetRect(getRect(), camera->convertToViewCoordinate(position));
    al_draw_filled_rectangle(
                             rect.getLeft(),
                             rect.getTop(),
                             rect.getRight(),
                             rect.getBottom(),
                             al_map_rgb(255, 0, 0));
    
}