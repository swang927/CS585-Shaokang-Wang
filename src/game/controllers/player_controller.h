// player_controller.h

#ifndef INCLUDED_PLAYER_CONTROLLER
#define INCLUDED_PLAYER_CONTROLLER
    
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "../../engine/rendering/renderable_sprite.h"
#include "../../engine/containers/dynamic_array.h"
#include "../actors/player.h"
#include "../../engine/scene/nxn_scene_graph.h"
#include "state_machine.h"
#include "state.h"

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
    mgc::StateMachine* d_state_machine;
    // the model of the game
    int model;

  public:
    // constructor
    PlayerController();
    // creat controller with relate window and grid 
    PlayerController(sf::RenderWindow* window, sgds::NxNSceneGraph* grid, mgc::StateMachine* state_machine);
    // Operator overload
    const PlayerController& operator=(const PlayerController &other);
    // Deconstructor
    ~PlayerController();

    // initial data
    void init();

    // add sprite
    void add_instance(sgda::Player*  player);
    // remove sprite
    void remove_instance(sgda::Player* player);
    // move
    void move(int id, double dx, double dy);
    // check the collision
    const sgds::ICollider* collisionWith(sgds::ICollider* self);
    // check the state
    const mgc::State* checkstate(sgds::ICollider* self);
    // move from cell to cell
    void moveCell(sgda::Player* player);
    
    // set model 
    void setModel(int i);
    // get model
    int getModel();

};// end of class

// constructor
inline
PlayerController::PlayerController(){
}

// creat controller with relate window and grid 
inline
PlayerController::PlayerController(sf::RenderWindow* window, sgds::NxNSceneGraph* grid, mgc::StateMachine* state_machine){
    d_window = window;
    d_grid = grid;
    d_state_machine = state_machine;
};

// Operator overload
inline
const PlayerController& PlayerController::operator = (const PlayerController &other){
    if (this != &other){
        this->d_window = other.d_window;
        this->d_grid = other.d_grid;
        this->players = other.players;
        this->num = other.num;
        this->d_state_machine = other.d_state_machine;
        this->model = other.model;
    }
    return *this;
}

// Deconstructor
inline
PlayerController::~PlayerController(){
}

inline
void PlayerController::init(){
    model = 1;
    float x, y;
    int r;
    // go through all elements
    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < num; i++){
        // start position
        r = (rand() % 10);
        x = d_state_machine->states[r]->d_bound.x();
        y = d_state_machine->states[r]->d_bound.y();
        players[i]->d_sprite.setPosition(x, y);
        // updata the state
        d_state_machine->hero = players[i];
        // update the bound
        players[i]->updata();
        moveCell(players[i]);
    }
};


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
    const sgds::ICollider* block;
    const mgc::State* spot;
    // move on x axis
    players[id]->d_sprite.move(dx, 0);
    players[id]->updata();
    moveCell(players[id]);
    // check collision with other object
    block = collisionWith(players[id]);
    // if collision happen, then make change to players[id] actor
    if (block){
        players[id]->d_sprite.move(-dx, 0);
        players[id]->updata();
        moveCell(players[id]);
        if (block == d_state_machine->blue ){
            if (model == 1)
                players[id]->setOff();
            else
                d_state_machine->blue->setOff();
        }
        if (block == d_state_machine->red){
            if (model == 1)
                players[id]->setOff();
            else
                d_state_machine->red->setOff();
        }
    }
    // if hit ths state spot then shift to state spot
    spot = checkstate(players[id]);
    if (spot){
        float d = spot->d_bound.x() - players[id]->bounds().x();
        if (d < 30 && d > 0 && dx >= 0){
            players[id]->d_sprite.setPosition(spot->d_bound.x(), spot->d_bound.y());
        }
        if (d > -30 && d < 0 && dx <= 0){
            players[id]->d_sprite.setPosition(spot->d_bound.x(), spot->d_bound.y());
        }
        players[id]->updata();
        moveCell(players[id]);
    }


    // move on y axis
    players[id]->d_sprite.move(0, dy);
    players[id]->updata();
    moveCell(players[id]);
    // check collision with other object
    block = collisionWith(players[id]);
    // if collision happen, then make change to players[id] actor
    if (block){
        players[id]->d_sprite.move(0, -dy);
        players[id]->updata();
        moveCell(players[id]);
        if (block == d_state_machine->blue){
            if (model == 1)
                players[id]->setOff();
            else
                d_state_machine->blue->setOff();
        }
        if (block == d_state_machine->red){
            if (model == 1)
                players[id]->setOff();
            else
                d_state_machine->red->setOff();
        }
    }
    // if hit ths state spot then shift to state spot
    spot = checkstate(players[id]);
    if (spot){
        float d = spot->d_bound.y() - players[id]->bounds().y();
        if (d < 30 && d > 0 && dy >= 0){
            players[id]->d_sprite.setPosition(spot->d_bound.x(), spot->d_bound.y());
        }
        if (d > -30 && d < 0 && dy <= 0){
            players[id]->d_sprite.setPosition(spot->d_bound.x(), spot->d_bound.y());
        }
        players[id]->updata();
        moveCell(players[id]);
    }

    // updata the state
    d_state_machine->hero = players[id];
};


// check the collision
inline
const sgds::ICollider* PlayerController::collisionWith(sgds::ICollider* self){
    sgdc::DynamicArray<sgds::ICollider*> check_list = d_grid->find_around(self);
    for (unsigned int i = 0; i < check_list.getLength(); i++)
    {
        if (self->doesCollide(check_list[i]->bounds()))
            return check_list[i];
    }
    return nullptr;
}

// check the state
inline
const mgc::State* PlayerController::checkstate(sgds::ICollider* self){
    sgdc::DynamicArray<mgc::State*> check_list = d_state_machine->states;
    for (unsigned int i = 0; i < check_list.getLength(); i++)
    {
        if (self->doesCollide(check_list[i]->bounds()))
            return check_list[i];
    }
    return nullptr;
}

// move from cell to cell
inline
void PlayerController::moveCell(sgda::Player* player){
    // check if the actor move to different cell; if did swith the cell
    int place = d_grid->getCellindex(player->d_bound);
    if (place != player->getCell()){
        d_grid->removeCollider(player, player->getCell());
        d_grid->addCollider(player, place);
    }
}

// set model 
inline
void PlayerController::setModel(int i){
    model = i;
}

// get model
inline
int PlayerController::getModel(){
    return model;
}

} // end of namespace
#endif