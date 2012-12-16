//
//  Character.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#ifndef project_white_Character_h
#define project_white_Character_h

#include "Entity.h"

namespace AllegroFighters {
    class Character;
    typedef std::shared_ptr<Character> CharacterPtr;
    
    class Character : public BaseEntity {
    public:
        Character();
        ~Character();
        
        void handleInput(InputHandlerPtr inputHandler, float dt);
        void update(float dt);
        void draw(ALLEGRO_DISPLAY *display, CameraPtr camera);
    };
}

#endif
