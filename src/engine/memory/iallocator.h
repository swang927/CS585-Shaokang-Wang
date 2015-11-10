// iallocator.h

#ifndef INCLUDED_IALLOCATOR
#define INCLUDED_IALLOCATOR
    
#include <string>

namespace sgdm
{

// In order to support multiple allocator types, creat the interface IAllocator.
template<class T>
class IAllocator {
  public:
    // allocate the certain times of corresponding type memory and return the address
    virtual T* get(int count) =0;
    // free the memory start from the pointed address with certain size 
    virtual void release(T* pointer, int count) = 0;
    // constrct the object as the copy 
    virtual void construct(T* pointer, const T& copy) = 0;
    // construct the object as default in the ceratin address
    virtual void construct(T* pointer) = 0;
    // destruct the oject as default in the ceratin address
    virtual void destruct(T* pointer) = 0;
    

    // construct the object with corresponding arguments in the ceratin address
    template<class U, class... Args>
    void construct(U* pointer, Args&&... args){
        ::new((void *)pointer) U(std::forward<Args>(args)...);
    };
}; // end of class
}; // end of namespace
#endif
