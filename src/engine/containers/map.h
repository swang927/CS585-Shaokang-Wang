//  map.h

#ifndef INCLUDED_MAP
#define INCLUDED_MAP

#include "../memory/counting_allocator.h"
#include "../memory/default_allocator.h"
#include "../memory/iallocator.h"
#include "dynamic_array.h"
#include <assert.h>
#include <string>


namespace sgdc
{
// set the tree node structur  
template <class T>
struct trie_node {
  trie_node *alter;
  trie_node *next;
  unsigned int use_time;
  char key;
  T* value;
};

// implement the map class with trie
template <class T>
class Map{
  private:
	// allocator use to allocate 
    sgdm::IAllocator<T>* allocator;
	// default allocate
	sgdm::DefaultAllocator<T> d_alloc;
	sgdm::DefaultAllocator<trie_node<T>> t_alloc;
	// tree root
    trie_node<T> root;
	// a dynamic array to save all the keys
    sgdc::DynamicArray<std::string> key_chain;
	// a dynamic array to save all the values
	sgdc::DynamicArray<T> value_chain;

	// add the alter node if the current letter is not record in current place 
	// before and there is other letter saved in this place
    trie_node<T>* add_alter(char c, trie_node<T> *curr_node);
	// add the next node if the current letter is not record and no 
	// letter in same place
    trie_node<T>* add_next(char c, trie_node<T> *curr_node);
	// abstract the key string from the trie
    void read_key(std::string key_string, trie_node<T>* curr_node);

  public:
	// Default Constructor
	Map();
	// Constructor need load a allocator
    Map(sgdm::IAllocator<T>* d_alloc);
	// Copy constructor
    Map(const Map &other);
	// Operator overload
    const Map& operator=(const Map &other);
	// Deconstructor
    ~Map();

	// get the element with one key, if the key not exists in map create one
    T& operator[](const std::string& key); 
	// get the element with one key, if the key not exists in map create one
	// use for immutatable variable
    const T& operator[](const std::string& key) const;
	// check if a key exists in the map
    bool has(const std::string& key);
	// remove the relate element form the map with key, return the element 
    T remove(const std::string& key);
	// retrieve all keys in map
    sgdc::DynamicArray<std::string> keys();
	// retrieve all elements in map
    sgdc::DynamicArray<T> values();

}; // end of class

// Default Constructor
template <class T>
inline
Map<T>::Map(){
	allocator = &d_alloc;
	root.alter = NULL;
	root.next = NULL;
	root.use_time = 1;
	root.key = '\0';
	root.value = NULL;
};


// Constructor need load a allocator
template <class T>
inline
Map<T>::Map(sgdm::IAllocator<T>* alloc){
	allocator = d_alloc;
	root.alter = NULL;
	root.next = NULL;
	root.use_time = 1;
	root.key = '\0';
	root.value = NULL;
};


// Copy constructor
template <class T>
inline
Map<T>::Map(const Map &other){
	allocator = other.allocator;
	root.alter = NULL;
	root.next = NULL;
	root.use_time = 1;
	root.key = '\0';
	root.value = NULL;
	value_chain = const_cast<Map<T> &>(other).values();
	key_chain = const_cast<Map<T> &>(other).keys();
	for (unsigned int i = 0; i < value_chain.getLength(); i++){
		this->operator[](key_chain[i]) = value_chain[i];
	}
};


// Operator overload
template <class T>
inline
const Map<T>& Map<T>:: operator=(const Map<T> &other) {
    if (this != &other) {
		allocator = other.allocator;
		value_chain = this->values();
		for (unsigned int i = 0; i < value_chain.getLength(); i++){
			allocator->destruct(&value_chain[i]);
		}
		root.alter = NULL;
		root.next = NULL;
		root.use_time = 1;
		root.key = '\0';
		root.value = NULL;
		value_chain = const_cast<Map<T> &>(other).values();
		key_chain = const_cast<Map<T> &>(other).keys();
		for (unsigned int i = 0; i < value_chain.getLength(); i++){
			this->operator[](key_chain[i]) = value_chain[i];
		}
	};
	return *this;
};

// Deconstructor
template <class T>
inline
Map<T>::~Map(){
	value_chain = this->values();
	key_chain = this->keys();
};


// get the element with one key, if the key not exists in map create one
template <class T>
inline
T& Map<T>::operator[](const std::string& key){
    trie_node<T> *curr_node;
    trie_node<T> *pass_node;
    pass_node = NULL;
    curr_node = &root;
    int i = 0;
    //search a node
    if (has(key)){
        curr_node = curr_node->next;
        while (key[i] != '\0'){
            if (curr_node->key == key[i]){
                if (curr_node->next == NULL){
                    i++;
                    break;
                }
                else{
                    curr_node = curr_node->next;
                    i++;
                }
            }
            else{
                if (curr_node->alter != NULL)
                   curr_node = curr_node->alter;
                else{
                   i++;
                   break;
                }
            }
        }
	    return *(curr_node->value);
    }
    // creat a new node
    else{
        if (root.next == NULL){
	        curr_node->use_time++;
	        curr_node = add_next(key[0], curr_node);
	        i++;
	    }
	    else{
	        curr_node->use_time++;
	        curr_node = curr_node->next;
	        while (key[i] != '\0'){
		        if (curr_node->key == key[i]){
		            if (curr_node->next == NULL){
			            i++;
			            break;
		            }
		            else{
			            pass_node = curr_node;
			            curr_node->use_time++;
			            curr_node = curr_node->next;
			            i++;
		            }
		        }
		        else{
		            if (curr_node->alter != NULL)
			            curr_node = curr_node->alter;
		            else{
			            curr_node = add_alter(key[i], curr_node);
			            pass_node = curr_node;
			            i++;
			            break;
		            }
		        }
	        }
	    }
		// create the 
	    T* default_value = allocator->get(1);
	    allocator->construct(default_value);
        // insert node
	    if (key[i] == '\0' && pass_node && !pass_node->value){
	        pass_node->value = default_value;
	    }
	    else{
	        while (key[i] != '\0'){
		        curr_node = add_next(key[i], curr_node);
		        i++;
	        }
	        if (!curr_node->value)
		        curr_node->value = default_value;
	    }
    }
    return  *(curr_node->value);
};


// get the element with one key, if the key not exists in map create one
// use for immutatable variable
template <class T>
inline
const T& Map<T>::operator[](const std::string& key) const{
	return this->operator[](key);
}

// check if a key exists in the map
template <class T>
inline
bool Map<T>::has(const std::string& key){
    trie_node<T> *curr_node = &root;
    int i = 0;
    if (root.next == NULL)
        return false;
    else{
        curr_node = curr_node->next;
        while (key[i] != '\0'){
            if (curr_node->key == key[i]){
                if (curr_node->next == NULL){
                    i++;
                    break;
                }
                else{
                    curr_node = curr_node->next;
                    i++;
                }
            }
            else{
            	 if (curr_node->alter != NULL)
                    curr_node = curr_node->alter;
                 else
                    return false;
            }
        }
    }
    if (key[i] == '\0')
        return true;
    else
       return false;
}


// remove the relate element form the map with key, return the element 
template <class T>
inline
T Map<T>::remove(const std::string& key){
    if (!has(key))
	return (T)NULL;
    T saved_value = this->operator[](key);
    trie_node<T> *curr_node;
    trie_node<T> *pass_node;
    trie_node<T> *alter_node = &root;
    curr_node = &root;
    int i = 0;
    pass_node = curr_node;
    curr_node = curr_node->next;
    while (key[i] != '\0'){
	if (curr_node->key == key[i]){
	    if (curr_node->use_time == 1){
		if (curr_node->alter == NULL){
		    if (alter_node->alter == curr_node)
			alter_node->alter = NULL;
		    else
			pass_node->next = NULL;
						
		    break;
		}
		else{
		    if (alter_node->alter == curr_node)
			alter_node->alter = curr_node->alter;
		    else
			pass_node->next = curr_node->alter;
		    break;
		}
	    }
	    else{
		curr_node->use_time--;
		pass_node = curr_node;
		curr_node = curr_node->next;
		i++;
	    }
	}
	else{
	    alter_node = curr_node;
	    curr_node = curr_node->alter;
	}
    };
    return saved_value;
}


// retrieve all keys in map
template <class T>
inline
sgdc::DynamicArray<std::string> Map<T>::keys() {
	key_chain.clean();
    trie_node<T> *curr_node =  &root;
    std::string key_string = "";

    if (root.next){
        read_key(key_string, curr_node);
    };
    return key_chain;
};


// retrieve all elements in map
template <class T>
inline
sgdc::DynamicArray<T> Map<T>::values() {
	sgdc::DynamicArray<std::string> curr_keys = this->keys();
	value_chain.clean();
    for (unsigned int i = 0; i < curr_keys.getLength(); i++){
         value_chain.push(this->operator[](curr_keys[i]));
    };
    return value_chain;
};


// Private Function:
// abstract the key string from the trie
template <class T>
inline
void Map<T>::read_key(std::string key_string, trie_node<T>* curr_node){
    if (curr_node == &root)
	curr_node = curr_node->next;
    
    if (curr_node->alter != NULL){
	read_key(key_string, curr_node->alter);
    }

    key_string += curr_node->key;
    if (curr_node->value != NULL)
	key_chain.push(key_string);

    if (curr_node->next != NULL){
	read_key(key_string, curr_node->next);
    }
    return;
};


// node insert
// add the alter node if the current letter is not record in current place 
// before and there is other letter saved in this place
template <class T>
inline
trie_node<T>* Map<T>::add_alter(char c, trie_node<T>* curr_node){
	trie_node<T>* new_node = t_alloc.get(1);
	t_alloc.construct(new_node);
    new_node->alter = NULL;
    new_node->next = NULL;
    new_node->use_time = 1;
    new_node->key = c;
    new_node->value = NULL;
    curr_node->alter = new_node;
    curr_node = curr_node->alter;
    return curr_node;
}


// add the next node if the current letter is not record and no 
// letter in same place
template <class T>
inline
trie_node<T>* Map<T>::add_next(char c, trie_node<T>* curr_node){
	trie_node<T>* new_node = t_alloc.get(1);
	t_alloc.construct(new_node);
    new_node->alter = NULL;
    new_node->next = NULL;
    new_node->use_time = 1;
    new_node->key = c;
    new_node->value = NULL;
    curr_node->next = new_node;
    curr_node = curr_node->next;
    return curr_node;
}


};
#endif
