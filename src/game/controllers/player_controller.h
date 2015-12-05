// player_controller.h

#ifndef INCLUDED_PLAYER_CONTROLLER
#define INCLUDED_PLAYER_CONTROLLER

#include "../../engine/rendering/renderable_sprite.h"
#include "../../engine/containers/dynamic_array.h"
#include "../actors/player.h"
#include "../../engine/scene/nxn_scene_graph.h"

namespace mgc
{
// The PlayerController process input and move around an actor 
// The Actor must be controlled using the WASD keys. 
// The Actor must be bound by the world constraints. 
// Colliders must collide away from the Actor.
class PlayerController{
  private:
	// save all sprites, I do this list in case in the future
	// there are multiply sprites can use this contoller
	sgdc::DynamicArray<sgda::Player *> players;
	sf::RenderWindow *d_window;
	unsigned int num = 0;
	sgds::NxNSceneGraph* d_grid;

  public:
	// constructor
	PlayerController();
	// creat controller with relate window and grid 
	PlayerController(sf::RenderWindow* window, sgds::NxNSceneGraph* grid);
	// Operator overload
	const PlayerController& operator=(const PlayerController &other);
	// Deconstructor
	~PlayerController();


	// add sprite
	void add_instance(sgda::Player*  player);
	// remove sprite
	void remove_instance(sgda::Player* player);

	// move
	void move(int id, double dx, double dy);

	
};// end of class


// constructor
inline
PlayerController::PlayerController(){
}

// creat controller with relate window and grid 
inline
PlayerController::PlayerController(sf::RenderWindow* window, sgds::NxNSceneGraph* grid){
	d_window = window;
	d_grid = grid;
};


// Operator overload
inline
const PlayerController& PlayerController::operator = (const PlayerController &other){
	if (this != &other){
		this->d_window = other.d_window;
		this->d_grid = other.d_grid;
		this->players = other.players;
		this->num = other.num;
	}
	return *this;
}


// Deconstructor
inline
PlayerController::~PlayerController(){
}

// add new sprite to the list
inline
void PlayerController::add_instance(sgda::Player*  player){
	assert(player);
	players.push(player);
	num++;
};

// remove a exist sprite from list
inline
void PlayerController::remove_instance(sgda::Player*  player){
	assert(player);
	players.remove(player);
	num--;
};

// move the sprite
inline
void PlayerController::move(int id, double dx, double dy){
	// set the boundary box width and height 
	float width = (float) d_window->getSize().x - 32;
	float height = (float) d_window->getSize().y - 32;

	//check the boundary, hard code here
	// move on x axis
	players[id]->d_sprite.move((float)dx, 0);
	if (players[id]->d_sprite.getPositionX() < 0)
		players[id]->d_sprite.setPosition(0, players[id]->d_sprite.getPositionY());
	if (players[id]->d_sprite.getPositionX() > width)
		players[id]->d_sprite.setPosition(width, players[id]->d_sprite.getPositionY());
	// move on y axis
	players[id]->d_sprite.move(0, (float)dy);
	if (players[id]->d_sprite.getPositionY() < 0)
		players[id]->d_sprite.setPosition(players[id]->d_sprite.getPositionX(), 0);
	if (players[id]->d_sprite.getPositionY() > height)
		players[id]->d_sprite.setPosition(players[id]->d_sprite.getPositionX(), height);
	// update the bound
	players[id]->updata();

	// check if the actor move to different cell; if did swith the cell
	int place = d_grid->getCellindex(players[id]->d_bound);
	if (place != players[id]->getCell()){
		d_grid->removeCollider(players[id], players[id]->getCell());
		d_grid->addCollider(players[id], place);
	}
};

} // end of namespace
#endif