//
//  Entity.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#ifndef project_white_Entity_h
#define project_white_Entity_h

#include "MathTypes.h"
#include <memory>

class InputHandler;
typedef std::shared_ptr<InputHandler> InputHandlerPtr;

struct ALLEGRO_DISPLAY;

namespace AllegroFighters {
    class World;
    typedef std::shared_ptr<World> WorldPtr;
    
    class Camera;
    typedef std::shared_ptr<Camera> CameraPtr;
    
    class IEntity {
    public:
        virtual WorldPtr getWorld() const = 0;
        virtual void setWorld(WorldPtr world) = 0;
        
        virtual Vector2 getPosition() const = 0;
        virtual void setPosition(const Vector2 &position) = 0;
        
        virtual Size    getSize() const = 0;
        virtual Rect    getRect() const = 0;
        
        virtual void handleInput(InputHandlerPtr inputHandler, float dt) {};
        virtual void update(float dt) = 0;
        virtual void draw(ALLEGRO_DISPLAY *display, CameraPtr camera) = 0;
        
        virtual void onAdd() {}
        virtual void onRemove() {}
    };
    
    class BaseEntity : public IEntity, public std::enable_shared_from_this<BaseEntity> {
    protected:
        WorldPtr world;
        Vector2 position;
        Size    size;
        
    public:
        BaseEntity(const Vector2 &position, const Size &size)
        : world(nullptr)
        , position(position)
        , size(size) {
        }
        
        WorldPtr getWorld() const {
            return world;
        }
        
        void setWorld(WorldPtr world) {
            assert(this->world == nullptr && "You can only assign the world once!");
            this->world = world;
        }
        
        virtual Vector2 getPosition() const {
            return position;
        }
        
        void setPosition(const Vector2 &position) {
            this->position = position;
        }
        
        virtual Size getSize() const {
            return size;
        }
        
        virtual Rect getRect() const {
            return Rect(Vector2(position.x - size.first / 2, position.y - size.second / 2), size);
        }
    };
}

#endif
