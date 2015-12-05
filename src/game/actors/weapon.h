// weapon.h

#ifndef INCLUDED_WEAPON
#define INCLUDED_WEAPON

#include "IActor.h"

namespace sgda
{
// class to save the data of weapon
class Weapon : public sgda::IActor{
  public:
	// save the moving vector
	float speed;
	float dirction_x;
	float dirction_y;
	sgdr::RenderableSprite d_sprite;
	sgds::RectangleBounds d_bound;
	int ownerCell;

	// constructor
	Weapon();
	// deconstructor
	~Weapon();
	// Copy constructor.
	Weapon(const Weapon &other);
	// OPERATOR OVERLOADS
	Weapon& operator = (const Weapon &other);

	//updata the bound
	void updata();

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
Weapon::Weapon(){
	d_bound.setX(d_sprite.getPositionX());
	d_bound.setY(d_sprite.getPositionY());
	d_bound.setWidth(32);
	d_bound.setHeight(32);
}

// deconstructor
inline
Weapon::~Weapon(){
}

// Copy constructor.
inline
Weapon::Weapon(const Weapon &other){
	if (this != &other) {
		this->speed = other.speed;
		this->dirction_x = other.dirction_x;
		this->dirction_y = other.dirction_y;
		this->d_sprite = other.d_sprite;
		this->d_bound = other.d_bound;
	};
}

// OPERATOR OVERLOADS
inline
Weapon& Weapon::operator = (const Weapon &other){
	if (this != &other) {
		this->speed = other.speed;
		this->dirction_x = other.dirction_x;
		this->dirction_y = other.dirction_y;
		this->d_sprite = other.d_sprite;
		this->d_bound = other.d_bound;
	};
	return *this;
}


// update the bound
inline
void Weapon::updata(){
	d_bound.setX(d_sprite.getPositionX());
	d_bound.setY(d_sprite.getPositionY());
	d_bound.setWidth(32);
	d_bound.setHeight(32);
}

// get the boundary
inline
const sgds::RectangleBounds& Weapon::bounds() const{
	return d_bound;
}

// check the collide
inline
bool Weapon::doesCollide(const sgds::RectangleBounds& candidate){
	return d_bound.doesCollide(candidate);
};

// return the cell the sprite belong to
inline
int Weapon::getCell(){
	return ownerCell;
}
// set the cell the sprite belong to
inline
void Weapon::setCell(int index){
	ownerCell = index;
}

};

#endif