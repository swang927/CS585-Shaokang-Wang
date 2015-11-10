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
	// base on the bound get the cell involved
    Cell* getCell(RectangleBounds bound);
    

  public:
	// Constructor
    // get the dimensions which provided the width/height, and divisions 
	// provided the number of cells per column/row
    NxNSceneGraph(float dimensions, int divisions);
	// get the width, height of window, and divisions 
	// provided the number of cells per column/row
    NxNSceneGraph(float width, float height, int divisions);
	// add new onject 
    void addCollider(ICollider* collider);
	// remove an exist object
    void removeCollider(ICollider* collider);
    
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
    
    // implement ITickable
	// pre-process
    void preTick();
	// process
    void tick(float dtS);
	// post-process
    void postTick();

};

// constructor
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
    for (unsigned int i = 0; i < _n*_n; i++){
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
    for (unsigned int i = 0; i < _n*_n; i++){
        float x = (i % _n)*c_width;
        float y = (i / _n)*c_height;
        Cell* cell =new Cell;
        cell->bound.setDimesions(c_width, c_height);
        cell->bound.setPosition(x, y);
        nxn_cells.push(cell);
    }
};


// base on the bound get the cell involved
inline
Cell* NxNSceneGraph::getCell(RectangleBounds bound){
    for (unsigned int i = 0; i < _n*_n; i++){
        if (nxn_cells[i]->bound.doesCollide(bound))
            return nxn_cells[i];
    }
    // if no collided rectangle return first cell
    return NULL;
};


// add new onject
inline
void NxNSceneGraph::addCollider(ICollider* collider){
    RectangleBounds bound = collider->bounds();
    if (getCell(bound))
      getCell(bound)->objects.push(collider);
};


// remove an exist object
inline
void NxNSceneGraph::removeCollider(ICollider* collider){
    RectangleBounds bound = collider->bounds();
    if (getCell(bound))
        getCell(bound)->objects.remove(collider);
};



// finder
// retrieve all the collider objects in the rectangel area definde by left corner and size
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(float x, float y, float width, float height){
    sgds::RectangleBounds bound(x, y, width, height);
    sgdc::DynamicArray<ICollider*> collection = *(new sgdc::DynamicArray <ICollider*>) ;
    for (unsigned int i = 0; i < _n*_n; i++)
    {
        if (nxn_cells[i]->bound.doesCollide(bound))
        {
            for (int j = 0; j < nxn_cells[i]->objects.getLength(); j++)
            {
                collection.push(nxn_cells[i]->objects[j]);
            }
        }
    }
    return collection;
};


// retrieve all the collider objects in the rectangel area definde by left corner, size and flags
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(float x, float y, float width, float height, unsigned short flags){
    sgds::RectangleBounds bound(x, y, width, height);
    sgdc::DynamicArray<ICollider*> collection = *(new sgdc::DynamicArray <ICollider*>);
    for (unsigned int i = 0; i < _n*_n; i++)
    {
        if (nxn_cells[i]->bound.doesCollide(bound))
        {
            for (int j = 0; j < nxn_cells[i]->objects.getLength(); j++)
            {
                collection.push(nxn_cells[i]->objects[j]);
            }
        }
    }
    return collection;
};


// retrieve all the collider objects in the rectangel area definde by bound
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(const RectangleBounds& bounds){
    sgdc::DynamicArray<ICollider*> collection = *(new sgdc::DynamicArray <ICollider*>);
    for (unsigned int i = 0; i < _n*_n; i++)
    {
        if (nxn_cells[i]->bound.doesCollide(bounds))
        {
            for (int j = 0; j < nxn_cells[i]->objects.getLength(); j++)
            {
                collection.push(nxn_cells[i]->objects[j]);
            }
        }
    }
    return collection;
};


// retrieve all the collider objects in the rectangel area definde by bound and flags
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(const RectangleBounds& bounds, unsigned short flags){
    sgdc::DynamicArray<ICollider*> collection = *(new sgdc::DynamicArray <ICollider*>);
    for (unsigned int i = 0; i < _n*_n; i++)
    {
        if (nxn_cells[i]->bound.doesCollide(bounds))
        {
            for (int j = 0; j < nxn_cells[i]->objects.getLength(); j++)
            {
                collection.push(nxn_cells[i]->objects[j]);
            }
        }
    }
    return collection;
};

// Do not return self
inline
sgdc::DynamicArray<ICollider*> NxNSceneGraph::find(const ICollider* collider){
    sgdc::DynamicArray<ICollider*> collection = *(new sgdc::DynamicArray <ICollider*>);
    RectangleBounds bound = collider->bounds();
    Cell* position = getCell(bound);
    if (position){
        for (int j = 0; j < position->objects.getLength(); j++){
            if (position->objects[j] != collider){
                collection.push(position->objects[j]);
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