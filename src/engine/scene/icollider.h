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
    virtual const RectangleBounds& bounds() const = 0 ;  
    virtual unsigned short shortflags() const = 0;
    virtual void setFlags(unsigned short flags) = 0;
    virtual bool canCollide(unsigned short flags) const = 0;
    virtual bool doesCollide(const RectangleBounds& candidate) = 0;
	virtual int getCell() = 0;
	virtual void setCell(int index) = 0;
};


};

#endif