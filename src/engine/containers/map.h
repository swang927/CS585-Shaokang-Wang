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

template <class T>
struct trie_node {
  trie_node *alter;
  trie_node *next;
  unsigned int use_time;
  char key;
  T* value;
};


template <class T>
class Map{
  private:
    sgdm::IAllocator<T>* allocator;
    trie_node<T> root;
    sgdc::DynamicArray<std::string> key_chain;
    trie_node<T>* add_alter(char c, trie_node<T> *curr_node);
    trie_node<T>* add_next(char c, trie_node<T> *curr_node);
    void read_key(std::string key_string, trie_node<T>* curr_node);

  public:
    Map(sgdm::IAllocator<T>* alloc);
    Map();
    Map(const Map &other);
    const Map& operator=(const Map &other);
    ~Map();


	
    T& operator[](const std::string& key); 
    const T& operator[](const std::string& key) const;
    bool has(const std::string& key);
    T remove(const std::string& key);
    sgdc::DynamicArray<std::string> keys();
    sgdc::DynamicArray<T> values();
};


template <class T>
T& Map<T>::operator[](const std::string& key){
    T* default_value = new T();
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
    // new a node
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

template <class T>
const T& Map<T>::operator[](const std::string& key) const{
    T* default_value = new T();
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
    // new a node
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
}

template <class T>
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

template <class T>
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

template <class T>
sgdc::DynamicArray<std::string> Map<T>::keys() {
    key_chain = *(new sgdc::DynamicArray<std::string>());
    trie_node<T> *curr_node =  &root;
    std::string key_string = "";

    if (root.next){
        read_key(key_string, curr_node);
    };
    return key_chain;
};

template <class T>
sgdc::DynamicArray<T> Map<T>::values() {
    sgdc::DynamicArray<T>* value_chain = new sgdc::DynamicArray<T>();
    sgdc::DynamicArray<std::string> curr_keys = *(new sgdc::DynamicArray<std::string>());
    curr_keys = this->keys();

    for (int i = 0; i < curr_keys.getLength(); i++){
         value_chain->push(this->operator[](curr_keys[i]));
    };
    return *(value_chain);
};


template <class T>
Map<T>::Map(){
    sgdm::DefaultAllocator<T>* alloc = new sgdm::DefaultAllocator<T>();
    allocator = alloc;
    root.alter = NULL;
    root.next = NULL;
    root.use_time = 1;
    root.key = '\0';
    root.value = NULL;
};

template <class T>
Map<T>::Map(sgdm::IAllocator<T>* alloc){
    allocator = alloc;
    root.alter = NULL;
    root.next = NULL;
    root.use_time = 1;
    root.key = '\0';
    root.value = NULL;
};

template <class T>
Map<T>::Map(const Map &other){
    allocator = other.allocator;
    root.alter = other.root;
};

template <class T>
const Map<T>& Map<T>:: operator=(const Map<T> &other) {
    if (this != &other) {
        allocator = other.allocator;
	root.alter = other.root;
    };
    return *this;
};

template <class T>
Map<T>::~Map(){
};



template <class T>
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

template <class T>
trie_node<T>* Map<T>::add_alter(char c, trie_node<T>* curr_node){
    trie_node<T>* new_node = new trie_node<T>;
    new_node->alter = NULL;
    new_node->next = NULL;
    new_node->use_time = 1;
    new_node->key = c;
    new_node->value = NULL;
    curr_node->alter = new_node;
    curr_node = curr_node->alter;
    return curr_node;
}

template <class T>
trie_node<T>* Map<T>::add_next(char c, trie_node<T>* curr_node){
    trie_node<T>* new_node = new trie_node<T>;
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
