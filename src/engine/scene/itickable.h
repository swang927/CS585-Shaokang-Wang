// itickable.h

#ifndef INCLUDED_ITICKABLE
#define INCLUDED_ITICKABLE

#include <string>

namespace sgds
{
// Simple interface (pure abstract class) for tracking an individual unit of game time in the world
class ITickable {
  public:
    virtual	void preTick() = 0;
	virtual	void tick(float dtS) = 0;
	virtual	void postTick() = 0;	
};

};
#endif