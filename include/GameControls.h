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
#include "InputHandler.h"

typedef std::shared_ptr<InputHandler> InputHandlerPtr;

namespace AllegroFighters {
    
    enum GameCommand {
        GameCommandMoveLeft = 0,
        GameCommandMoveRight,
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
        static const KeyboardKey DefaultJumpKey;
        static const KeyboardKey DefaultPunchKey;
        static const KeyboardKey DefaultKickKey;
        
        ControlsManager(const std::string &configFilename = "");
        
        void bindCommand(GameCommand command, KeyboardKey key);
        void unbindCommand(GameCommand command);
        
        bool isKeyDown(InputHandlerPtr inputHandler, GameCommand command) const;
        bool isKeyUp(InputHandlerPtr inputHandler, GameCommand command) const;
        bool isKeyPressed(InputHandlerPtr inputHandler, GameCommand command) const;
        bool isKeyReleased(InputHandlerPtr inputHandler, GameCommand command) const;
    };
}

#endif
