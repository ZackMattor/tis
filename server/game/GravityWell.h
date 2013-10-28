#ifndef GRAVITYWELL_H
#define GRAVITYWELL_H

#include "Vector2D.h"

class GravityWell
{
public:
    GravityWell();
private:
    float m_mass;
    Vector2D m_location;
};

#endif // GRAVITYWELL_H
