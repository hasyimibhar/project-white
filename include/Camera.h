//
//  Camera.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#ifndef project_white_Camera_h
#define project_white_Camera_h

#include "MathTypes.h"
#include "DeltaTimer.h"
#include <memory>

namespace AllegroFighters {

    class World;
    typedef std::shared_ptr<World> WorldPtr;
    
    class Camera {
    private:
        WorldPtr world;
        
        // {0, 0} means the center
        Vector2 position;
        
        // The position the last time moveTo was called
        Vector2 start;
        
        // Where to move to
        Vector2 target;
        
        // The view size
        Size    size;
        
        DeltaTimer moveTimer;
        
    public:
        static const float MoveDuration;
        
        Camera(WorldPtr world, const Size &size);
        
        void moveTo(const Vector2 &target);
        void moveBy(const Vector2 &delta);
        void update(float dt);
        
        Vector2 getPosition() const {
            return position;
        }
        
        Vector2 convertToViewCoordinate(const Vector2 &p) const;
    };
    
}

#endif
