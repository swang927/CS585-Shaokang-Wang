// default_allocator.h

#ifndef INCLUDED_DEFAULT_ALLOCATOR
#define INCLUDED_DEFAULT_ALLOCATOR

#include "iallocator.h"

namespace sgdm
{

template<class T> 
class DefaultAllocator : public IAllocator<T> 
{
  protected:
    unsigned int totalAllocationCount;
    unsigned int totalReleaseCount;
    unsigned int allocationCount;
    unsigned int releaseCount;

  public:
    DefaultAllocator();
    ~DefaultAllocator();
    DefaultAllocator(DefaultAllocator const& other);
    DefaultAllocator& operator=(DefaultAllocator const& other);

    T* get(int count);
    void release(T* target_memory, int count);
    int get_count(){ return totalAllocationCount-totalReleaseCount; };
};


template<class T>
DefaultAllocator<T>::DefaultAllocator(){
    this->totalAllocationCount = 0;
    this->totalReleaseCount = 0;
    this->allocationCount = 0;
    this->releaseCount = 0;
};

template<class T>
DefaultAllocator<T>::~DefaultAllocator(){   
};


template<class T>
DefaultAllocator<T>::DefaultAllocator(DefaultAllocator const& other){
    this->totalAllocationCount = other.totalAllocationCount;
    this->totalReleaseCount = other.totalReleaseCount;
    this->allocationCount = other.allocationCount;
    this->releaseCount = other.releaseCount;
};

template<class T>
DefaultAllocator<T>& DefaultAllocator<T>::operator=(DefaultAllocator const& other){
    this->totalAllocationCount = other.totalAllocationCount;
    this->totalReleaseCount = other.totalReleaseCount;
    this->allocationCount = other.allocationCount;
    this->releaseCount = other.releaseCount;
};


template<class T>
T* DefaultAllocator<T>::get(int count){
    this->totalAllocationCount += count;
    this->allocationCount += 1;
    return (T*)::operator new (sizeof(T)*count);
};

template<class T>
void DefaultAllocator<T>::release(T* target_memory, int count){
    this->totalReleaseCount += count;
    this->releaseCount += 1;
    delete target_memory;
};

};


#endif
