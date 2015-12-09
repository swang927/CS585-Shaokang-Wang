// blue_guard_controller.h
    
#ifndef INCLUDED_BLUE_GUARD_CONTROLLER
#define INCLUDED_BLUE_GUARD_CONTROLLER

#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "../../engine/rendering/renderable_sprite.h"
#include "../../engine/containers/dynamic_array.h"
#include "../actors/guard.h"
#include "../../engine/scene/nxn_scene_graph.h"
#include "state_machine.h"
#include "state.h"

namespace mgc
{
// AI controller for blue guard
class BlueGuardController{
  private:
    // save the moving vector
    sgdc::DynamicArray<sgda::Guard *> guards;
    sf::RenderWindow *d_window;
    // static grid
    sgds::NxNSceneGraph* d_grid;
    // state machine
    mgc::StateMachine* d_state_machine;
    sgdc::DynamicArray<State*> previous;
    sgdc::DynamicArray<State*> current;
    sgdc::DynamicArray<State*> next;
    // the model of the game
    int model;
    
    // flag for initialization
    bool has_init = false;
    unsigned int num = 0;

    // move actor on x axis
    void move_X(sgda::Guard* guard, int index);
    // move actor on y axis
    void move_Y(sgda::Guard* guard, int index);
    // updata current direction
    void updata_direction(sgda::Guard* guard, int i);
 public:
    // constructor
    BlueGuardController();
    // creat controller with relate window and grid
    BlueGuardController(sf::RenderWindow* window, sgds::NxNSceneGraph* grid, mgc::StateMachine* state_machine);
    // Operator overload
    const BlueGuardController& operator=(const BlueGuardController &other);
    // Deconstructor
    ~BlueGuardController();

    // add sprite
    void add_instance(sgda::Guard* guard);
    // remove sprite
    void remove_instance(sgda::Guard* guard);
    // initial data
    void init();
    // initial certain object data
    void init(sgda::Guard* guard);
    // updata function
    void update();
    // move from cell to cell
    void moveCell(sgda::Guard* guard);
    // check the collision
    const sgds::ICollider* collisionWith(sgds::ICollider* self);

    // set model 
    void setModel(int i);
    // get model
    int getModel();

};// end of class

// constructor
inline
BlueGuardController::BlueGuardController(){
}

// creat controller with relate window and grid
inline
BlueGuardController::BlueGuardController(sf::RenderWindow* window, sgds::NxNSceneGraph* grid, mgc::StateMachine* state_machine){
    d_window = window;
    d_grid = grid;
    d_state_machine = state_machine;
};

// Operator overload
inline
const BlueGuardController& BlueGuardController::operator = (const BlueGuardController &other){
    if (this != &other){
        this->d_window = other.d_window;
        this->d_grid = other.d_grid;
        this->guards = other.guards;
        this->d_state_machine = other.d_state_machine;
        this->has_init = other.has_init;
        this->num = other.num;
        this->previous = other.previous;
        this->current = other.current;
        this->next = other.next;
        this->model = other.model;
    }
    return *this;
}

// Deconstructor
inline
BlueGuardController::~BlueGuardController(){
}

// add new sprite to the list
inline
void BlueGuardController::add_instance(sgda::Guard * guard){
    assert(guard);
    if (has_init)
        init(guard);
    guards.push(guard);
    num++;
};

// remove a exist sprite from list
inline
void BlueGuardController::remove_instance(sgda::Guard * guard){
    assert(guard);
    guards.remove(guard);
    num--;
};

// initial certain object data
inline
void BlueGuardController::init(sgda::Guard* guard){
    // direction
    guard->dirction_x = 0.5;
    guard->dirction_y = 0;
    // speed 
    guard->speed = 0.5;
    float x = 0;
    float y = 0;
    // start position
    guard->d_sprite.setPosition(x, y);
    // update the bound
    guard->updata();
    // check if the actor move to different cell; if did swith the cell
    int place = d_grid->getCellindex(guard->d_bound);
    if (place != guard->getCell()){
        d_grid->removeCollider(guard, guard->getCell());
        d_grid->addCollider(guard, place);
    }
}

// inital the AI data: speed, direction and start point
inline
void BlueGuardController::init(){
    has_init = true;
    model = 1;
    previous.clean();
    current.clean();
    next.clean();
    float x, y;
    // go through all elements
    for (unsigned int i = 0; i < num; i++){
        current.push(d_state_machine->states[33]);
        previous.push(d_state_machine->states[33]);
        // start position
        x = current[i]->d_bound.x();
        y = current[i]->d_bound.y();
        guards[i]->d_sprite.setPosition(x, y);
        // direction
        next.push(d_state_machine->next_step(current[i]));
        guards[i]->dirction_x = 0;
        if (next[i]->d_bound.x() - current[i]->d_bound.x() > 0)
            guards[i]->dirction_x = 1;
        if (next[i]->d_bound.x() - current[i]->d_bound.x() < 0)
            guards[i]->dirction_x = -1;

        guards[i]->dirction_y = 0;
        if (next[i]->d_bound.y() - current[i]->d_bound.y() > 0)
            guards[i]->dirction_y = 1;
        if (next[i]->d_bound.y() - current[i]->d_bound.y() < 0)
            guards[i]->dirction_y = -1;

        // speed 
        guards[i]->speed = 0.5;
        // update the bound
        guards[i]->updata();
        // updata the state
        d_state_machine->blue = guards[i];
        // check if the actor move to different cell; if did swith the cell
        moveCell(guards[i]);
    }
};

inline
void BlueGuardController::update(){
    for (unsigned int i = 0; i < num; i++){
        if (guards[i]->isOff()){
            guards[i]->d_sprite.setPosition(0, 576);
            guards[i]->updata();
            moveCell(guards[i]);
        }
        else{
            if (guards[i]->d_bound.x() == next[i]->d_bound.x()
                && guards[i]->d_bound.y() == next[i]->d_bound.y())
            {
                // update the current state
                previous[i] = current[i];
                current[i] = next[i];
                // find the new next state
                sgds::RectangleBounds detect = d_state_machine->hero->d_bound;
                if (guards[i]->d_bound.x() - detect.x() < 300 &&
                    guards[i]->d_bound.y() - detect.y() < 300 && model == 1)
                    next[i] = d_state_machine->lookfor(current[i], previous[i]);
                else
                    next[i] = d_state_machine->next_step(current[i]);
            }
            // updata the direction
            updata_direction(guards[i], i);
            // move on x axis
            move_X(guards[i], i);
            // move on y axis
            move_Y(guards[i], i);
        }
    }
};

// updata current direction
inline
void BlueGuardController::updata_direction(sgda::Guard* guard, int i){
    //  x
    guard->dirction_x = 0;
    if (next[i]->d_bound.x() - current[i]->d_bound.x() > 0)
        guard->dirction_x = 1;
    if (next[i]->d_bound.x() - current[i]->d_bound.x() < 0)
        guard->dirction_x = -1;
    // y
    guard->dirction_y = 0;
    if (next[i]->d_bound.y() - current[i]->d_bound.y() > 0)
        guard->dirction_y = 1;
    if (next[i]->d_bound.y() - current[i]->d_bound.y() < 0)
        guard->dirction_y = -1;
}

// move actor on x axis
inline
void BlueGuardController::move_X(sgda::Guard* guard, int index){
    const sgds::ICollider* block;
    // move on x axis
    guard->d_sprite.move(guard->dirction_x * guard->speed, 0);
    guard->updata();
    moveCell(guard);
    // check collision with other object
    block = collisionWith(guard);
    // if collision happen, then make change to guard actor
    if (block){
        guard->d_sprite.move(-guard->dirction_x * guard->speed, 0);
        guard->updata();
        moveCell(guard);
        if (block == d_state_machine->hero){
            if (model == 1)
                d_state_machine->hero->setOff();
            else
                guard->setOff();
        }
        if (block == d_state_machine->red && next[index] != current[index]){
            previous[index] = next[index];
            next[index] = current[index];
            current[index] = previous[index];
        }
    }
}

// move actor on y axis
inline
void BlueGuardController::move_Y(sgda::Guard* guard, int index){
    const sgds::ICollider* block;
    // move on x axis
    guard->d_sprite.move(0, guard->dirction_y * guard->speed);
    guard->updata();
    moveCell(guard);
    // check collision with other object
    block = collisionWith(guard);
    // if collision happen, then make change to guard actor
    if (block){
        guard->d_sprite.move(0, -guard->dirction_y * guard->speed);
        guard->updata();
        moveCell(guard);
        if (block == d_state_machine->hero){
            if (model == 1)
                d_state_machine->hero->setOff();
            else
                guard->setOff();
        }
        if (block == d_state_machine->red && next[index] != current[index]){
            previous[index] = next[index];
            next[index] = current[index];
            current[index] = previous[index];

        }
    }
}

// check the collision
inline
const sgds::ICollider* BlueGuardController::collisionWith(sgds::ICollider* self){
    sgdc::DynamicArray<sgds::ICollider*> check_list = d_grid->find_around(self);
    for (unsigned int i = 0; i < check_list.getLength(); i++)
    {
        if (self->doesCollide(check_list[i]->bounds()))
            return check_list[i];
    }
    return nullptr;
}

// move from cell to cell
inline
void BlueGuardController::moveCell(sgda::Guard* guard){
    // check if the actor move to different cell; if did swith the cell
    int place = d_grid->getCellindex(guard->d_bound);
    if (place != guard->getCell()){
        d_grid->removeCollider(guard, guard->getCell());
        d_grid->addCollider(guard, place);
    }
}

// set model 
inline
void BlueGuardController::setModel(int i){
    model = i;
}

// get model
inline
int BlueGuardController::getModel(){
    return model;
}

} // end of namespace
#endif