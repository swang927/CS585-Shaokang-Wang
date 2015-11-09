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
struct Cell
{
	RectangleBounds bound;
	sgdc::DynamicArray<ICollider*> objects;
};

class NxNSceneGraph : public ITickable {
  private:
	float _dimensions;
	float w_width;
	float w_height;
	float c_width;
	float c_height;
	int _n;
	sgdc::DynamicArray<Cell*> nxn_cells;
	Cell* getCell(RectangleBounds bound);
	

  public:
	// dimensions provides the width/height, divisions the number of cells per column/row
    NxNSceneGraph(float dimensions, int divisions);
	NxNSceneGraph(float width, float height, int divisions);
    void addCollider(ICollider* collider);
    void removeCollider(ICollider* collider);
	
	// finder
	sgdc::DynamicArray<ICollider*> find(float x, float y, float width, float height);
	sgdc::DynamicArray<ICollider*> find(float x, float y, float width, float height, unsigned short flags);
	sgdc::DynamicArray<ICollider*> find(const RectangleBounds& bounds);
	sgdc::DynamicArray<ICollider*> find(const RectangleBounds& bounds, unsigned short flags);
	// Do not return self
	sgdc::DynamicArray<ICollider*> find(const ICollider* collider); 
	
	// implement ITickable
	void preTick();
	void tick(float dtS);
	void postTick();

};

// constructor 
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



// finders
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
inline
void NxNSceneGraph::preTick(){
}

inline
void NxNSceneGraph::tick(float dtS){
}

inline
void NxNSceneGraph::postTick(){
};


};
#endif