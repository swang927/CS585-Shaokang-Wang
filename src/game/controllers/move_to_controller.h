// move_to_controller.h

#ifndef INCLUDED_MOVE_TO_CONTROLLER
#define INCLUDED_MOVE_TO_CONTROLLER

#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../engine/rendering/renderable_sprite.h"
#include "../../engine/containers/dynamic_array.h"
#include "../actors/weapon.h"
#include "../../engine/scene/nxn_scene_graph.h"

namespace mgc
{
#define PI 3.14159265

// Select a world extent, move toward it until collision 
// and then reflect on the line of collision. Move infinitely.
class MoveToController{
  private:
	  // save the moving vector
	  sgdc::DynamicArray<sgda::Weapon *> weapons;
	  sf::RenderWindow *d_window;
	  // static grid
	  sgds::NxNSceneGraph* d_grid;
	  // flag for initialization
	  bool has_init = false;
	  unsigned int num = 0;
	  // move actor on x axis
	  void move_X(sgda::Weapon* weapon);
	  // move actor on y axis
	  void move_Y(sgda::Weapon* weapon);

  public:
	  // constructor
	  MoveToController();
	  // creat controller with relate window and grid
	  MoveToController(sf::RenderWindow* window, sgds::NxNSceneGraph* grid);
	  // Operator overload
	  const MoveToController& operator=(const MoveToController &other);
	  // Deconstructor
	  ~MoveToController();


	  // add sprite
	  void add_instance(sgda::Weapon* weapon);
	  // remove sprite
	  void remove_instance(sgda::Weapon* weapon);

	  // initial data
	  void init();
	  // initial certain object data
	  void init(sgda::Weapon* weapon);
	  // updata function
	  void update();

	  // check the collision
	  const sgds::RectangleBounds* collisionWith(sgds::ICollider* self);

};// end of class

// constructor
inline
MoveToController::MoveToController(){
}

// creat controller with relate window and grid
inline
MoveToController::MoveToController(sf::RenderWindow* window, sgds::NxNSceneGraph* grid){
	d_window = window;
	d_grid = grid;
};

// Operator overload
inline
const MoveToController& MoveToController::operator = (const MoveToController &other){
	if(this != &other){
		this->d_window = other.d_window;
		this->d_grid = other.d_grid;
		this->weapons = other.weapons;
		this->has_init = other.has_init;
		this->num = other.num;
	}
	return *this;
}

// Deconstructor
inline
MoveToController::~MoveToController(){
}

// add new sprite to the list
inline
void MoveToController::add_instance(sgda::Weapon * weapon){
	assert(weapon);
	if (has_init)
		init(weapon);
	weapons.push(weapon);
	num++;
};

// remove a exist sprite from list
inline
void MoveToController::remove_instance(sgda::Weapon * weapon){
	assert(weapon);
	weapons.remove(weapon);
	num--;
};

// initial certain object data
inline
void MoveToController::init(sgda::Weapon* weapon){
	/* initialize random seed: */
	srand((unsigned int)time(NULL));
	// direction
	float degree = 360 * (rand() / float(RAND_MAX));
	weapon->dirction_x = (float)sin(degree*PI / 180);
	weapon->dirction_y = (float)cos(degree*PI / 180);
	// speed 
	weapon->speed = 0.5;

	float x = 0;
	float y = 0;
	// start position
	weapon->d_sprite.setPosition(x, y);
	// update the bound
	weapon->updata();

	// check if the actor move to different cell; if did swith the cell
	int place = d_grid->getCellindex(weapon->d_bound);
	if (place != weapon->getCell()){
		d_grid->removeCollider(weapon, weapon->getCell());
		d_grid->addCollider(weapon, place);
	}
}


// inital the AI data: speed, direction and start point
inline
void MoveToController::init(){
	has_init = true;
	/* initialize random seed: */
	srand((unsigned int)time(NULL));
	// go through all elements
	for (unsigned int i = 0; i < num; i++){
		// direction
		float degree = 360 * (rand() / float(RAND_MAX));
		weapons[i]->dirction_x = (float)sin(degree*PI / 180);
		weapons[i]->dirction_y = (float)cos(degree*PI / 180);
		// speed 
		weapons[i]->speed = 1;
		
		float x = ((rand()) / float(RAND_MAX))*(d_window->getSize().x - 32);
		float y = ((rand()) / float(RAND_MAX))*(d_window->getSize().y - 32);
		// start position
		weapons[i]->d_sprite.setPosition(x, y);
		// update the bound
		weapons[i]->updata();

		// check if the actor move to different cell; if did swith the cell
		int place = d_grid->getCellindex(weapons[i]->d_bound);
		if (place != weapons[i]->getCell()){
			d_grid->removeCollider(weapons[i], weapons[i]->getCell());
			d_grid->addCollider(weapons[i], place);
		}
	}
};


inline
void MoveToController::update(){	 
	for (unsigned int i = 0; i < num; i++){
		// move on x axis
		move_X(weapons[i]);
		// move on y axis
		move_Y(weapons[i]);
		// update the bound
		weapons[i]->updata();

		// check if the actor move to different cell; if did swith the cell
		int place = d_grid->getCellindex(weapons[i]->d_bound);
		if (place != weapons[i]->getCell()){
			d_grid->removeCollider(weapons[i], weapons[i]->getCell());
			d_grid->addCollider(weapons[i], place);
		}
	}
};


// move actor on x axis
inline 
void MoveToController::move_X(sgda::Weapon* current){
	// get the boundary box width
	float width = (float)d_window->getSize().x - 32;
	
	// move on x axis
	current->d_sprite.move(current->dirction_x * current->speed, 0);
	
	// check collision with other object
	const sgds::RectangleBounds* block = collisionWith(current);
	// if collision happen, then make change to current actor
	if (block){
		if (block->x() == current->d_bound.x()){
			if (current->dirction_x > 0)
				current->d_sprite.setPosition(block->x() + block->width(), current->d_sprite.getPositionY());
			else
				current->d_sprite.setPosition(block->x() - current->d_bound.width(), current->d_sprite.getPositionY());
		}
		else{
			if (current->dirction_x > 0)
				current->d_sprite.setPosition(block->x() - current->d_bound.width(), current->d_sprite.getPositionY());
			else
				current->d_sprite.setPosition(block->x() + block->width(), current->d_sprite.getPositionY());
		}
		
		current->dirction_x = -current->dirction_x;
	}

	// check the window bound
	if (current->d_sprite.getPositionX() < 0){
		current->d_sprite.setPosition(0, current->d_sprite.getPositionY());
		current->dirction_x = -current->dirction_x;
	}
	if (current->d_sprite.getPositionX() > width){
		current->d_sprite.setPosition(width, current->d_sprite.getPositionY());
		current->dirction_x = -current->dirction_x;
	}
}

// move actor on y axis
inline
void MoveToController::move_Y(sgda::Weapon* current){
	// get the boundary box height 
	float height = (float)d_window->getSize().y - 32;
	
	// move on x axis
	current->d_sprite.move(0, current->dirction_y * current->speed);

	// check collision with other object
	const sgds::RectangleBounds* block = collisionWith(current);
	// if collision happen, then make change to current actor
	if (block){
		if (block->y() == current->d_bound.y()){
			if (current->dirction_y > 0)
				current->d_sprite.setPosition(current->d_sprite.getPositionX(), block->y() + block->height());
			else
				current->d_sprite.setPosition(current->d_sprite.getPositionX(), block->y() - current->d_bound.height());
		}
		else{
			if (current->dirction_y > 0)
				current->d_sprite.setPosition(current->d_sprite.getPositionX(), block->y() - current->d_bound.height());
			else
				current->d_sprite.setPosition(current->d_sprite.getPositionX(), block->y() + block->height());
		}
		
		current->dirction_y = -current->dirction_y;
	}
	// check the window bound
	if (current->d_sprite.getPositionY() < 0){
		current->d_sprite.setPosition(current->d_sprite.getPositionX(), 0);
		current->dirction_y = -current->dirction_y;
	}
	if (current->d_sprite.getPositionY() > height){
		current->d_sprite.setPosition(current->d_sprite.getPositionX(), height);
		current->dirction_y = -current->dirction_y;
	}
}


// check the collision
inline
const sgds::RectangleBounds* MoveToController::collisionWith(sgds::ICollider* self){
	sgdc::DynamicArray<sgds::ICollider*> check_list = d_grid->find_around(self);
	for (unsigned int i = 0; i < check_list.getLength(); i++)
	{
		if (self->doesCollide(check_list[i]->bounds()))
			return &(check_list[i]->bounds());
	}
	return nullptr;
}
 
} // end of namespace
#endif