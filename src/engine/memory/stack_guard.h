//  stack_guard.h
    
#ifndef INCLUDED_STACK_GUARD
#define INCLUDED_STACK_GUARD
    
#include "iallocator.h"
#include "default_allocator.h"

namespace sgdm{
// A simple template for wrapping a raw pointer
template <class T>
class StackGuard{
  private:
    // default allocator
    IAllocator<T>* d_alloc;
    // the pointer point to the object
    T* d_ref;
    // the size of object
    int d_size;
    
    // default constructor
    StackGuard() = delete;
    // copy constructor
    StackGuard(const StackGuard &) = delete;
    // copy constructor
    StackGuard(StackGuard &&) = delete;
    // override operator
    StackGuard& operator= (const StackGuard&) = delete;
    StackGuard& operator= (StackGuard&&) = delete;

  public:
    // Constructor
    StackGuard(T* guarded);
    // Constructor with size
    StackGuard(T* guarded, int size);
    // Constructor with size and allocator
    StackGuard(T* guarded, int size, IAllocator<T>* alloc);
    // Deconstructor
    ~StackGuard();
    // override the -> operator
    T* operator->() const;
};


// Constructor
template <class T>
inline
StackGuard<T>::StackGuard(T* guarded, int size, IAllocator<T>* alloc){
    d_ref = guarded;
    d_size = size;
    d_alloc = alloc;
};


// Constructor with size
template <class T>
inline
StackGuard<T>::StackGuard(T* guarded, int size){
    d_ref = guarded;
    d_size = size;
};


// Constructor with size and allocator
template <class T>
inline
StackGuard<T>::StackGuard(T* guarded){
    d_ref = guarded;
    d_size = 1;
};


// Deconstructor
template <class T>
inline
StackGuard<T>::~StackGuard(){
    if (d_ref)
    {
        if (d_alloc)
        {
            d_alloc->release(d_ref, d_size);
        }
        else
        {
            DefaultAllocator<T> alloc;
            alloc.release(d_ref, d_size);
        }
    }
}


// override the -> operator
template <class T>
inline
T* StackGuard<T>::operator->() const{
    return d_ref;
}

};
#endif