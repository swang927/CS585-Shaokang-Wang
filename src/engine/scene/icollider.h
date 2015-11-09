// icollider.h

#ifndef INCLUDED_ICOLLIDER
#define INCLUDED_ICOLLIDER

#include "rectangle_bounds.h"

namespace sgds
{
class ICollider {
  public:
	// We could replace this to abstract away
	virtual const RectangleBounds& bounds() const;   
	virtual unsigned short shortflags() const;
	virtual void setFlags(unsigned short flags);
	virtual bool canCollide(unsigned short flags) const;
	virtual bool doesCollide(const RectangleBounds& candidate);
};

/*
inline
const RectangleBounds& ICollider::bounds() const{

}

inline
unsigned short ICollider::shortflags() const{

}

inline
void ICollider::setFlags(unsigned short flags){

}

inline
bool ICollider::canCollide(unsigned short flags) const{
}

inline
bool ICollider::doesCollide(const RectangleBounds& candidate){
}
*/

};

#endif