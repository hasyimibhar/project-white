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
#include <list>
#include "MathTypes.h"

struct ALLEGRO_DISPLAY;

class InputHandler;
typedef std::shared_ptr<InputHandler> InputHandlerPtr;

namespace AllegroFighters {
    
    class Camera;
    typedef std::shared_ptr<Camera> CameraPtr;
    
    class IEntity;
    typedef std::shared_ptr<IEntity> EntityPtr;
    
    class Character;
    typedef std::shared_ptr<Character> CharacterPtr;
    
    typedef std::list<EntityPtr> EntityList;
 
    // The world where the fighters rumble!
    class World : public std::enable_shared_from_this<World> {
    private:
        const Size size;
        
        EntityList activeEntityList, newEntityList, deadEntityList;
        CharacterPtr player1, player2;
        CameraPtr camera;
        
        void processQueuedEntities();
        
    public:
        static const float FloorY;
        static const float GravityAcceleration;
        
        World(const Size &size, CameraPtr camera);
        ~World();
        
        void setPlayer1(CharacterPtr player1);
        void setPlayer2(CharacterPtr player1);
        
        void handleInput(InputHandlerPtr inputHandler, float dt);
        void update(float dt);
        void draw(ALLEGRO_DISPLAY *display, CameraPtr camera);
        
        void addEntity(EntityPtr entity);
        void removeEntity(EntityPtr entity);
        
        Size getSize() const {
            return size;
        }
    };

}

#endif
