// default_allocator.h

#ifndef INCLUDED_DEFAULT_ALLOCATOR
#define INCLUDED_DEFAULT_ALLOCATOR

#include "iallocator.h"

namespace sgdm
{

// Provides a default implementation of IAllocator<T> using new and delete
template<class T> 
class DefaultAllocator : public IAllocator<T> 
{
  protected:
	// the total number of memory blocks has been allocate
    unsigned int totalAllocationCount;
	// the total number of memory blocks has been released
    unsigned int totalReleaseCount;
	// the number of allocate times
    unsigned int allocationCount;
	// the number of release times
    unsigned int releaseCount;

  public:
	// Constructor
    DefaultAllocator();
	// Deconstructor
    ~DefaultAllocator();
    // Copy constructor.
    DefaultAllocator(const DefaultAllocator &other);
	// Operator overload
    DefaultAllocator& operator=(const DefaultAllocator &other);

	// Access
	// Get the current numbers of allocated memory size 
    int get_count(){ return totalAllocationCount - totalReleaseCount; };

	// Implement the interface "IAllocator" //
	// allocate the certain times of corresponding type memory and return the address
    T* get(int count);
	// free the memory start from the pointed address with certain size 
    void release(T* target_memory, int count);
	// free the memory start from the pointed address
    void release(T* target_memory);
	// constrct the object as the copy
    void construct(T* pointer, const T& copy);
	// construct the object as default in the ceratin address
    void construct(T* pointer);
	// destruct the oject as default in the ceratin address
    void destruct(T* pointer);
    
	// construct the object with corresponding arguments in the ceratin address
    template<class U, class... Args>
    void construct(U* pointer, Args&&... args);

}; // end of class


// Constructor
template<class T>
inline
DefaultAllocator<T>::DefaultAllocator(){
    totalAllocationCount = 0;
    totalReleaseCount = 0;
    allocationCount = 0;
    releaseCount = 0;
};


// Deconstructor
template<class T>
inline
DefaultAllocator<T>::~DefaultAllocator(){   
};


// Copy constructor.
template<class T>
inline
DefaultAllocator<T>::DefaultAllocator(DefaultAllocator const& other){
    totalAllocationCount = other.totalAllocationCount;
    totalReleaseCount = other.totalReleaseCount;
    allocationCount = other.allocationCount;
    releaseCount = other.releaseCount;
};


// Operator overload
template<class T>
inline
DefaultAllocator<T>& DefaultAllocator<T>::operator=(DefaultAllocator const& other){
    this->totalAllocationCount = other.totalAllocationCount;
    this->totalReleaseCount = other.totalReleaseCount;
    this->allocationCount = other.allocationCount;
    this->releaseCount = other.releaseCount;
};



// allocate the certain times of corresponding type memory and return the address
template<class T>
inline
T* DefaultAllocator<T>::get(int count){
    totalAllocationCount += count;
    allocationCount += 1;
    return (T*)::operator new (sizeof(T)*count);
};


// free the memory start from the pointed address with certain size 
template<class T>
inline
void DefaultAllocator<T>::release(T* target_memory, int count){
	if (target_memory != NULL){
		totalReleaseCount += count;
		releaseCount += 1;
		::operator delete((void*)target_memory);
	}
};


// free the memory start from the pointed address
template<class T>
inline
void DefaultAllocator<T>::release(T* target_memory){
	::operator delete((void*)target_memory);
};


// construct the object as default in the ceratin address
template<class T>
void DefaultAllocator<T>::construct(T* pointer){
	new((void *)pointer) T();
};


// constrct the object as the copy
template<class T>
void DefaultAllocator<T>::construct(T* pointer, const T& copy){
	new((void *)pointer) T(copy);
};


// destruct the oject as default in the ceratin address
template<class T>
void DefaultAllocator<T>::destruct(T* pointer){
	pointer->~T();
};


// construct the object with corresponding arguments in the ceratin address
template<class T>
template< class U, class... Args >
inline
void DefaultAllocator<T>::construct(U* p, Args&&... args){
	::new((void *)p) U(std::forward<Args>(args)...);
};


}; // end of namespace
#endif
