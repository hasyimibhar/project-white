//
//  ComboRecognition.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/17/12.
//
//

#include "ComboRecognition.h"
#include "InputHandler.h"
#include <cassert>

using namespace AllegroFighters;

Combo::Combo(const std::string &name, float maxDelay)
: name(name)
, maxDelay(maxDelay)
{
    assert(!name.empty());
    assert(maxDelay > 0);
    timer.setTimeInterval(maxDelay);
}

ComboPtr Combo::key(KeyboardKey key) {
    keyArray.push_back(key);
    return shared_from_this();
}

void Combo::accumulateKey(KeyboardKey key) {
 
    if (key == keyArray[accumulatedKeys.size()]) {
        accumulatedKeys.push_back(key);
        
        if (accumulatedKeys.size() == keyArray.size()) {
            for (auto d : delegateList) {
                d(name);
            }
            
            accumulatedKeys.clear();
        }
    } else {
        accumulatedKeys.clear();
    }
    
    timer.setTimeInterval(maxDelay);
    
}

void Combo::update(float dt) {
    timer.update(dt);
    
    if (timer.isOver()) {
        accumulatedKeys.clear();
    }
}

void Combo::addDelegate(OnComboMatched delegate) {
    delegateList.push_back(delegate);
}

void Combo::removeDelegate(OnComboMatched delegate) {
    delegateList.remove(delegate);
}

ComboManager::ComboManager(InputHandlerPtr inputHandler)
: inputHandler(inputHandler) {
    assert(inputHandler != nullptr);
    inputHandler->addKeyDownDelegate(MakeDelegate(this, &ComboManager::onKeyDown));
}

ComboManager::~ComboManager() {
    inputHandler->removeKeyDownDelegate(MakeDelegate(this, &ComboManager::onKeyDown));
}

ComboPtr ComboManager::addCombo(ComboPtr combo) {
    assert(comboMap.find(combo->getName()) == comboMap.end());
    comboMap[combo->getName()] = combo;
    return combo;
}

void ComboManager::update(float dt) {
    for (auto comboPair : comboMap) {
        ComboPtr combo = comboPair.second;
        combo->update(dt);
    }
}

void ComboManager::onKeyDown(KeyboardKey key) {
    
    for (auto comboPair : comboMap) {
        ComboPtr combo = comboPair.second;
        combo->accumulateKey(key);
    }
}