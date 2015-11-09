// counting_allocator.h

#ifndef INCLUDED_COUNTING_ALLOCATOR
#define INCLUDED_COUNTING_ALLOCATOR

# include "default_allocator.h"

namespace sgdm
{

// Provides a implementation of IAllocator<T> inherit DefaultAllocator
// which can counting allocator to keep track of allocations and frees
template<class T>
class CountingAllocator : public DefaultAllocator<T>
{
  public:
	// Constructor
    CountingAllocator();
	// Deconstructor
    ~CountingAllocator();
	// Copy constructor.
    CountingAllocator(const CountingAllocator &other);
	// Operator overload
    CountingAllocator& operator=(const CountingAllocator &other);

	// Access
	// get the number of allocate times 
    const int getAllocationCount();
	// get the number of release times
    const int getReleaseCount();
	// get the number of allocate times substract release times
    const int getOutstandingCount();
	// get the total number of memory blocks has been allocate 
    int getTotalAllocationCount();
	// get the total number of memory blocks has been released
    int getTotalReleaseCount();
	// the total number of memory blocks still been allocated
    int getTotalOutstandingCount();

}; // end of class


// Constructor
template<class T>
inline
CountingAllocator<T>::CountingAllocator(){
    this->totalAllocationCount = 0;
    this->totalReleaseCount = 0;
    this->allocationCount = 0;
    this->releaseCount = 0;
};


// Deconstructor
template<class T>
inline
CountingAllocator<T>::~CountingAllocator(){
};


// Copy constructor.
template<class T>
inline
CountingAllocator<T>::CountingAllocator(CountingAllocator const& other){
    this->totalAllocationCount = other.totalAllocationCount;
    this->totalReleaseCount = other.totalReleaseCount;
    this->allocationCount = other.allocationCount;
    this->releaseCount = other.releaseCount;
};


// Operator overload
template<class T>
inline
CountingAllocator<T>& CountingAllocator<T>::operator=(CountingAllocator const& other){
    this->totalAllocationCount = other.totalAllocationCount;
    this->totalReleaseCount = other.totalReleaseCount;
    this->allocationCount = other.allocationCount;
    this->releaseCount = other.releaseCount;
};

// Access
// get the number of allocate times 
template<class T>
inline
const int CountingAllocator<T>::getAllocationCount(){
    return this->allocationCount;
};

// get the number of release times
template<class T>
inline
const int CountingAllocator<T>::getReleaseCount(){
    return this->releaseCount;
};


// get the number of allocate times substract release times
template<class T>
inline
const int CountingAllocator<T>::getOutstandingCount(){
    return this->allocationCount-this->releaseCount;
};


// get the total number of memory blocks has been allocate 
template<class T>
inline
int CountingAllocator<T>::getTotalAllocationCount(){
    return this->totalAllocationCount;
};


// get the total number of memory blocks has been released
template<class T>
inline
int CountingAllocator<T>::getTotalReleaseCount(){
    return this->totalReleaseCount;
};


// the total number of memory blocks still been allocated
template<class T>
inline
int CountingAllocator<T>::getTotalOutstandingCount(){
    return this->totalAllocationCount - this->totalReleaseCount;
};


}; // end of namespace
#endif
