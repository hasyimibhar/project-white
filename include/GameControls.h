//
//  GameControls.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/17/12.
//
//

#ifndef project_white_GameControls_h
#define project_white_GameControls_h

#include <map>
#include <string>
#include <cassert>
#include <algorithm>
#include "InputHandler.h"

typedef std::shared_ptr<InputHandler> InputHandlerPtr;

namespace AllegroFighters {
    
    enum GameCommand {
        GameCommandMoveLeft = 0,
        GameCommandMoveRight,
        GameCommandMoveDown,
        GameCommandJump,
        GameCommandPunch,
        GameCommandKick
    };
    
    typedef std::map<GameCommand, KeyboardKey> CommandKeyMap;
    
    std::string GetGameCommandString(GameCommand command);
    
    class ControlsManager {
    private:
        CommandKeyMap commandKeyMap;
        
    public:
        static const KeyboardKey DefaultMoveLeftKey;
        static const KeyboardKey DefaultMoveRightKey;
        static const KeyboardKey DefaultMoveDownKey;
        static const KeyboardKey DefaultJumpKey;
        static const KeyboardKey DefaultPunchKey;
        static const KeyboardKey DefaultKickKey;
        
        ControlsManager(const std::string &configFilename = "");
        
        void bindCommand(GameCommand command, KeyboardKey key);
        void unbindCommand(GameCommand command);
        
        KeyboardKey getKey(GameCommand command) const {
            assert(commandKeyMap.find(command) != commandKeyMap.end());
            return commandKeyMap.at(command);
        }
        
        GameCommand getCommand(KeyboardKey key) const {
            auto result = std::find_if(commandKeyMap.begin(), commandKeyMap.end(), [key](std::pair<GameCommand, KeyboardKey> v) {
                return v.second == key;
            });
            assert(result != commandKeyMap.end());
            return result->first;
        }
        
        bool isKeyDown(InputHandlerPtr inputHandler, GameCommand command) const;
        bool isKeyUp(InputHandlerPtr inputHandler, GameCommand command) const;
        bool isKeyPressed(InputHandlerPtr inputHandler, GameCommand command) const;
        bool isKeyReleased(InputHandlerPtr inputHandler, GameCommand command) const;
    };
}

#endif
