// counting_allocator.h

#ifndef INCLUDED_COUNTING_ALLOCATOR
#define INCLUDED_COUNTING_ALLOCATOR

# include "default_allocator.h"

namespace sgdm
{
template<class T>
class CountingAllocator : public DefaultAllocator<T>
{
  public:
    CountingAllocator();
    ~CountingAllocator();
    CountingAllocator(CountingAllocator const& other);
    CountingAllocator& operator=(CountingAllocator const& other);

    const int getAllocationCount();
    const int getReleaseCount();
    const int getOutstandingCount();
    int getTotalAllocationCount();
    int getTotalReleaseCount();
    int getTotalOutstandingCount();
};

template<class T>
CountingAllocator<T>::CountingAllocator(){
    this->totalAllocationCount = 0;
    this->totalReleaseCount = 0;
    this->allocationCount = 0;
    this->releaseCount = 0;
};

template<class T>
CountingAllocator<T>::~CountingAllocator(){
};

template<class T>
CountingAllocator<T>::CountingAllocator(CountingAllocator const& other){
    this->totalAllocationCount = other.totalAllocationCount;
    this->totalReleaseCount = other.totalReleaseCount;
    this->allocationCount = other.allocationCount;
    this->releaseCount = other.releaseCount;
};

template<class T>
CountingAllocator<T>& CountingAllocator<T>::operator=(CountingAllocator const& other){
    this->totalAllocationCount = other.totalAllocationCount;
    this->totalReleaseCount = other.totalReleaseCount;
    this->allocationCount = other.allocationCount;
    this->releaseCount = other.releaseCount;
};


template<class T>
const int CountingAllocator<T>::getAllocationCount(){
    return this->allocationCount;
};


template<class T>
const int CountingAllocator<T>::getReleaseCount(){
    return this->releaseCount;
};


template<class T>
const int CountingAllocator<T>::getOutstandingCount(){
    return this->allocationCount-this->releaseCount;
};


template<class T>
int CountingAllocator<T>::getTotalAllocationCount(){
    return this->totalAllocationCount;
};

template<class T>
int CountingAllocator<T>::getTotalReleaseCount(){
    return this->totalReleaseCount;
};

template<class T>
int CountingAllocator<T>::getTotalOutstandingCount(){
    return this->totalAllocationCount - this->totalReleaseCount;
};

};

#endif
