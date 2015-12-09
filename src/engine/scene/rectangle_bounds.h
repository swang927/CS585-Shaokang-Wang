// rectangle_bounds.h
        
#ifndef INCLUDED_RECTANGELE_BOUND
#define INCLUDED_RECTANGELE_BOUND
    
#include <algorithm> 

namespace sgds
{
// A very simple bounding box (2D) rectangle
class RectangleBounds {
  private:
    // left corner position x
    float _x;
    // left corner position y 
    float _y;
    // the width of bounding box
    float _width;
    // the heiht of bounding box
    float _height;

public:
    // CONSTRUCTORS
    // default constructor.
    RectangleBounds();
    // Detail constructor.
    RectangleBounds(float x, float y, float width, float height);
    // DESTRUCTOR
    ~RectangleBounds();
    // OPERATOR OVERLOADS
    RectangleBounds& operator = (const RectangleBounds &other);

    // NOT EQUAL OPERATOR OVERLOADS
    bool operator != ( RectangleBounds &other);

    // Getter
    // left corner position x 
    float x() const;
    // left corner position y 
    float y() const;
    // the width of bounding box
    float width() const;
    // the heiht of bounding box
    float height() const;

    // Setter
    // set the left corner position x 
    void setX(float x);
    // set the left corner position y
    void setY(float y);
    // set the width of bounding box
    void setWidth(float width);
    // set the heiht of bounding box
    void setHeight(float height);
    // set the width and heiht of bounding box
    void setDimesions(float width, float height);
    // set the left corner position (x, y) 
    void setPosition(float x, float y);

    // collision detection 
    bool doesCollide(const RectangleBounds& candidate);
}; // end of class


// default constructor.
inline
RectangleBounds::RectangleBounds(){
    this->_x = 0;
    this->_y = 0;
    this->_height = 0;
    this->_width = 0;
}


// Detail constructor.
inline
RectangleBounds::RectangleBounds(float x, float y, float width, float height){
    this->_x = x;
    this->_y = y;
    this->_height = height;
    this->_width = width;
}


// DESTRUCTOR
inline
RectangleBounds::~RectangleBounds(){
}


// OPERATOR OVERLOADS
inline
RectangleBounds& RectangleBounds::operator = (const RectangleBounds &other){
    if (this != &other) {
        this->_x = other._x;
        this->_y = other._y;
        this->_width = other._width;
        this->_height= other._height;
    };
    return *this;
}


// NOT EQUAL OPERATOR OVERLOADS
inline
bool RectangleBounds::operator != (RectangleBounds &other){
    if (this->_x == other._x
        && this->_y == other._y
        && this->_width == other._width
        && this->_height == other._height)
        return false;
    else
        return true;
}
// Getter
// get left corner position x 
inline
float RectangleBounds::x() const{
    return this->_x;
}


// get the left corner position y
inline
float RectangleBounds::y() const{
    return this->_y;
}


// get the width of bounding box
inline
float RectangleBounds::width() const{
    return this->_width;
}


// get the heiht of bounding box
inline
float RectangleBounds::height() const{
    return this->_height;
}

 
// Setter
// set the left corner position x 
inline
void RectangleBounds::setX(float x){
    this->_x = x;
}


// set the left corner position y
inline
void RectangleBounds::setY(float y){
    this->_y = y;
}


// set the width of bounding box
inline
void RectangleBounds::setWidth(float width){
    this->_width = width;
}


// set the width of bounding box
inline
void RectangleBounds::setHeight(float height){
    this->_height = height;
}


// set the width and heiht of bounding box
inline
void RectangleBounds::setDimesions(float width, float height){
    this->_width = width;
    this->_height = height;
}


// set the left corner position (x, y) 
inline
void RectangleBounds::setPosition(float x, float y){
    this->_x = x;
    this->_y = y;
}


// collision detection
inline
bool RectangleBounds::doesCollide(const RectangleBounds& candidate){
    float A = this->_x, B = this->_y, C = A+this->_width, D = B+this->_height;
    float E = candidate.x(), F = candidate.y(), G = E+candidate.width(), H = F+candidate.height();
    if (std::max(A, E)<std::min(C, G) && std::max(B, F)<std::min(D, H))
        return true;
    else
        return false;
}
};
#endif