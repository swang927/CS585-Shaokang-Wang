// guard.h
        
#ifndef INCLUDED_GUARD
#define INCLUDED_GUARD

#include "IActor.h"

namespace sgda
{
// class to save the data of weapon
class Guard : public sgda::IActor{
  private:
    bool off;

  public:
    enum Direct { Down, Left, Right, Up };
    // save the moving vector
    float speed;
    float dirction_x;
    float dirction_y;
    sgdr::RenderableSprite d_sprite;
    sgds::RectangleBounds d_bound;
    int ownerCell;

    // constructor
    Guard();
    // deconstructor
    ~Guard();    
    // Copy constructor.
    Guard(const Guard &other);
    // OPERATOR OVERLOADS
    Guard& operator = (const Guard &other);

    //updata the bound
    void updata();
    // get the direction
    int direction();
    // set guard off
    void setOff();
    // set guard on
    void setOn();
    // check guard is off or not
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
Guard::Guard(){
    d_bound.setX(d_sprite.getPositionX());
    d_bound.setY(d_sprite.getPositionY());
    d_bound.setWidth(32);
    d_bound.setHeight(32);
}

// deconstructor
inline
Guard::~Guard(){
}

// Copy constructor.
inline
Guard::Guard(const Guard &other){
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
Guard& Guard::operator = (const Guard &other){
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
void Guard::updata(){
    d_bound.setX(d_sprite.getPositionX());
    d_bound.setY(d_sprite.getPositionY());
    d_bound.setWidth(32);
    d_bound.setHeight(32);
}


// get the direction
inline
int Guard::direction(){
    if (dirction_y < 0)
        return Up;
    if (dirction_y > 0)
        return Down;
    if (dirction_x < 0)
        return Left;
    if (dirction_x > 0)
        return Right;
    return Down;
}


// set guard off
inline
void Guard::setOff(){
    this->off = true;
}

// set guard off
inline
void Guard::setOn(){
    this->off = false;
}

// check guard is off or not
inline
bool Guard::isOff(){
    return this->off;
}



// get the boundary
inline
const sgds::RectangleBounds& Guard::bounds() const{
    return d_bound;
}


// check the collide
inline
bool Guard::doesCollide(const sgds::RectangleBounds& candidate){
    return d_bound.doesCollide(candidate);
};

// return the cell the sprite belong to
inline
int Guard::getCell(){
    return ownerCell;
}

// set the cell the sprite belong to
inline
void Guard::setCell(int index){
    ownerCell = index;
}

};

#endif