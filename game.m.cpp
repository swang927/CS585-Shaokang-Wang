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
#include "src/engine/scene/itickable.h"
#include "src/engine/scene/scene.h"
#include "src/engine/input/input.h"
#include "src/engine/rendering/renderable_sprite.h"
#include "src/engine/rendering/renderer.h"
#include "src/engine/scene/rectangle_bounds.h"
#include "src/engine/scene/icollider.h"
#include "src/engine/scene/nxn_scene_graph.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace sgdm;

int main()
{
	std::cout << "Hello CS585, I am ready to fight\n";
	
	// enum the input types
	enum Direction { Down, Left, Right, Up };
	int source[2] = {1, Down};
	// set the frameCount and game time
	float frameCount = 0;
	clock_t time;

	// create the render and set window
	sgdr::Renderer render;
	render.setupWindow("Hello", 800, 600);

	// create the player sprite and add to render
	sgdr::RenderableSprite player;
	render.addSprite(&player);

	// load texture and set it to player sprite 
	if (!render.loadTexture("pTexture","player.png"))
		std::cout << "Error could not load player image" << std::endl;
	player.setTexture(render.getTexture("pTexture"));
	time = clock();

	// start the game loop
	while (render.isActive())
	{
		render.draw();
		
		sgdi::Input::inst().preTick();
		// use key board up to control player move up
		if (sgdi::Input::inst().isDown(sgdi::InputType::UP_KEY))
		{
			source[1] = Up;
			if (player.getPositionY() > 0)
				player.move(0, -0.2);
		}

		// use key board down to control player move down
		if (sgdi::Input::inst().isDown(sgdi::InputType::DOWN_KEY))
		{
			source[1] = Down;
			if (player.getPositionY() < render.window_height() -32)
				player.move(0, 0.2);
		}

		// use key board left to control player move left
		if (sgdi::Input::inst().isDown(sgdi::InputType::LEFT_KEY))
		{
			source[1] = Left;
			if (player.getPositionX() > 0)
				player.move(-0.2, 0);
		}

		// use key board right to control player move right
		if (sgdi::Input::inst().isDown(sgdi::InputType::RIGHT_KEY))
		{
			source[1] = Right;
			if (player.getPositionX() < render.window_width() - 32)
				player.move(0.2, 0);
		}

		// press entern key to close the window
		if (sgdi::Input::inst().wasPressed(sgdi::InputType::RETURN_KEY))
		{
			render.closewindow();
		}

		// do animation by swith the image every 0.1s
		frameCount += ((float)(clock() - time))/CLOCKS_PER_SEC;
		time = clock();
		if (frameCount > 0.1){
			frameCount = 0;
			source[0]++;
			if (source[0] * 32 >= render.getTexture("pTexture").getSize().x)
				source[0] = 0;
		}

		// choose the right image form the texture
		player.setTextureRect(source[0] * 32, source[1] * 32, 32, 32);
	}

	return 0;
};
