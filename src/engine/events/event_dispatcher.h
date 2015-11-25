// event_dispatcher.h

#ifndef INCLUDED_IEVENT_DISPATCHER
#define INCLUDED_IEVENT_DISPATCHER

#include <string>
#include <assert.h>
#include <functional>
#include "../scene/itickable.h"
#include "ievent.h"
#include "../containers/map.h"

namespace sgde{

typedef std::function<void(const IEvent &)>* EventListenerCallbacksPtr;
typedef sgdc::DynamicArray<EventListenerCallbacksPtr> EventListenerPtrList;

// Re-entrant wrapper around an event broadcasting systems.
// use the post-tick to add/remove listeners and 
// calling the dispatch function will immediately 
// dispatch the event to all listeners
class EventDispatcher : public sgds::ITickable{
  private:
	// store a map of listeners ready for exec.
	// listeners have to manage themslves.
	sgdc::Map<EventListenerPtrList> d_listeners;
	
	//DELETED
	EventDispatcher(const EventDispatcher &) = delete;
	EventDispatcher(EventDispatcher &&) = delete;
	EventDispatcher& operator=(const EventDispatcher &) = delete;
	EventDispatcher& operator=(EventDispatcher &&) = delete;

  public:
	// constructor
	EventDispatcher();
	// deconstructor
	~EventDispatcher();

	void add(const std::string& type, EventListenerCallbacksPtr listener);
	void remove(const std::string& type, EventListenerCallbacksPtr listener);
	// called as part of tick, synchronous
	void dispatch(const IEvent& ev);

	// implement ITickable
	// pre-process, probably does nothing
    void preTick();
	// process, probably does nothing
    void tick(float dtS);
	// post-process, should add/remove any listeners
    void postTick();

}; // end of class


// CONSTRUCTORS
inline
EventDispatcher::EventDispatcher(){
}

// DESTRUCTOR
inline
EventDispatcher::~EventDispatcher(){
}

// dispath the event to all relatived listeners 
inline
void EventDispatcher::dispatch(const IEvent & ev)
{
	std::string evType = ev.type();

	if (d_listeners.has(evType))
	{
		unsigned int size = d_listeners[evType].getLength();
		for (unsigned int i = 0; i < size; ++i){
			EventListenerCallbacksPtr evCallbackPtr = d_listeners[evType][i];
			if (evCallbackPtr && *evCallbackPtr){
				(*evCallbackPtr)(ev);
			}
		}
	}
}

// add a new event listener to certain type of event
inline
void EventDispatcher::add(const std::string& type, EventListenerCallbacksPtr listener)
{
	assert(listener);
	d_listeners[type].push(listener);
}

// remove the event listener for certain type of event
inline
void EventDispatcher::remove(const std::string& eventName, EventListenerCallbacksPtr listener)
{
	assert(listener);
	assert(d_listeners.has(eventName));
	unsigned int size = d_listeners[eventName].getLength();
	for (unsigned int i = 0; i < size; ++i)
	{
		if (d_listeners[eventName][i] == listener){
			d_listeners[eventName].removeAt(i);
		}
	}
}


// MEMBER FUNCTIONS
inline
void EventDispatcher::preTick(){
}

inline
void EventDispatcher::tick(float dtSec){
}

inline
void EventDispatcher::postTick(){
}

} // end of namespace
#endif

