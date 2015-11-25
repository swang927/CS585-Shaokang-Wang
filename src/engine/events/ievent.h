// ievent.h

#ifndef INCLUDED_IEVENT
#define INCLUDED_IEVENT

#include <string>

namespace sgde{
class IEvent {
  public:
	// String or enum (if you want) to provide info
	virtual const std::string type() const = 0;
	
}; // end of class


} // end of namespace
#endif