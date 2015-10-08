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
    CountingAllocator(const CountingAllocator &other);
    CountingAllocator& operator=(const CountingAllocator &other);

    const int getAllocationCount();
    const int getReleaseCount();
    const int getOutstandingCount();
    int getTotalAllocationCount();
    int getTotalReleaseCount();
    int getTotalOutstandingCount();
};

template<class T>
inline
CountingAllocator<T>::CountingAllocator(){
    this->totalAllocationCount = 0;
    this->totalReleaseCount = 0;
    this->allocationCount = 0;
    this->releaseCount = 0;
};

template<class T>
inline
CountingAllocator<T>::~CountingAllocator(){
};

template<class T>
inline
CountingAllocator<T>::CountingAllocator(CountingAllocator const& other){
    this->totalAllocationCount = other.totalAllocationCount;
    this->totalReleaseCount = other.totalReleaseCount;
    this->allocationCount = other.allocationCount;
    this->releaseCount = other.releaseCount;
};

template<class T>
inline
CountingAllocator<T>& CountingAllocator<T>::operator=(CountingAllocator const& other){
    this->totalAllocationCount = other.totalAllocationCount;
    this->totalReleaseCount = other.totalReleaseCount;
    this->allocationCount = other.allocationCount;
    this->releaseCount = other.releaseCount;
};


template<class T>
inline
const int CountingAllocator<T>::getAllocationCount(){
    return this->allocationCount;
};


template<class T>
inline
const int CountingAllocator<T>::getReleaseCount(){
    return this->releaseCount;
};


template<class T>
inline
const int CountingAllocator<T>::getOutstandingCount(){
    return this->allocationCount-this->releaseCount;
};


template<class T>
inline
int CountingAllocator<T>::getTotalAllocationCount(){
    return this->totalAllocationCount;
};

template<class T>
inline
int CountingAllocator<T>::getTotalReleaseCount(){
    return this->totalReleaseCount;
};

template<class T>
inline
int CountingAllocator<T>::getTotalOutstandingCount(){
    return this->totalAllocationCount - this->totalReleaseCount;
};


};

#endif
