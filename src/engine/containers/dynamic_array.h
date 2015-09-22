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

template <class T>
class DynamicArray {
  private:
    sgdm::IAllocator<T>* allocator;
    T *array;
    unsigned int elementCount;
    unsigned int capacity;
    void Recapacity(int capacity);

  public:
    DynamicArray();
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
DynamicArray<T>::DynamicArray(){
    allocator = new sgdm::DefaultAllocator<T>();
    capacity = 2;
    elementCount = 0;
    array = allocator->get(2);
    for (unsigned int i = 0; i < capacity; i++){
        allocator->construct(&(array[i]));
    }
};

template <class T>
DynamicArray<T>::DynamicArray(sgdm::IAllocator<T>* alloc){
    allocator = alloc;
    capacity = 2;
    elementCount = 0;
    array = allocator->get(2);
    for (unsigned int i = 0; i < capacity; i++){
	allocator->construct(&(array[i]));
    }
};


template <class T>
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

template <class T>
const DynamicArray<T>& DynamicArray<T>:: operator=(const DynamicArray<T> &other) {
    if (this != &other) {
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

template <class T>
DynamicArray<T>::~DynamicArray() {
    allocator->release(array, capacity);
};


template <class T> void DynamicArray<T>::Recapacity(int newCapacity) {
    assert(capacity >= elementCount);
    T* newArray = allocator->get(newCapacity);
	for (int i = 0; i < newCapacity; i++){
	    allocator->construct(&(newArray[i]));
	}
    for (unsigned int i = 0; i < elementCount; i++)
    {
        newArray[i]=array[i];
    }
    allocator->release(array, capacity);
	capacity = newCapacity;
    array = newArray;
    
};


template <class T>
void DynamicArray<T>::push(const T &element) {
    if (elementCount == capacity){
        Recapacity(2 * capacity);
    };
	allocator->construct(&array[elementCount++], element);
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
	allocator->construct(&array[0], element);
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
    assert((unsigned int)index < elementCount && index >= 0);
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
