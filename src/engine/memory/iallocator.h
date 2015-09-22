// iallocator.h

#include <string>

#ifndef INCLUDED_IALLOCATOR
#define INCLUDED_IALLOCATOR

namespace sgdm
{


template<class T>
class IAllocator {
  public:
    virtual T* get(int count) =0;
    virtual void release(T* pointer, int count) = 0;
    virtual void construct(T* pointer, const T& copy) = 0;
    virtual void destruct(T* pointer) = 0;
    virtual void construct(T* pointer) = 0;

    template<class U, class... Args>
    void construct(U* pointer, Args&&... args);

};


};
#endif
