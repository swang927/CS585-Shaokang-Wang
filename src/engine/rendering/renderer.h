// renderer.h

#ifndef INCLUDED_RENDERER
#define INCLUDED_RENDERER

#include "../memory/iallocator.h"
#include "../memory/default_allocator.h"
#include "../containers/dynamic_array.h"
#include "../containers/map.h"
#include "renderable_sprite.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace sgdr
{
// implement our renderer specifically for SFML
class Renderer{
  private:
	sf::RenderWindow d_window;
	sgdc::DynamicArray<sgdr::RenderableSprite*> d_sprites;
	sgdc::Map<sf::Texture> d_textures;

	// CONSTRUCTORS
	Renderer(const Renderer &) = delete;
	Renderer(Renderer &&) = delete;
	// OPERATOR OVERLOADS
	Renderer& operator = (const Renderer &) = delete;
	Renderer& operator = (Renderer &&) = delete;

  public:
	// CONSTRUCTORS
    // does not open a window.
	Renderer();
	// set up window with some settings.
	Renderer(std::string title, int width, int height);
	// deconstructor
	~Renderer();

	void draw();
	// use object manager to alloc sprites memory(outside this class).
	void addSprite(RenderableSprite* sprite);
	// use object manager to dealloc sprites memory(outside this class).
	void removeSprite(RenderableSprite* sprite);
	// set up the window with name and size: x & y 
	void setupWindow(std::string title, int width, int height);
	// return window width
	int window_width();
	// return window height
	int window_height();
	// close the window
	void closewindow();
	// load the texture form outside
	bool loadTexture(const std::string & name, const std::string & path);
	// accesse certain texture
	sf::Texture& getTexture(const std::string & name);
	// Returns false once the window is ready to be destroyed
	bool isActive(); 

};

// CONSTRUCTORS
inline
Renderer::Renderer(){
}

inline
Renderer::Renderer(std::string title, int width, int height)
{
	d_window.create(sf::VideoMode(width, height), title);
}

// DESTRUCTORS
inline
Renderer::~Renderer()
{
	for (int i = d_sprites.getLength() - 1; i >= 0; ++i)
	{
		d_sprites.pop();
	}
	if (d_window.isOpen())
	{
		d_window.close();
	}
}



// if window is open draw all the sprites in list
inline
void Renderer::draw()
{
	assert(d_window.isOpen());

	d_window.clear();

	for (unsigned int i = 0; i < d_sprites.getLength(); ++i)
	{
		d_window.draw(d_sprites[i]->sprite());
	}

	d_window.display();
}


// add new sprite to the list
inline
void Renderer::addSprite(RenderableSprite* sprite){
	assert(sprite);
	d_sprites.push(sprite);
};

// remove a exist sprite from list
inline
void Renderer::removeSprite(RenderableSprite* sprite){
	assert(sprite);
	d_sprites.remove(sprite);
};

// set up the window with name and size: x & y 
inline
void Renderer::setupWindow(std::string title, int width, int height)
{
	if (d_window.isOpen())
	{
		d_window.setTitle(title);
		d_window.setPosition(sf::Vector2i(width, height));
	}
	else
	{
		d_window.create(sf::VideoMode(width, height), title);
	}
}


// load the texture form outside
inline 
bool Renderer::loadTexture(const std::string & name, const std::string & path)
{
	if (d_textures.has(name)){
		return false;
	}

	sf::Texture texture;
	if (texture.loadFromFile(path)){
		d_textures[name] = texture;
		return true;
	}

	return false;
}

// accesse certain texture
inline
sf::Texture& Renderer::getTexture(const std::string & name)
{
	assert(d_textures.has(name));
	return d_textures[name];
}

// check if a window is still usable
inline
bool Renderer::isActive()
{
	return d_window.isOpen();
}

// return window width
inline
int Renderer::window_width(){
	return d_window.getSize().x;
}

// return window height
inline
int Renderer::window_height(){
	return d_window.getSize().y;
}

// close the current window
inline
void Renderer::closewindow(){
	d_window.close();
}

};
#endif