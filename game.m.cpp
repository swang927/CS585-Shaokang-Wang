//  game.m.cpp
//  Author: Shaokang Wang
    
#include <iostream>
#include <time.h>
#include "src/engine/memory/counting_allocator.h"
#include "src/engine/memory/default_allocator.h"
#include "src/engine/memory/iallocator.h"
#include "src/engine/memory/stack_guard.h"

#include "src/engine/containers/dynamic_array.h"
#include "src/engine/containers/map.h"

#include "src/engine/data/json_parser.h"
#include "src/engine/data/json_entity.h"

#include "src/engine/input/input.h"

#include "src/engine/rendering/renderable_sprite.h"
#include "src/engine/rendering/renderer.h"

#include "src/engine/scene/itickable.h"
#include "src/engine/scene/scene.h"
#include "src/engine/scene/rectangle_bounds.h"
#include "src/engine/scene/icollider.h"
#include "src/engine/scene/nxn_scene_graph.h"

#include "src/engine/events/event_bus.h"
#include "src/engine/events/event_dispatcher.h"
#include "src/engine/events/ievent.h"

#include "src/game/controllers/move_to_controller.h"
#include "src/game/controllers/player_controller.h"

#include "src/game/actors/weapon.h"
#include "src/game/actors/player.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <vector>

using namespace sgdm;

// set the frameCount and animation time
float frameCount = 0;
clock_t animation_time;
// enum the input types
enum Direction { Down, Left, Right, Up };
int source[2] = { 1, Down };
sgds::Scene* main_scene;
sgdr::Renderer render;
sgds::NxNSceneGraph static_grid;
sgda::Player player;
sgda::Weapon shuriken1, shuriken2;
mgc::MoveToController fly;
mgc::PlayerController play;

void init(){
	//==== inital scene and render=======================//
	// create the main scene
	main_scene = &(sgds::Scene::inst());

	// create the render and set window
	render.setupWindow("My First Game", 800, 600);
	// create the player actor; add to render
	render.addSprite(&(player.d_sprite));
	// create the AI acotr; add to render 
	render.addSprite(&(shuriken1.d_sprite));
	render.addSprite(&(shuriken2.d_sprite));
	// scene add tickable
	main_scene->setRenderer(&render);
	main_scene->addTickable(&sgdi::Input::inst());
	//==================================================//



	//==== load texture =================================//
	// load texture and set it to player sprite 
	if (!render.loadTexture("pTexture", "player.png"))
		std::cout << "Error could not load player image" << std::endl;
	player.d_sprite.setTexture(render.getTexture("pTexture"));

	// load texture and set it to shuriken sprite 
	if (!render.loadTexture("aTexture", "ninja_weapon.png"))
		std::cout << "Error could not load player image" << std::endl;
	shuriken1.d_sprite.setTexture(render.getTexture("aTexture"));
	shuriken2.d_sprite.setTexture(render.getTexture("aTexture"));
	//==================================================//



	//=init static grid=================================//
	sgds::NxNSceneGraph grid(800, 600, 4);
	static_grid = grid;
	//==================================================//


	//== init AI controller============================//
	mgc::MoveToController AI(render.window(), &static_grid);
	fly = AI;
	//==================================================//


	//== player controller==============================//
	mgc::PlayerController Pl(render.window(), &static_grid);
	play = Pl;
	//==================================================//



	//==link actor to controller=======================//
	// add to control
	play.add_instance(&player);
	fly.add_instance(&shuriken1);
	fly.add_instance(&shuriken2);
	//==================================================//


	//== fill the grid=================================//
	static_grid.addCollider(&player);
	static_grid.addCollider(&shuriken1);
	static_grid.addCollider(&shuriken2);
	//=================================================//

	// inital state
	fly.init();
}

void Keyboard(){
	// use key board up to control player move up
	if (sgdi::Input::inst().isDown(sgdi::InputType::UP_KEY)){
		source[1] = Up;
		play.move(0, 0, -0.5);
	}
	// use key board down to control player move down
	if (sgdi::Input::inst().isDown(sgdi::InputType::DOWN_KEY)){
		source[1] = Down;
		play.move(0, 0, 0.5);
	}
	// use key board left to control player move left
	if (sgdi::Input::inst().isDown(sgdi::InputType::LEFT_KEY)){
		source[1] = Left;
		play.move(0, -0.5, 0);
	}
	// use key board right to control player move right
	if (sgdi::Input::inst().isDown(sgdi::InputType::RIGHT_KEY)){
		source[1] = Right;
		play.move(0, 0.5, 0);
	}
	// use key board return key close game
	if (sgdi::Input::inst().isDown(sgdi::InputType::RETURN_KEY)){
		render.closewindow();
	}
}

void Display(){
	// do animation by swith the image every 0.1s
	frameCount += ((float)(clock() - animation_time)) / 1000;
	animation_time = clock();
	if (frameCount > 0.1){
		frameCount = 0;
		source[0]++;
		if ((unsigned int)source[0] * 32 >= render.getTexture("pTexture").getSize().x)
			source[0] = 0;
	}

	// choose the right image form the texture
	player.d_sprite.setTextureRect(source[0] * 32, source[1] * 32, 32, 32);

	// draw current scene
	render.draw();
}

void Updata(){
	// do AI move
	fly.update();
	sgdi::Input::inst().preTick();	
}

int main()
{
    std::cout << "Hello CS585, I am ready to fight\n";
	
	init();

	// give the start time
    animation_time = clock();	
    // start the game loop
    while (render.isActive())
    {	
       	
		Updata();
		Keyboard();
		Display();
    }

    return 0;
};
