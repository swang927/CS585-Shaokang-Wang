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
    DefaultAllocator(const DefaultAllocator &other);
    DefaultAllocator& operator=(const DefaultAllocator &other);
    int get_count(){ return totalAllocationCount - totalReleaseCount; };

    T* get(int count);
    void release(T* target_memory, int count);
    void release(T* target_memory);
    void construct(T* pointer, const T& copy);
    void construct(T* pointer);
    void destruct(T* pointer);
    
/*
    template<class U, class... Args>
    void construct(U* pointer, Args&&... args);
 */
};


template<class T>
DefaultAllocator<T>::DefaultAllocator(){
    totalAllocationCount = 0;
    totalReleaseCount = 0;
    allocationCount = 0;
    releaseCount = 0;
};

template<class T>
DefaultAllocator<T>::~DefaultAllocator(){   
};


template<class T>
DefaultAllocator<T>::DefaultAllocator(DefaultAllocator const& other){
    totalAllocationCount = other.totalAllocationCount;
    totalReleaseCount = other.totalReleaseCount;
    allocationCount = other.allocationCount;
    releaseCount = other.releaseCount;
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
    totalAllocationCount += count;
    allocationCount += 1;
    return (T*)::operator new (sizeof(T)*count);
};

template<class T>
void DefaultAllocator<T>::release(T* target_memory, int count){
	if (target_memory != NULL){
		totalReleaseCount += count;
		releaseCount += 1;
		delete target_memory;
	}
};


template<class T>
void DefaultAllocator<T>::release(T* target_memory){
	::operator delete((void*)target_memory);
};



/*
template<class T>
template< class U, class... Args >
void DefaultAllocator<T>::construct(U* p, Args&&... args){
	::new((void *)p) U(std::forward<Args>(args)...);
};
*/

template<class T>
void DefaultAllocator<T>::construct(T* pointer, const T& copy){
	new((void *)pointer) T(copy);
};

template<class T>
void DefaultAllocator<T>::construct(T* pointer){
	new((void *)pointer) T();
};

template<class T>
void DefaultAllocator<T>::destruct(T* pointer){
	pointer->~T();
};
};


#endif
