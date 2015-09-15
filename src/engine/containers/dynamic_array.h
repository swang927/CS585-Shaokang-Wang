//  dynamic_array.h

#ifndef INCLUDED_DYNAMIC_ARRAY
#define INCLUDED_DYNAMIC_ARRAY

#include "../memory/counting_allocator.h"
#include "../memory/default_allocator.h"
#include "../memory/iallocator.h"
#include <assert.h>

namespace sgdc
{

template <class T>
class DynamicArray {
  private:
    sgdm::IAllocator<T>* allocator;
    T *array;
    unsigned int elementCount;
    unsigned int capacity;
	
    void Recapacity(int capacity);

  public:
    DynamicArray(sgdm::IAllocator<T>* alloc);
    DynamicArray(const DynamicArray &other); 
    const DynamicArray& operator=(const DynamicArray &other); 
    ~DynamicArray(); 

    void push(const T & element);
    void pushFront(T element);
    T pop();
    T popFront();
    const unsigned int getLength();
    const T at(unsigned int index);
    T& operator[](int);
    const T& operator[](int) const;
    T removeAt(unsigned int index);
    void insertAt(unsigned int index, const T& element);

}; 

template <class T>
DynamicArray<T>::DynamicArray(sgdm::IAllocator<T>* alloc){
    allocator = alloc;
    array = allocator->get(2);
    capacity = 2;
    elementCount = 0;
};

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other) {
    array = allocator->get(other.capacity);
    for (int i = 0; i < other.elementCount; i++)
        array[i] = other.array[i];
    capacity = other.capacity;
    elementCount = other.elementCount;
};

template <class T>
const DynamicArray<T>& DynamicArray<T>:: operator=(const DynamicArray<T> &other) {
    if (this != &other) {
        allocator->release(array, capacity);
        array = allocator->get(other.capacity);
        for (int i = 0; i < other.elementCount; i++)
            array[i] = other.array[i];
        capacity = other.capacity;
        elementCount = other.elementCount;
    };
    return *this;
};

template <class T>
DynamicArray<T>::~DynamicArray() {
    allocator->release(array, capacity);
};


template <class T> void DynamicArray<T>::Recapacity(int newCapacity) {
    assert(capacity >= elementCount);
    T* newArray = allocator->get(newCapacity);
    for (unsigned int i = 0; i < elementCount; i++)
    {
        newArray[i] = array[i];
    }
    allocator->release(array, capacity);;
    array = newArray;
    capacity = newCapacity;
};


template <class T>
void DynamicArray<T>::push(const T &element) {
    if (elementCount == capacity){
        Recapacity(2 * capacity);
    };
    array[elementCount++] = element;
};

template <class T>
void DynamicArray<T>::pushFront(T element) {
    if (elementCount == capacity){
        Recapacity(2 * capacity);
    };
    elementCount++;
    for (int i = elementCount - 1; i > 0; i--)
    {
        array[i] = array[i - 1];
    };
    array[0] = element;
};

template <class T>
T DynamicArray<T>::pop() {
    assert(elementCount > 0);
    elementCount--;
    return array[elementCount + 1];
}

template <class T>
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

template <class T>
const unsigned int DynamicArray<T>::getLength(){
    return elementCount;
}

template <class T>
const T DynamicArray<T>::at(unsigned int index){
    assert(index < elementCount && index >= 0);
    return array[index];
}

template <class T>
T& DynamicArray<T>::operator[](int index) {
    assert(index < elementCount && index >= 0);
    return array[index];
}

template <class T>
const T& DynamicArray<T>::operator[](int index) const {
    assert(index < elementCount && index >= 0);
    return array[index];
}


template <class T>
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

template <class T>
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


};
#endif
