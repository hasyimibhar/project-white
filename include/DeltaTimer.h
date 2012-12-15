//
//  DeltaTimer.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#ifndef project_white_DeltaTimer_h
#define project_white_DeltaTimer_h

#include <allegro5/allegro.h>
#include <cassert>

class DeltaTimer {
  
private:
    float       timeElapsed;
    float       timeInterval;
    bool        isSet;
    
public:
    DeltaTimer(): timeInterval(0.0f), timeElapsed(0.0f), isSet(false) {
    }
    
    void setTimeInterval(float timeInterval) {
        assert(timeInterval > 0);
        isSet = true;
        this->timeInterval = timeInterval;
        reset();
    }
    
    void reset() {
        assert(isSet && "Timer is not set yet!");
        timeElapsed = 0.0f;
    }
    
    void update(float dt) {
        if (!isOver()) {
            timeElapsed += dt;
        }
    }
    
    bool isOver() const {
        assert(isSet && "Timer is not set yet!");
        return timeElapsed > timeInterval;
    }
};

#endif
