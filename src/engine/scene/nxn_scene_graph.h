// nxn_scene_graph.h

#ifndef INCLUDED_NXN_SCENE_GRAPH
#define INCLUDED_NXN_SCENE_GRAPH
    
#include "itickable.h"
#include "icollider.h"
#include "rectangle_bounds.h"
#include "../containers/dynamic_array.h"
#include "../containers/map.h"

namespace sgds
{
// defind the cell as unit for the grid
struct Cell
{
	// the rectangle bound for cell
    RectangleBounds bound;
	// the objects list in this cell
    sgdc::DynamicArray<ICollider*> objects;
};

// Uniform, 2 dimensional spatial partition of fixed size
// which is used for querying against
class NxNSceneGraph : public ITickable {
  private:
	// the dimentions of the window
    float _dimensions;
	// window width
    float w_width;
	// window height
    float w_height;
	// cell width
    float c_width;
	// cell height
    float c_height;
	// number of cell in each row or column 
    int _n;
	// the cell list  
    sgdc::DynamicArray<Cell*> nxn_cells;
	// a collection of target IColliders
	sgdc::DynamicArray<ICollider*> collection;

  public:
	// Constructor
	NxNSceneGraph();
    // get the dimensions which provided the width/height, and divisions 
	// provided the number of cells per column/row
    NxNSceneGraph(float dimensions, int divisions);
	// get the width, height of window, and divisions 
	// provided the number of cells per column/row
    NxNSceneGraph(float width, float height, int divisions);
	// Operator overload
	const NxNSceneGraph& operator=(const NxNSceneGraph &other);
	// Deconstructor
	~NxNSceneGraph();

	// Accessor
	// base on the bound get the cell involved
	Cell* getCell(RectangleBounds bound);
	// base on the bound get the involved cell's index
	int getCellindex(RectangleBounds bound);

	// Editor
	// add new onject 
    void addCollider(ICollider* collider);
	// add new onject to certain cell
	void addCollider(ICollider* collider, int index);
	// remove an exist object
    void removeCollider(ICollider* collider);
	// remove an exist object from certain cell
	void removeCollider(ICollider* collider, int index);

    
    // finder
	// retrieve all the collider objects in the rectangel area definde by left corner and size
    sgdc::DynamicArray<ICollider*> find(float x, float y, float width, float height);
	// retrieve all the collider objects in the rectangel area definde by left corner, size and flags
    sgdc::DynamicArray<ICollider*> find(float x, float y, float width, float height, unsigned short flags);
	// retrieve all the collider objects in the rectangel area definde by bound
    sgdc::DynamicArray<ICollider*> find(const RectangleBounds& bounds);
	// retrieve all the collider objects in the rectangel area definde by bound and flags
    sgdc::DynamicArray<ICollider*> find(const RectangleBounds& bounds, unsigned short flags);
    // Do not return self
    sgdc::DynamicArray<ICollider*> find(const ICollider* collider);
	// retrieve all the collider objects in the cell and its neighbor cells
	sgdc::DynamicArray<ICollider*> find_around(const ICollider* collider);
    
    // implement ITickable
	// pre-process
    void preTick();
	// process
    void tick(float dtS);
	// post-process
    void postTick();

};

// Constructor
inline
NxNSceneGraph::NxNSceneGraph(){
}
// get the dimensions which provided the width/height, and divisions 
// provided the number of cells per column/row
inline
NxNSceneGraph::NxNSceneGraph(float dimensions, int divisions){
    this->_dimensions = dimensions;
    this->_n = divisions;
    this->w_width = dimensions;
    this->w_height = 1;
    this->c_width = this->w_width / this->_n;
    this->c_height = this->w_height / this->_n;
    for (int i = 0; i < _n*_n; i++){
        float x = (i % _n)*c_width;
        float y = (i / _n)*c_height;
        Cell* cell =new Cell;
        cell->bound.setDimesions(c_width, c_height);
        cell->bound.setPosition(x, y);
        nxn_cells.push(cell);
    }

};


// get the width, height of window, and divisions 
// provided the number of cells per column/row
inline
NxNSceneGraph::NxNSceneGraph(float width, float height, int divisions){
    this->_dimensions = width/height;
    this->_n = divisions;
    this->w_width = width;
    this->w_height = height;
    this->c_width = this->w_width/ this->_n;
    this->c_height = this->w_height / this->_n;
    for (int i = 0; i < _n*_n; i++){
        float x = (i % _n)*c_width;
        float y = (i / _n)*c_height;
        Cell* cell =new Cell;
        cell->bound.setDimesions(c_width, c_height);
        cell->bound.setPosition(x, y);
        nxn_cells.push(cell);
    }
};


// Operator overload
inline
const NxNSceneGraph& NxNSceneGraph::operator=(const NxNSceneGraph &other){
	if (this != &other){
		this->_dimensions = other._dimensions;
		this->_n = other._n;
		this->w_width = other.w_width;
		this->w_height = other.w_height;
		this->c_width = this->w_width / this->_n;
		this->c_height = this->w_height / this->_n;
		for (int i = 0; i < _n*_n; i++){
			float x = (i % _n)*c_width;
			float y = (i / _n)*c_height;
			Cell* cell = new Cell;
			cell->bound.setDimesions(c_width, c_height);
			cell->bound.setPosition(x, y);
			nxn_cells.push(cell);
		}
	}
	return *this;
}

// Deconstructor
inline
NxNSceneGraph::~NxNSceneGraph(){
}


// base on the bound get the cell involved
inline
Cell* NxNSceneGraph::getCell(RectangleBounds bound){
    for (int i = 0; i < _n*_n; i++){
        if (nxn_cells[i]->bound.doesCollide(bound))
            return nxn_cells[i];
    }
    // if no collided rectangle return first cell
    return NULL;
};

// base on the bound get the involved cell's index
inline
int NxNSceneGraph::getCellindex(RectangleBounds bound){
	for (int i = 0; i < _n*_n; i++){
		if (nxn_cells[i]->bound.doesCollide(bound))
			return i;
	}
	// if no collided rectangle return first cell
	return -1;
};

// add new onject
inline
void NxNSceneGraph::addCollider(ICollider* collider){
    RectangleBounds bound = collider->bounds();
	int i = getCellindex(bound);
	if (i>= 0){
		nxn_cells[i]->objects.push(collider);
		collider->setCell(i);
	}
};

// add new onject to certain cell
inline
void NxNSceneGraph::addCollider(ICollider* collider, int index){
	nxn_cells[index]->objects.push(collider);
	collider->setCell(index);
};


// remove an exist object
inline
void NxNSceneGraph::removeCollider(ICollider* collider){
    RectangleBounds bound = collider->bounds();
	int i = getCellindex(bound);
	if (i >= 0){
		nxn_cells[i]->objects.remove(collider);
		collider->setCell(-1);
	}
};

// remove an exist object from certain cell
inline
void NxNSceneGraph::removeCollider(ICollider* collider, int index){
	nxn_cells[index]->objects.remove(collider);
	collider->setCell(-1);
};

// finder
// retrieve all the collider objects in the rectangel area definde by left corner and size
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(float x, float y, float width, float height){
    sgds::RectangleBounds bound(x, y, width, height);
    collection.clean();
	Cell* position = getCell(bound);
	if (position){
		for (unsigned int j = 0; j < position->objects.getLength(); j++){
			collection.push(position->objects[j]);
		}
	}
    return collection;
};


// retrieve all the collider objects in the rectangel area definde by left corner, size and flags
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(float x, float y, float width, float height, unsigned short flags){
    sgds::RectangleBounds bound(x, y, width, height);
	collection.clean();
	Cell* position = getCell(bound);
	if (position && flags){
		for (unsigned int j = 0; j < position->objects.getLength(); j++){
			collection.push(position->objects[j]);
		}
	}
    return collection;
};


// retrieve all the collider objects in the rectangel area definde by bound
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(const RectangleBounds& bound){
	collection.clean();
	Cell* position = getCell(bound);
	if (position){
		for (unsigned int j = 0; j < position->objects.getLength(); j++){
				collection.push(position->objects[j]);
		}
	}
	return collection;
};


// retrieve all the collider objects in the rectangel area definde by bound and flags
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(const RectangleBounds& bound, unsigned short flags){
	collection.clean();
	Cell* position = getCell(bound);
	if (position && flags){
		for (unsigned int j = 0; j < position->objects.getLength(); j++){
			collection.push(position->objects[j]);
		}
	}
	return collection;
};


// Do not return self
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(const ICollider* collider){
    collection.clean();
    RectangleBounds bound = collider->bounds();
    Cell* position = getCell(bound);
    if (position){
        for (unsigned int j = 0; j < position->objects.getLength(); j++){
            if (position->objects[j] != collider){
                collection.push(position->objects[j]);
            }
        }
    }
    return collection;
};

// retrieve all the collider objects in the cell and its neighbor cells
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find_around(const ICollider* collider){
	collection.clean();
	RectangleBounds bound = collider->bounds();
	// template position
	int t_position = -1;
	// current cell index
	int position = getCellindex(bound);
	if (position >= 0){
		// check its own cell
		for (unsigned int j = 0; j < nxn_cells[position]->objects.getLength(); j++){
			if (nxn_cells[position]->objects[j] != collider)
				collection.push(nxn_cells[position]->objects[j]);
		}
		// check the top left cell
		if ((position-_n-1) >= 0){
			t_position = position-_n-1;
			for (unsigned int j = 0; j < nxn_cells[t_position]->objects.getLength(); j++){
				collection.push(nxn_cells[t_position]->objects[j]);
			}
		}
		// check the top cell
		if ((position-_n) >= 0){
			t_position = position - _n;
			for (unsigned int j = 0; j < nxn_cells[t_position]->objects.getLength(); j++){
				collection.push(nxn_cells[t_position]->objects[j]);
			}
		}
		// check the top right cell
		if ((position-_n+1) >= 0){
			t_position = position - _n + 1;
			for (unsigned int j = 0; j < nxn_cells[t_position]->objects.getLength(); j++){
				collection.push(nxn_cells[t_position]->objects[j]);
			}
		}
		// check the  left cell
		if ((position-1) >= 0){
			t_position = position - 1;
			for (unsigned int j = 0; j < nxn_cells[t_position]->objects.getLength(); j++){
				collection.push(nxn_cells[t_position]->objects[j]);
			}
		}
		// check the right cell
		if ((position+1) < _n*_n){
			t_position = position + 1;
			for (unsigned int j = 0; j < nxn_cells[t_position]->objects.getLength(); j++){
				collection.push(nxn_cells[t_position]->objects[j]);
			}
		}
		// check the bottom left cell
		if ((position + _n - 1)  < _n*_n){
			t_position = position + _n - 1;
			for (unsigned int j = 0; j < nxn_cells[t_position]->objects.getLength(); j++){
				collection.push(nxn_cells[t_position]->objects[j]);
			}
		}
		// check the bottom cell
		if ((position + _n)  < _n*_n){
			t_position = position + _n;
			for (unsigned int j = 0; j < nxn_cells[t_position]->objects.getLength(); j++){
				collection.push(nxn_cells[t_position]->objects[j]);
			}
		}
		// check the bottom right cell
		if ((position + _n + 1)  < _n*_n){
			t_position = position + _n + 1;
			for (unsigned int j = 0; j < nxn_cells[t_position]->objects.getLength(); j++){
				collection.push(nxn_cells[t_position]->objects[j]);
			}
		}
	}
	return collection;
};

// implement ITickable
// pre-process
inline
void NxNSceneGraph::preTick(){
}


// process
inline
void NxNSceneGraph::tick(float dtS){
}


// post-process
inline
void NxNSceneGraph::postTick(){
};


};
#endif