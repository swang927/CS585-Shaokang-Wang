//  stack_guard.h

#ifndef INCLUDED_STACK_GUARD
#define INCLUDED_STACK_GUARD

#include "iallocator.h"
#include "default_allocator.h"

namespace sgdm
{
template <class T>
class StackGuard{
  private:
      IAllocator<T>* d_alloc;
      T* d_ref;
      int d_size;

  public:
      StackGuard(T* guarded);
      StackGuard(T* guarded, int size);
      StackGuard(T* guarded, int size, IAllocator<T>* alloc);
      ~StackGuard();
      T* operator->() const;
};

template <class T>
inline
StackGuard<T>::StackGuard(T* guarded, int size, IAllocator<T>* alloc){
    d_ref = guarded;
    d_size = size;
    d_alloc = alloc;
};

template <class T>
inline
StackGuard<T>::StackGuard(T* guarded, int size){
    d_ref = guarded;
    d_size = size;
};

template <class T>
inline
StackGuard<T>::StackGuard(T* guarded){
    d_ref = guarded;
    d_size = 1;
};

template <class T>
inline
StackGuard<T>::~StackGuard(){
    if (d_ref){
	if (d_alloc){
	    d_alloc->release(d_ref, d_size);
	}
	else{
	    DefaultAllocator<T> alloc;
	    alloc.release(d_ref, d_size);
	}
    }
};

template <class T>
inline
T* StackGuard<T>::operator->() const{
	return d_ref;
};

};
#endif
