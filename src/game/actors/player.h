// player.h

#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#include "IActor.h"

namespace sgda
{
// class to save the data of player
class Player : public sgda::IActor{
  public:
	sgdr::RenderableSprite d_sprite;
	sgds::RectangleBounds d_bound;
	int ownerCell;
	// constructor
	Player();
	// deconstructor
	~Player();
	// Copy constructor.
	Player(const Player &other);
	// OPERATOR OVERLOADS
	Player& operator = (const Player &other);

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
	bool canCollide(unsigned short flags) const { return true; };
};

// constructor
inline
Player::Player(){
	d_bound.setX(d_sprite.getPositionX());
	d_bound.setY(d_sprite.getPositionY());
	d_bound.setWidth(32);
	d_bound.setHeight(32);
}

// deconstructor
inline
Player::~Player(){
}

// Copy constructor.
inline
Player::Player(const Player &other){
	if (this != &other) {
		this->d_sprite = other.d_sprite;
		this->d_bound = other.d_bound;
	};
}

// OPERATOR OVERLOADS
inline
Player& Player::operator = (const Player &other){
	if (this != &other) {
		this->d_sprite = other.d_sprite;
		this->d_bound = other.d_bound;
	};
	return *this;
}


// update the bound
inline
void Player::updata(){
	d_bound.setX(d_sprite.getPositionX());
	d_bound.setY(d_sprite.getPositionY());
	d_bound.setWidth(32);
	d_bound.setHeight(32);
}

// get the boundary
inline
const sgds::RectangleBounds& Player::bounds() const{
	return d_bound;
}

// check the collide
inline
bool Player::doesCollide(const sgds::RectangleBounds& candidate){
	return d_bound.doesCollide(candidate);
};

// return the cell the sprite belong to
inline
int Player::getCell(){
	return ownerCell;
}
// set the cell the sprite belong to
inline
void Player::setCell(int index){
	ownerCell = index;
}

};

#endif