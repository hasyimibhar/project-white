//
//  GameControls.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/17/12.
//
//

#include "GameControls.h"
#include <allegro5/allegro.h>
#include "Elves.h"

using namespace AllegroFighters;

std::string AllegroFighters::GetGameCommandString(GameCommand command) {
    
    std::string commandString = "";
    
    switch (command) {
        case GameCommandMoveLeft:
            commandString = "moveleft";
            break;
            
        case GameCommandMoveRight:
            commandString = "moveright";
            break;
            
        case GameCommandMoveDown:
            commandString = "movedown";
            break;
            
        case GameCommandJump:
            commandString = "jump";
            break;
            
        case GameCommandPunch:
            commandString = "punch";
            break;
            
        case GameCommandKick:
            commandString = "kick";
            break;
            
        default:
            assert(!"Invalid game command!");
            return "";
            break;
    }
    
    return commandString;
}

const KeyboardKey ControlsManager::DefaultMoveLeftKey = ALLEGRO_KEY_LEFT;
const KeyboardKey ControlsManager::DefaultMoveRightKey = ALLEGRO_KEY_RIGHT;
const KeyboardKey ControlsManager::DefaultMoveDownKey = ALLEGRO_KEY_DOWN;
const KeyboardKey ControlsManager::DefaultJumpKey = ALLEGRO_KEY_UP;
const KeyboardKey ControlsManager::DefaultPunchKey = ALLEGRO_KEY_X;
const KeyboardKey ControlsManager::DefaultKickKey = ALLEGRO_KEY_Z;

ControlsManager::ControlsManager(const std::string &configFilename)
{
    bindCommand(GameCommandMoveLeft,    DefaultMoveLeftKey);
    bindCommand(GameCommandMoveRight,   DefaultMoveRightKey);
    bindCommand(GameCommandMoveDown,    DefaultMoveDownKey);
    bindCommand(GameCommandJump,        DefaultJumpKey);
    bindCommand(GameCommandPunch,       DefaultPunchKey);
    bindCommand(GameCommandKick,        DefaultKickKey);
    
    if (!configFilename.empty()) {
        
        ALLEGRO_CONFIG *configFile = al_load_config_file(configFilename.c_str());
        
        if (configFile == NULL) {
            throw std::runtime_error("Config file is missing!");
        } else {
            const std::string commandStringArray[] = {
                GetGameCommandString(GameCommandMoveLeft),
                GetGameCommandString(GameCommandMoveRight),
                GetGameCommandString(GameCommandMoveDown),
                GetGameCommandString(GameCommandJump),
                GetGameCommandString(GameCommandPunch),
                GetGameCommandString(GameCommandKick)
            };
            
            int commandIndex = 0;
            for (auto commandString : commandStringArray) {
                const char *keyString = al_get_config_value(configFile, "key", commandString.c_str());
                if (keyString) {
                    bindCommand((GameCommand)commandIndex, (GameCommand)from_string<int>(std::string(keyString)));
                }
                
                ++commandIndex;
            }
        }
    }
}

void ControlsManager::bindCommand(GameCommand command, KeyboardKey key) {
    commandKeyMap[command] = key;
}

void ControlsManager::unbindCommand(GameCommand command) {

    if (commandKeyMap.find(command) == commandKeyMap.end()) {
        throw std::runtime_error("Command has not been binded yet!");
    }
    
    commandKeyMap.erase(command);
}

bool ControlsManager::isKeyDown(InputHandlerPtr inputHandler, GameCommand command) const {
    assert(commandKeyMap.find(command) != commandKeyMap.end());
    return inputHandler->isKeyDown(commandKeyMap.at(command));
}

bool ControlsManager::isKeyUp(InputHandlerPtr inputHandler, GameCommand command) const {
    assert(commandKeyMap.find(command) != commandKeyMap.end());
    return inputHandler->isKeyUp(commandKeyMap.at(command));
}

bool ControlsManager::isKeyPressed(InputHandlerPtr inputHandler, GameCommand command) const {
    assert(commandKeyMap.find(command) != commandKeyMap.end());
    return inputHandler->isKeyPressed(commandKeyMap.at(command));
}

bool ControlsManager::isKeyReleased(InputHandlerPtr inputHandler, GameCommand command) const {
    assert(commandKeyMap.find(command) != commandKeyMap.end());
    return inputHandler->isKeyReleased(commandKeyMap.at(command));
}