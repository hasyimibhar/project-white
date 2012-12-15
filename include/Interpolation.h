//
//  Interpolation.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/15/12.
//
//

#ifndef project_white_Interpolation_h
#define project_white_Interpolation_h

#include "Elves.h"
#include <cmath>

enum InterpolationType {
    EaseIn,
    EaseOut,
    EaseInOut
};

template <typename T>
class Interpolation {
    
public:

    static T Linear(float   time,
                    T       start,
                    T       end) {
        
        // Make sure the time is normalized
        time = clamp(time, 0.0f, 1.0f);
        return start + (end - start) * time;
        
    }
    
    static T Quadratic(float                time,
                       T                    start,
                       T                    end,
                       InterpolationType    type = EaseInOut) {
        
        // Make sure the time is normalized
        time = clamp(time, 0.0f, 1.0f);
        
        
        if (type == EaseIn) {
            return start + (end - start) * time * time;
        } else if (type == EaseOut) {
            return start - (end - start) * time * (time - 2);
        } else if (type == EaseInOut) {
            
            time *= 2;
            
            if (time < 1) {
                return start + ((end - start) / 2) * time * time;
            } else {
                time -= 1;
                return start - ((end - start) / 2) * (time * (time - 2) - 1);
            }

        } else {
            assert(!"Invalid type!");
        }
        
    }
    
    static T Exponential(float              time,
                         T                  start,
                         T                  end,
                         InterpolationType  type = EaseInOut) {
        
        // Make sure the time is normalized
        time = clamp(time, 0.0f, 1.0f);
        
        if (type == EaseIn) {
            
            return start + (end - start) * powf(2, 10 * (time - 1));
     
        } else if (type == EaseOut) {
            
            return start + (end - start) * (-powf(2, -10 * time) + 1);
            
        } else if (type == EaseInOut) {
            
            time *= 2;
            
            if (time < 1) {
                return start + ((end - start) / 2) * powf(2, 10 * (time - 1));
            } else {
                time -= 1;
                return start + ((end - start) / 2) * (-powf(2, -10 * time) + 2);
            }
            
        } else {
            assert(!"Invalid type!");
        }
        
    }
    
};

#endif
