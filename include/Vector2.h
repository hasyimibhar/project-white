//
//  Vector2.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#ifndef project_white_Vector2_h
#define project_white_Vector2_h

#include <cmath>

// 2d vector class
// I don't know why I end up rewriting this class
// for every single project. I'm a bad programmer. :(
class Vector2 {
public:
    float x, y;
    
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}
    
    ////////////////////////////
    // Operator overloads
    Vector2 &operator=(const Vector2 &v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
        }
        
        return *this;
    }
    
    const Vector2 operator+(const Vector2 &v) const {
        return Vector2(x + v.x, y + v.y);
    }
    
    const Vector2 operator-(const Vector2 &v) const {
        return Vector2(x - v.x, y - v.y);
    }
    
    const Vector2 operator*(const float c) const {
        return Vector2(x * c, y * c);
    }
    
    const Vector2 operator/(const float c) const {
        return Vector2(x / c, y / c);
    }
    
    Vector2 &operator+=(const Vector2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    
    Vector2 &operator-=(const Vector2 &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    
    Vector2 &operator*=(const float c) {
        x *= c;
        y *= c;
        return *this;
    }

    Vector2 &operator/=(const float c) {
        x /= c;
        y /= c;
        return *this;
    }
    
    ////////////////////////////
    // The usual vector operations
    float getSquaredLength() const {
        return x * x + y * y;
    }
    
    float getLength() const {
        return sqrtf(getSquaredLength());
    }
    
    Vector2 getNormalized() const {
        float length = getLength();
        return Vector2(x / length, y / length);
    }
    
    float getDotProduct(const Vector2 &v) const {
        return x * v.x + y * v.y;
    }

    float getSquaredDistance(const Vector2 &v) const {
        return (v - *this).getSquaredLength();
    }

    float getDistance(const Vector2 &v) const {
        return sqrtf(getSquaredDistance(v));
    }
};

#endif
