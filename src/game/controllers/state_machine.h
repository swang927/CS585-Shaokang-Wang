// state_machine.h
    
#ifndef INCLUDED_STATE_MACHINE
#define INCLUDED_STATE_MACHINE

#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../engine/rendering/renderable_sprite.h"
#include "../../engine/containers/dynamic_array.h"
#include "state.h"
#include "../../engine/scene/nxn_scene_graph.h"
#include "../actors/player.h"
#include "../actors/guard.h"

namespace mgc
{
// State machine to save all the states and update them
class StateMachine{
  public:
	// save all stats
	sgdc::DynamicArray<State*> states;
	sgda::Player* hero;
	sgda::Guard* red;
	sgda::Guard* blue;
	unsigned int num = 0;


	// constructor
	StateMachine();
	// Operator overload
	const StateMachine& operator=(const StateMachine &other);
	// Deconstructor
	~StateMachine();

	// initial data
	void init();
	// inital the position
	void set_position();
	// set realtion among states
	void set_relation();
	// add sprite
	void add_instance(State*  state);
	// remove sprite
	void remove_instance(State* state);

	// set the next step
	State* next_step(State* state);
	// find the best chose to chase player
	State* lookfor(State* state, State* previous);

};// end of class


// constructor
inline
StateMachine::StateMachine(){
}

// Operator overload
inline
const StateMachine& StateMachine::operator = (const StateMachine &other){
	if (this != &other){
		this->states = other.states;
		this->num = other.num;
	}
	return *this;
}

// Deconstructor
inline
StateMachine::~StateMachine(){
}

// init the position of all states hard code hear
inline
void StateMachine::init(){
	set_position();
	set_relation();
};

// inital the position
inline
void StateMachine::set_position(){
	unsigned int i;
	float x, y;
	// build the maze
	for (i = 0; i < num; i++){
		switch (i){
		case 0:
			x = 32; y = 32; break;
		case 1:
			x = 11 * 32; y = 32; break;
		case 2:
			x = 13 * 32; y = 32; break;
		case 3:
			x = 23 * 32; y = 32; break;
		case 4:
			x = 32;	y = 5 * 32; break;
		case 5:
			x = 8 * 32;	y = 5 * 32;	break;
		case 6:
			x = 11 * 32; y = 5 * 32; break;
		case 7:
			x = 13 * 32; y = 5 * 32; break;
		case 8:
			x = 16 * 32; y = 5 * 32; break;
		case 9:
			x = 23 * 32; y = 5 * 32; break;
		case 10:
			x = 32;	y = 7 * 32;	break;
		case 11:
			x = 7 * 32;	y = 7 * 32;	break;
		case 12:
			x = 8 * 32;	y = 7 * 32;	break;
		case 13:
			x = 16 * 32; y = 7 * 32; break;
		case 14:
			x = 17 * 32; y = 7 * 32; break;
		case 15:
			x = 23 * 32; y = 7 * 32; break;
		case 16:
			x = 32; y = 13 * 32; break;
		case 17:
			x = 7 * 32; y = 13 * 32; break;
		case 18:
			x = 12 * 32; y = 13 * 32; break;
		case 19:
			x = 17 * 32; y = 13 * 32; break;
		case 20:
			x = 23 * 32; y = 13 * 32; break;
		case 21:
			x = 32; y = 15 * 32; break;
		case 22:
			x = 6 * 32; y = 15 * 32; break;
		case 23:
			x = 8 * 32; y = 15 * 32; break;
		case 24:
			x = 12 * 32; y = 15 * 32; break;
		case 25:
			x = 16 * 32; y = 15 * 32; break;
		case 26:
			x = 18 * 32; y = 15 * 32; break;
		case 27:
			x = 23 * 32; y = 15 * 32; break;
		case 28:
			x = 32; y = 17 * 32; break;
		case 29:
			x = 6 * 32; y = 17 * 32; break;
		case 30:
			x = 8 * 32; y = 17 * 32; break;
		case 31:
			x = 16 * 32; y = 17 * 32; break;
		case 32:
			x = 18 * 32; y = 17 * 32; break;
		case 33:
			x = 23 * 32; y = 17 * 32; break;
		}
		states[i]->d_sprite.setPosition((float)x, (float)y);
		// update the bound
		states[i]->updata();
	}
}

// set realtion among states
inline
void StateMachine::set_relation(){
	// build the link
	// state 0
	states[0]->right = states[1]; 
	states[0]->down = states[4];
	// state 1
	states[1]->left = states[0];
	states[1]->down = states[6];
	// state 2
	states[2]->right = states[3];
	states[2]->down = states[7];
	// state 3
	states[3]->left = states[2];
	states[3]->down = states[9];
	// state 4
	states[4]->up = states[0];
	states[4]->right = states[5];
	states[4]->down = states[10];
	// state 5
	states[5]->left = states[4];
	states[5]->right = states[6];
	states[5]->down = states[12];
	// state 6
	states[6]->up = states[1];
	states[6]->left = states[5];
	// state 7
	states[7]->up = states[2];
	states[7]->right = states[8];
	// state 8
	states[8]->left = states[7];
	states[8]->right = states[9];
	states[8]->down = states[13];
	// state 9
	states[9]->up = states[3];
	states[9]->left = states[8];
	states[9]->down = states[15];
	// state 10
	states[10]->up = states[4];
	states[10]->right = states[11];
	// state 11
	states[11]->left = states[10];
	states[11]->right = states[12];
	states[11]->down = states[17];
	// state 12
	states[12]->left = states[11];
	states[12]->right = states[13];
	states[12]->up = states[5];
	// state 13
	states[13]->left = states[12];
	states[13]->right = states[14];
	states[13]->up = states[8];
	// state 14
	states[14]->left = states[13];
	states[14]->right = states[15];
	states[14]->down = states[19];
	// state 15
	states[15]->left = states[14];
	states[15]->up = states[9];
	// state 16
	states[16]->right = states[17];
	states[16]->down = states[21];
	// state 17
	states[17]->left = states[16];
	states[17]->right = states[18];
	states[17]->up = states[11];
	// state 18
	states[18]->left = states[17];
	states[18]->right = states[19];
	states[18]->down = states[24];
	// state 19
	states[19]->left = states[18];
	states[19]->right = states[20];
	states[19]->up = states[14];
	// state 20
	states[20]->left = states[19];
	states[20]->down = states[27];
	// state 21
	states[21]->up = states[16];
	states[21]->right = states[22];
	// state 22
	states[22]->right = states[21];
	states[22]->down = states[29];
	// state 23
	states[23]->right = states[24];
	states[23]->down = states[30];
	// state 24
	states[24]->left = states[23];
	states[24]->right = states[25];
	states[24]->up = states[18];
	// state 25
	states[25]->left = states[24];
	states[25]->down = states[31];
	// state 26
	states[26]->right = states[27];
	states[26]->down = states[32];
	// state 27
	states[27]->up = states[20];
	states[27]->left = states[26];
	// state 28
	states[28]->right = states[29];
	// state 29
	states[29]->left = states[28];
	states[29]->right = states[30];
	states[29]->up = states[22];
	// state 30
	states[30]->left = states[29];
	states[30]->up = states[23];
	// state 31
	states[31]->right = states[32];
	states[31]->up = states[25];
	// state 32
	states[32]->left = states[31];
	states[32]->right = states[33];
	states[32]->up = states[26];
	// state 33
	states[33]->left = states[32];
}


// add new sprite to the list
inline
void StateMachine::add_instance(mgc::State*  state){
	assert(state);
	states.push(state);
	num++;
};

// remove a exist sprite from list
inline
void StateMachine::remove_instance(mgc::State*  state){
	assert(state);
	states.remove(state);
	num--;
};


// set the next step
inline
State* StateMachine::next_step(State* state){
	sgdc::DynamicArray<State*> next = state->reachable();
	// random choose one avalible state
	int target  = rand() % next.getLength();
	return next[target];
}

// find the best chose to chase player
inline
State* StateMachine::lookfor(State* state, State* previous){
	sgdc::DynamicArray<State*> next = state->reachable();
	// find the shortest distance as chose
	State* best = NULL;
	float distance = -1;
	float dx, dy;
	for (unsigned int i = 0; i < next.getLength(); i++){
		dx = hero->d_bound.x() - next[i]->d_bound.x();
		dy = hero->d_bound.y() - next[i]->d_bound.y();
		// don't want to go back
		if (next[i] != previous){
			// find the short distance to player
			if ((dx*dx + dy*dy) < distance || distance < 0){
				distance = dx*dx + dy*dy;
				best = next[i];
			}
		}	
	}
	return best;
}

} // end of namespace
#endif
