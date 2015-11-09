// rectangle_bounds.h

#ifndef INCLUDED_RECTANGELE_BOUND
#define INCLUDED_RECTANGELE_BOUND

#include <algorithm> 

namespace sgds
{
class RectangleBounds {
  private:
	float _x;
	float _y;
	float _width;
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


	// Getter
    float x() const;
	float y() const;
	float width() const;
	float height() const;

	// Setter
	void setX(float x);
	void setY(float y);
	void setWidth(float width);
	void setHeight(float height);
	void setDimesions(float width, float height);
	void setPosition(float x, float y);

	// collision detection 
	bool doesCollide(const RectangleBounds& candidate);
};

inline
RectangleBounds::RectangleBounds(){
	this->_x = 0;
	this->_y = 0;
	this->_height = 0;
	this->_width = 0;
}

inline
RectangleBounds::RectangleBounds(float x, float y, float width, float height){
	this->_x = x;
	this->_y = y;
	this->_height = height;
	this->_width = width;
}

inline
RectangleBounds::~RectangleBounds(){
}

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


// Getter
inline
float RectangleBounds::x() const{
	return this->_x;
}

inline
float RectangleBounds::y() const{
	return this->_y;
}

inline
float RectangleBounds::width() const{
	return this->_width;
}

inline
float RectangleBounds::height() const{
	return this->_height;
}

 
// Setter
inline
void RectangleBounds::setX(float x){
	this->_x = x;
}

inline
void RectangleBounds::setY(float y){
	this->_y = y;
}

inline
void RectangleBounds::setWidth(float width){
	this->_width = width;
}

inline
void RectangleBounds::setHeight(float height){
	this->_height = height;
}

inline
void RectangleBounds::setDimesions(float width, float height){
	this->_width = width;
	this->_height = height;
}

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