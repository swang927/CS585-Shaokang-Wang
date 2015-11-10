//  dynamic_array.h
    
#ifndef INCLUDED_DYNAMIC_ARRAY
#define INCLUDED_DYNAMIC_ARRAY

#include "../memory/counting_allocator.h"
#include "../memory/default_allocator.h"
#include "../memory/iallocator.h"
#include <assert.h>
#include <string>

namespace sgdc
{
// implment the dynamic array 
template <class T>
class DynamicArray {
  private:
    // allocator use to allocate 
    sgdm::IAllocator<T>* allocator;
    // default allocate
    sgdm::DefaultAllocator<T> def_allocator;
    // the array pointer save the address of array
    T *array;
    // the number of element in array
    unsigned int elementCount;
    // the capacity of current array
    unsigned int capacity;
    // reset the capacity of array
    void Recapacity(int capacity);

  public:
    // Default Constructor
    DynamicArray();
    // Constructor need load a allocator
    DynamicArray(sgdm::IAllocator<T>* alloc);
    // Copy constructor
    DynamicArray(const DynamicArray &other);
    // Operator overload
    const DynamicArray& operator=(const DynamicArray &other); 
    // Deconstructor
    ~DynamicArray(); 

    // add element to end of collection
    void push(const T & element);
    // push to the front of the collection
    void pushFront(T element);
    // remove and retrieves the last element
    T pop();
    // remove and retrieves the first element
    T popFront();


    // return the number of elements contained
    const unsigned int getLength();
    // retrieves an element at a location
    const T at(unsigned int index);
    // retrieves an element, undefined behavior if out of bounds
    T& operator[](int);
    // get an element, undefined behavior if out of bounds    
    const T& operator[](int) const;

    // remove the element at a location
    T removeAt(unsigned int index);
    // remove the element  from the array
    T remove(const T& element);
    // insert an element at a location, shift the element to next avalible place
    void insertAt(unsigned int index, const T& element);
    // remove all elements in array
    void clean();
    // check if the array is empty
    bool empty();
    
}; // end of class


// Default Constructor
template <class T>
inline
DynamicArray<T>::DynamicArray(){
    allocator = &def_allocator;
    capacity = 2;
    elementCount = 0;
    array = allocator->get(2);
};


// Constructor, need load a allocator
template <class T>
inline
DynamicArray<T>::DynamicArray(sgdm::IAllocator<T>* alloc){
    allocator = alloc;
    capacity = 2;
    elementCount = 0;
    array = allocator->get(2);
    for (unsigned int i = 0; i < capacity; i++){
    allocator->construct(&(array[i]));
    }
};


// Copy constructor
template <class T>
inline
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other) {
    capacity = other.capacity;
    allocator = other.allocator;
    elementCount = other.elementCount;
    array = allocator->get(other.capacity);
        for (unsigned int i = 0; i < capacity; i++)
        allocator->construct(&(array[i]));
    for (unsigned int i = 0; i < elementCount; i++)
        array[i] = other.array[i];
};


// Operator overload
template <class T>
inline
const DynamicArray<T>& DynamicArray<T>:: operator=(const DynamicArray<T> &other) {
    if (this != &other) {
        for (unsigned int i = 0; i < elementCount; i++){
            allocator->destruct(&array[i]);
        }
        allocator->release(array, capacity);
        capacity = other.capacity;
        allocator = other.allocator;
        elementCount = other.elementCount;
        array = allocator->get(other.capacity);
        for (unsigned int i = 0; i < capacity; i++)
            allocator->construct(&(array[i]));
        for (unsigned int i = 0; i < elementCount; i++)
            array[i] = other.array[i];
    };
    return *this;
};


// Deconstructor
template <class T>
inline
DynamicArray<T>::~DynamicArray() {
    for (unsigned int i = 0; i < elementCount; i++){
        allocator->destruct(&array[i]);
    }
    allocator->release(array, capacity);
};


// private function: reset the capacity of array
template <class T>
inline
void DynamicArray<T>::Recapacity(int newCapacity) {
    assert(capacity >= elementCount);
    T* newArray = allocator->get(newCapacity);
    for (int i = 0; i < newCapacity; i++){
        allocator->construct(&(newArray[i]));
    }
    for (unsigned int i = 0; i < elementCount; i++)
    {
        newArray[i] = array[i];
    }
    allocator->release(array, capacity);
    capacity = newCapacity;
    array = newArray;

};


// add element to end of collection
template <class T>
inline
void DynamicArray<T>::push(const T &element) {
    if (elementCount == capacity){
        Recapacity(2 * capacity);
    };
    allocator->construct(&array[elementCount++], element);
};


// push to the front of the collection
template <class T>
void DynamicArray<T>::pushFront(T element) {
    if (elementCount == capacity){
        Recapacity(2 * capacity);
    };
    elementCount++;
    for (int i = elementCount - 1; i > 0; i--){
        array[i] = array[i - 1];
    };
    allocator->construct(&array[0], element);
};


// remove and retrieves the last element
template <class T>
inline
T DynamicArray<T>::pop() {
    assert(elementCount > 0);
    elementCount--;
    return array[elementCount];
}


// remove and retrieves the first element
template <class T>
inline
T DynamicArray<T>::popFront() {
    assert(elementCount > 0);
    T targetElement = array[0];
    for (unsigned int i = 0; i < elementCount - 1; i++)
    {
        array[i] = array[i + 1];
    }
    elementCount--;
    return targetElement;
}


// return the number of elements contained
template <class T>
inline
const unsigned int DynamicArray<T>::getLength(){
    return elementCount;
}


// retrieves an element, undefined behavior if out of bounds
template <class T>
inline
T& DynamicArray<T>::operator[](int index) {
    assert((unsigned int)index < elementCount && index >= 0);
    return array[index];
}


// get an element, undefined behavior if out of bounds
template <class T>
inline
const T& DynamicArray<T>::operator[](int index) const {
    assert(index < elementCount && index >= 0);
    return array[index];
}


// retrieves an element at a location, need a int as index
template <class T>
inline
const T DynamicArray<T>::at(unsigned int index){
    assert(index < elementCount && index >= 0);
    return array[index];
}


// remove the element from the array, need a element
template <class T>
inline
T DynamicArray<T>::remove(const T& element){
    unsigned int index = -1;

    for (unsigned int i = 0; i < elementCount; i++){
        if (array[i] == element){
            index = i;
            break;
        }
    };
    if (index == -1)
        return NULL;

    for (unsigned int i = index; i < elementCount - 1; i++){
        array[i] = array[i + 1];
    };

    elementCount--;
    return element;
}


// insert an element at a location, shift the element to next avalible place
template <class T>
inline
void DynamicArray<T>::insertAt(unsigned int index, const T& element){
    assert(index < elementCount && index >= 0);
    if (elementCount == capacity){
        Recapacity(2 * capacity);
    }
    elementCount++;
    for (int i = elementCount - 1; i > index; i--)
    {
        array[i] = array[i - 1];
    }
    array[index] = element;
};


// remove the element  from the array
template <class T>
inline
T DynamicArray<T>::removeAt(unsigned int index){
    assert(index < elementCount && index >= 0);
    T targetElement = array[index];
    for (unsigned int i = index; i < elementCount - 1; i++)
    {
        array[i] = array[i + 1];
    };
    elementCount--;
    return targetElement;
}


// clean up the array
template <class T>
inline
void DynamicArray<T>::clean(){
    while (!this->empty()){
        this->pop();
    };
};


// check the array is empty or not
template <class T>
inline
bool DynamicArray<T>::empty(){
    if (elementCount == 0)
        return true;
    return false;
};

}; // end of namespace
#endif
