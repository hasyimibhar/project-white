//
//  MathTypes.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#include "MathTypes.h"

//////////////////////////////////////////
// Size helper functions
Size MakeSize(float width, float height)
{
    return std::make_pair(width, height);
}

//////////////////////////////////////////
// Rect helper functions
Rect OffsetRect(const Rect &r, const Vector2 &offset)
{
    return Rect(r.getOrigin() + offset, r.getSize());
}