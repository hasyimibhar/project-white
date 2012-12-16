//
//  World.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#ifndef project_white_World_h
#define project_white_World_h

#include <memory>
#include "MathTypes.h"

struct ALLEGRO_DISPLAY;

class InputHandler;
typedef std::shared_ptr<InputHandler> InputHandlerPtr;

namespace AllegroFighters {
 
    // The world where the fighters rumble!
    class World {
    public:
        static const float FloorY;
        static const Size Size;
        
        World();
        ~World();
        
        void handleInput(InputHandlerPtr inputHandler, float dt);
        void update(float dt);
        void draw(ALLEGRO_DISPLAY *display);
    };

}

#endif
