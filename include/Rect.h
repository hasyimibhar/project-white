//
//  Rect.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#ifndef project_white_Rect_h
#define project_white_Rect_h

#include "Vector2.h"
#include <cassert>
#include <utility>

typedef std::pair<float, float> Size;
Size MakeSize(float width, float height);

class Rect {
private:
    void init(const Vector2 &min, const Vector2 &max) {
        assert(min <= max);
        this->min = min;
        this->max = max;
    }
    
public:
    Vector2 min, max;
    
    Rect() {
        init(Vector2(), Vector2());
    }
    
    Rect(const Vector2 &min, const Vector2 &max) {
        init(min, max);
    }
    
    Rect(const Vector2& origin, const Size &size) {
        init(origin, Vector2(origin.x + size.first, origin.y + size.second));
    }
    
    bool containsPoint(const Vector2 &p) {
        return (p.x >= min.x &&
                p.x <= max.x &&
                p.y >= min.y &&
                p.y <= max.y);
    }
    
    bool containsRect(const Rect &r) {
        return (r.min >= min && r.max <= max);
    }
    
    bool intersectsRect(const Rect &r) {
        return !((r.min.x > max.x) ||
                 (r.max.x < min.x) ||
                 (r.min.y > max.y) ||
                 (r.max.y < min.y));
    }
};

#endif
