// IActor.h

#ifndef INCLUDED_IACTOR
#define INCLUDED_IACTOR


#include "../../engine/scene/icollider.h"
#include "../../engine/rendering/renderable_sprite.h"

namespace sgda
{
// A simple abstract class for actor
class IActor : public sgds::ICollider{
  public:
	  sgdr::RenderableSprite d_sprite;
	  sgds::RectangleBounds d_bound;

	  virtual const sgds::RectangleBounds& bounds() const = 0;
	  virtual unsigned short shortflags() const = 0;
	  virtual void setFlags(unsigned short flags) = 0;
	  virtual bool canCollide(unsigned short flags) const = 0;
	  virtual bool doesCollide(const sgds::RectangleBounds& candidate) = 0;
};

};

#endif