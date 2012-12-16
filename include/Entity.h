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
    class IEntity {
    public:
        virtual Vector2 getPosition() const = 0;
        virtual Size    getSize() const = 0;
        virtual Rect    getRect() const = 0;
        
        virtual void handleInput(InputHandlerPtr inputHandler, float dt) {};
        virtual void update(float dt) = 0;
        virtual void draw(ALLEGRO_DISPLAY *display) = 0;
        
        virtual void onAdd() {}
        virtual void onRemove() {}
    };
    
    class BaseEntity : public IEntity, public std::enable_shared_from_this<BaseEntity> {
    private:
        Vector2 position;
        Size    size;
        
    public:
        BaseEntity(const Vector2 &position, const Size &size)
        : position(position)
        , size(size) {
            
        }
        
        virtual Vector2 getPosition() const {
            return position;
        }
        
        virtual Size getSize() const {
            return size;
        }
        
        virtual Rect getRect() const {
            return Rect(position, size);
        }
    };
}

#endif
