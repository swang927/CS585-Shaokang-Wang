// iallocator.h

#ifndef INCLUDED_IALLOCATOR
#define INCLUDED_IALLOCATOR

namespace sgdm
{

template<class T> 
class IAllocator {
  public:
    virtual T* get(int count) =0;
    virtual void release(T* target_memory, int count) = 0;
};


};
#endif
