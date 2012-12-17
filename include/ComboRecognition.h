//
//  ComboRecognition.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/17/12.
//
//

#ifndef project_white_ComboRecognition_h
#define project_white_ComboRecognition_h

#include "GameControls.h"
#include "DeltaTimer.h"
#include "FastDelegate.h"
#include <vector>
#include <list>
#include <map>

using namespace fastdelegate;

class InputHandler;
typedef std::shared_ptr<InputHandler> InputHandlerPtr;
typedef unsigned char KeyboardKey;

namespace AllegroFighters {
    
    class ControlsManager;
    typedef std::shared_ptr<ControlsManager> ControlsManagerPtr;
    
    typedef std::vector<KeyboardKey> KeyArray;
    typedef FastDelegate1<const std::string&> OnComboMatched;
    typedef std::list<OnComboMatched> DelegateList;
    
    class Combo;
    typedef std::shared_ptr<Combo> ComboPtr;
    
    class Combo : public std::enable_shared_from_this<Combo> {
    private:
        std::string name;
        KeyArray keyArray;
        KeyArray accumulatedKeys;
        float maxDelay;
        DeltaTimer timer;
        DelegateList delegateList;
        
    public:
        Combo(const std::string &name, float maxDelay);
        
        ComboPtr key(KeyboardKey key);
        void accumulateKey(KeyboardKey key);
        
        void update(float dt);
        void addDelegate(OnComboMatched delegate);
        void removeDelegate(OnComboMatched delegate);
        
        std::string getName() const {
            return name;
        }
    };
    
    typedef std::map<std::string, ComboPtr> ComboMap;
    
    class ComboManager {
    private:
        ComboMap comboMap;
        InputHandlerPtr inputHandler;
        
    public:
        ComboManager(InputHandlerPtr inputHandler);
        ~ComboManager();
        
        ComboPtr addCombo(ComboPtr combo);
        void update(float dt);
        
        void onKeyDown(KeyboardKey key);
        
        ComboPtr getCombo(const std::string &name) const {
            assert(comboMap.find(name) != comboMap.end());
            return comboMap.at(name);
        }
    };
}

#endif
