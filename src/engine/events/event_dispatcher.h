// event_dispatcher.h

#ifndef INCLUDED_IEVENT_DISPATCHER
#define INCLUDED_IEVENT_DISPATCHER

#include <string>
#include <functional>
#include "ievent.h" 
#include "../scene/itickable.h"

namespace sgde{
// Re-entrant wrapper around an event broadcasting systems.
// use the post-tick to add/remove listeners and 
// calling the dispatch function will immediately 
// dispatch the event to all listeners
class EventDispatcher : public sgds::ITickable{

  public:
	void add(const std::string& type, std::function<void(const IEvent&)>* listener);
	void remove(const std::string& type, std::function<void(const IEvent&)>* listener);
	// called as part of tick, synchronous
	void dispatch(IEvent& const);


	// implement ITickable
	// pre-process, probably does nothing
    void preTick();
	// process, probably does nothing
    void tick(float dtS);
	// post-process, should add/remove any listeners
    void postTick();

}; // end of class


} // end of namespace
#endif

