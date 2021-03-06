// player.h
    
#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#include "IActor.h"

namespace sgda
{
// class to save the data of player
class Player : public sgda::IActor{
  private:
    bool off;

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
    // set player off
    void setOff();
    // set player on
    void setOn();
    // check player is off
    bool isOff();

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
    off = false;
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
        this->ownerCell = other.ownerCell;
        this->off = other.off;
    };
}

// OPERATOR OVERLOADS
inline
Player& Player::operator = (const Player &other){
    if (this != &other) {
        this->d_sprite = other.d_sprite;
        this->d_bound = other.d_bound;
        this->ownerCell = other.ownerCell;
        this->off = other.off;
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



// set player off
inline
void Player::setOff(){
    this->off = true;
}

// set player off
inline
void Player::setOn(){
    this->off = false;
}

// check player is off or not
inline
bool Player::isOff(){
    return this->off;
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