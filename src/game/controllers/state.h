// state.h
    
#ifndef INCLUDED_STATE
#define INCLUDED_STATE
    
#include "../actors/IActor.h"
#include "../../engine/containers/dynamic_array.h"

namespace mgc
{
// class to save the data of state
class State : public sgda::IActor{
  public:
	// save the state sprite for better debug
	sgdr::RenderableSprite d_sprite;
	// save the bound for collosion check;
	sgds::RectangleBounds d_bound;
	// save the states next to this state 
	sgdc::DynamicArray<State*> next;
	State* up;
	State* down;
	State* left;
	State* right;


	int ownerCell;

	// constructor
	State();
	// deconstructor
	~State();
	// Copy constructor.
	State(const State &other);
	// OPERATOR OVERLOADS
	State& operator = (const State &other);


	//updata the bound
	void updata();
	// get reachable states
	sgdc::DynamicArray<State*> reachable();

	// ICollider menber function
	// get the boundary
	const sgds::RectangleBounds& bounds() const;
	// check the collide
	bool doesCollide(const sgds::RectangleBounds& candidate);
	// return the cell the sprite belong to
	int getCell();
	// set the cell the sprite belong to
	void setCell(int index);

	// no need so far
	unsigned short shortflags() const { return 1; };
	void setFlags(unsigned short flags) {};
	bool canCollide(unsigned short flags) const { return true;  };
};


// constructor
inline
State::State(){
	State* up = NULL;
	State* down = NULL;
	State* left = NULL;
	State* right = NULL;
}

// deconstructor
inline
State::~State(){
}

// Copy constructor.
inline
State::State(const State &other){
	if (this != &other) {
		this->d_sprite = other.d_sprite;
		this->d_bound = other.d_bound;
		this->up = other.up;
		this->down = other.down;
		this->left = other.left;
		this->right = other.right;
	};
}

// OPERATOR OVERLOADS
inline
State& State::operator = (const State &other){
	if (this != &other) {
		this->d_sprite = other.d_sprite;
		this->d_bound = other.d_bound;
		this->up = other.up;
		this->down = other.down;
		this->left = other.left;
		this->right = other.right;
	};
	return *this;
}


// update the bound
inline
void State::updata(){
	d_bound.setX(d_sprite.getPositionX());
	d_bound.setY(d_sprite.getPositionY());
	d_bound.setWidth(32);
	d_bound.setHeight(32);
}


// get reachable states
inline
sgdc::DynamicArray<State*> State::reachable(){
	next.clean();
	if (up)
		next.push(up);
	if (down)
		next.push(down);
	if (left)
		next.push(left);
	if (right)
		next.push(right);
	return next;
}


// get the boundary
inline
const sgds::RectangleBounds& State::bounds() const{
	return d_bound;
}

// check the collide
inline
bool State::doesCollide(const sgds::RectangleBounds& candidate){
	return d_bound.doesCollide(candidate);
};

// return the cell the sprite belong to
inline
int State::getCell(){
	return ownerCell;
}

// set the cell the sprite belong to
inline
void State::setCell(int index){
	ownerCell = index;
}
};
#endif