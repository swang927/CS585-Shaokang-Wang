// event_bus.h
    
#ifndef INCLUDED_IEVENT_BUS
#define INCLUDED_IEVENT_BUS

#include "event_dispatcher.h"

namespace sgde{

class EventBus : public sgds::ITickable
{
  private:
      unsigned int d_queueSize = 1000;
      EventDispatcher d_evDispatcher;
      sgdc::DynamicArray<const IEvent*> d_eventQueue;

  public:
    //ACCESSORS
    static EventBus& inst();
    // MUTATORS
    void setQueueSize(unsigned int size);

    // MEMBER FUNCTIONS
    // return false if queue is full.
    bool addEvent(const IEvent & ev);
    // return false if the event is not there.
    bool removeEvent(const IEvent & ev);
    

    void registerListener(const IEvent & ev, EventListenerCallbacksPtr listener);
    void logoutListener(const IEvent & ev, EventListenerCallbacksPtr listener);

    // trigger event at once without adding to the event queue.
    void triggerEvent(const IEvent & ev);
    
    void preTick() override;
    void tick(float dtSec) override;
    void postTick() override;
};


//ACCESSORS
inline
EventBus& EventBus::inst(){
    static EventBus inst;
    return inst;
}


// Set event Queue 
inline
void EventBus::setQueueSize(unsigned int size)
{
    d_queueSize = size;
}


// add event to event queue, return false if queue is full.
inline
bool EventBus::addEvent(const IEvent & ev)
{
    if (d_queueSize == d_eventQueue.getLength()){
        // this makes d_eventQ fixed size.
        return false;
    }
    d_eventQueue.push(&ev);
    return true;
}


// remove event from event queue, return false if event is not there .
inline
bool EventBus::removeEvent(const IEvent & ev)
{
    unsigned int size = d_eventQueue.getLength();
    bool ret = false;
    for (unsigned int i = 0; i < size; ++i)
    {
        if (d_eventQueue[i]->type() == ev.type())
        {
            d_eventQueue.removeAt(i);
            ret = true;
        }
    }
    return ret;
}


// register event listener
inline
void EventBus::registerListener(const IEvent & ev, EventListenerCallbacksPtr listener){
    d_evDispatcher.add(ev.type(), listener);
}

// log out the event listener
inline
void EventBus::logoutListener(const IEvent & ev,EventListenerCallbacksPtr listener)
{
    d_evDispatcher.remove(ev.type(), listener);
}


// trigger event at once without adding to the event queue.
inline
void EventBus::triggerEvent(const IEvent & ev){
    d_evDispatcher.dispatch(ev);
}


// ITickable Member function
inline
void EventBus::preTick(){
}

inline
void EventBus::tick(float dtSec){
}

inline
void EventBus::postTick()
{
    unsigned int size = d_eventQueue.getLength();
    for (unsigned int i = 0; i < size; ++i)
    {
        d_evDispatcher.dispatch(*(d_eventQueue[i]));
    }
    d_eventQueue.clean();
}

}; // end of namespace

#endif