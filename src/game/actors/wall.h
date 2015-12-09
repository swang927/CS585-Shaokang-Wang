// wall.h
    
#ifndef INCLUDED_WALL
#define INCLUDED_WALL

#include "IActor.h"

namespace sgda
{
// class to save the data of weapon
class Wall : public sgda::IActor{
  public:
    // save the moving vector
    sgdr::RenderableSprite d_sprite;
    sgds::RectangleBounds d_bound;
    int ownerCell;

    // constructor
    Wall();
    // deconstructor
    ~Wall();
    // Copy constructor.
    Wall(const Wall &other);
    // OPERATOR OVERLOADS
    Wall& operator = (const Wall &other);


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
Wall::Wall(){
    d_bound.setX(d_sprite.getPositionX());
    d_bound.setY(d_sprite.getPositionY());
    d_bound.setWidth(32);
    d_bound.setHeight(32);
}

// deconstructor
inline
Wall::~Wall(){
}

// Copy constructor.
inline
Wall::Wall(const Wall &other){
    if (this != &other) {
        this->d_sprite = other.d_sprite;
        this->d_bound = other.d_bound;
    };
}

// OPERATOR OVERLOADS
inline
Wall& Wall::operator = (const Wall &other){
    if (this != &other) {
        this->d_sprite = other.d_sprite;
        this->d_bound = other.d_bound;
    };
    return *this;
}


// update the bound
inline
void Wall::updata(){
    d_bound.setX(d_sprite.getPositionX());
    d_bound.setY(d_sprite.getPositionY());
    d_bound.setWidth(32);
    d_bound.setHeight(32);
}

// get the boundary
inline
const sgds::RectangleBounds& Wall::bounds() const{
    return d_bound;
}

// check the collide
inline
bool Wall::doesCollide(const sgds::RectangleBounds& candidate){
    return d_bound.doesCollide(candidate);
};

// return the cell the sprite belong to
inline
int Wall::getCell(){
    return ownerCell;
}
// set the cell the sprite belong to
inline
void Wall::setCell(int index){
    ownerCell = index;
}

};

#endif