//
//  Camera.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#include "Camera.h"
#include "Elves.h"
#include "World.h"
#include "Interpolation.h"
#include "Entity.h"

#include <cassert>

using namespace AllegroFighters;

const float Camera::MoveDuration = 1.0f;

Camera::Camera(WorldPtr world, const Size &size)
: world(world)
, size(size)
, position(Vector2())
, start(position)
, target(position) {
    // World must not be null
    assert(world != nullptr);
    
    // Size must be smaller than the world's
    assert(size.first <= world->getSize().first && size.second <= world->getSize().second);
    
    moveTimer.setTimeInterval(MoveDuration);
}

void Camera::moveTo(const Vector2 &target) {
    start = position;
    this->target = clamp(target,
                         Vector2((size.first / 2) - (world->getSize().first / 2), 0),
                         Vector2((world->getSize().first / 2) - (size.first / 2), 0));
    
    moveTimer.setTimeInterval(MoveDuration);
}

void Camera::moveBy(const Vector2 &delta) {
    moveTo(position + delta);
}

void Camera::update(float dt) {
    moveTimer.update(dt);
    this->position = Interpolation<Vector2>::Quadratic(moveTimer.getNormalizedTime(), start, target, EaseOut);
}

Vector2 Camera::convertToViewCoordinate(const Vector2 &p) const {
    return p + Vector2(size.first / 2, 0) + position;
}