// renderable_sprite.h
    
#ifndef INCLUDED_RENDERABLE_SPRITE
#define INCLUDED_RENDERABLE_SPRITE

#include <SFML/Graphics.hpp>

namespace sgdr
{
// provide a base reusable component for managing sprites that are drawable on the screen
class RenderableSprite{
  private:
    // default spirte
    sf::Sprite d_sprite;

    // move constructor.
    RenderableSprite(RenderableSprite &&) = delete;
    // move assignment.
    RenderableSprite& operator = (RenderableSprite &&) = delete;
    

  public:
    // Constructor
    RenderableSprite();
    // copy constructor.
    RenderableSprite(const RenderableSprite &);
    // Operator overload
    RenderableSprite& operator = (const RenderableSprite &);
    // Deconstructor
    ~RenderableSprite();

    // Accessors
    // access the sfml sprite
    sf::Sprite& sprite();
    // access absolute x position
    float getPositionX();
    // access absolute y position
    float getPositionY();
    
    // Mutators
    // Sets absolute x/y position
    void setPosition(float x, float y);    
    // Increments x by x, y by y
    void move(float x, float y);
    // Set texture to spirit
    void setTexture(const sf::Texture &texture);
    // Set the Texture rectangle
    void setTextureRect(int position_x, int position_y, int width, int height);
    // Set the color
    void setColor(const sf::Color &color);
};

// constructor
inline
RenderableSprite::RenderableSprite(){
};

// copy constructor.
inline
RenderableSprite::RenderableSprite(const RenderableSprite & obj)
{
    d_sprite.setTexture(*obj.d_sprite.getTexture());
    d_sprite.setTextureRect(obj.d_sprite.getTextureRect());
    d_sprite.setScale(obj.d_sprite.getScale());
    d_sprite.setRotation(obj.d_sprite.getRotation());
    d_sprite.setPosition(obj.d_sprite.getPosition());
}

// Operator overload
inline
RenderableSprite& RenderableSprite::operator = (const RenderableSprite & obj)
{
    if (this != &obj)
    {
        d_sprite.setTexture(*obj.d_sprite.getTexture());
        d_sprite.setTextureRect(obj.d_sprite.getTextureRect());
        d_sprite.setScale(obj.d_sprite.getScale());
        d_sprite.setRotation(obj.d_sprite.getRotation());
        d_sprite.setPosition(obj.d_sprite.getPosition());
    }
    return *this;
}

// deconstructor
inline
RenderableSprite::~RenderableSprite(){
};

// get sprite
inline
sf::Sprite& RenderableSprite::sprite(){
    return d_sprite;
};

// access absolute x position
inline
float RenderableSprite::getPositionX(){
    return d_sprite.getPosition().x;
};

// access absolute y position
inline
float RenderableSprite::getPositionY(){
    return d_sprite.getPosition().y;
};


// Sets absolute x/y position
inline
void RenderableSprite::setPosition(float x, float y) {
    d_sprite.setPosition(x, y);
};

// Increments x by dx, y by dy
inline
void RenderableSprite::move(float dx, float dy){
    d_sprite.move(dx, dy);
};


// Set texture to spirit
inline
void RenderableSprite::setTexture(const sf::Texture &texture){
    d_sprite.setTexture(texture);
};

// Set the Texture rectangle
inline
void RenderableSprite::setTextureRect(int position_x, int position_y, int width, int height){

    d_sprite.setTextureRect(sf::IntRect(position_x, position_y, width, height));
};

// Set the color
inline
void RenderableSprite::setColor(const sf::Color &color){
}
};
#endif