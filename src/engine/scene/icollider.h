// icollider.h
    
#ifndef INCLUDED_ICOLLIDER
#define INCLUDED_ICOLLIDER

#include "rectangle_bounds.h"

namespace sgds
{
// A simple interface for defining the bounds of collision and flags appropriate for colliding
class ICollider {
  public:
    // We could replace this to abstract away
    virtual const RectangleBounds& bounds() const;  
    virtual unsigned short shortflags() const;
    virtual void setFlags(unsigned short flags);
    virtual bool canCollide(unsigned short flags) const;
    virtual bool doesCollide(const RectangleBounds& candidate);
};


};

#endif