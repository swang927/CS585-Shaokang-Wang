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
#include "src/game/controllers/red_guard_controller.h"
#include "src/game/controllers/blue_guard_controller.h"
#include "src/game/controllers/player_controller.h"
#include "src/game/controllers/maze.h"
#include "src/game/controllers/state.h"
#include "src/game/controllers/state_machine.h"
#include "src/game/actors/wall.h"
#include "src/game/actors/guard.h"
#include "src/game/actors/player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <stdio.h>

#define Num_Wall 400
#define Num_State 34
// set the frameCount and animation time
float frameCount = 0;
float holdCount = 0;
float elapseCount = 0;
clock_t animation_time, hold_time, game_time;
// enum the input types
enum Direction { Down, Left, Right, Up };
int source[2] = { 1, Down };
sgds::Scene* main_scene;
sgdr::Renderer render;
sgds::NxNSceneGraph static_grid;
sgda::Player player;
sgda::Guard red, blue;
sgda::Wall wall[Num_Wall];
mgc::State state[Num_State];
mgc::StateMachine state_machine;
mgc::RedGuardController seek;
mgc::BlueGuardController chase;
mgc::PlayerController play;
mgc::Maze maze;
sgdr::RenderableSprite tag, watch;
bool lose = false;
bool win = false;
bool stopwatch = false;
    
// switch between model 1 and 2
void switchModel(int model){
    if (model == 2){
        play.setModel(2);
        seek.setModel(2);
        chase.setModel(2);
        player.d_sprite.setTexture(render.getTexture("dpTexture"));
        red.d_sprite.setTexture(render.getTexture("drTexture"));
        blue.d_sprite.setTexture(render.getTexture("dbTexture"));
    }
    if (model == 1){
        play.setModel(1);
        seek.setModel(1);
        chase.setModel(1);
        player.d_sprite.setTexture(render.getTexture("pTexture"));
        red.d_sprite.setTexture(render.getTexture("rTexture"));
        blue.d_sprite.setTexture(render.getTexture("bTexture"));
    }
}

// load the texture
void loadTexture(){
    //==== load texture =================================//
    // load textures
    if (!render.loadTexture("pTexture", "image/player.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("bTexture", "image/blue_guard.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("rTexture", "image/red_guard.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("dpTexture", "image/player_1.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("dbTexture", "image/blue_guard_1.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("drTexture", "image/red_guard_1.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("wTexture", "image/Brick_Wall.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("sTexture", "image/ninja_weapon.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("loseTexture", "image/youLoss.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("winTexture", "image/youWin.png"))
        std::cout << "Error could not load player image" << std::endl;

    if (!render.loadTexture("timeTexture", "image/number_sheets.png"))
        std::cout << "Error could not load player image" << std::endl;
}

// inital all the data
void init(){
    // 1. Scene and Render:
    // create the main scene
    main_scene = &(sgds::Scene::inst());

    // create the render and set window 25*19
    render.setupWindow("My First Game", 800, 608); 

    // add the player actor, AI acotrs and static sprites to render
    render.addSprite(&(player.d_sprite));
    render.addSprite(&(red.d_sprite));
    render.addSprite(&(blue.d_sprite));
    for (int i = 0; i < Num_Wall; i++){
        render.addSprite(&(wall[i].d_sprite));
    }

    // scene add tickable and link render
    main_scene->setRenderer(&render);
    main_scene->addTickable(&sgdi::Input::inst());
    
    
    // 2. Texture:
    loadTexture();
    // set texture
    player.d_sprite.setTexture(render.getTexture("pTexture"));
    red.d_sprite.setTexture(render.getTexture("rTexture"));
    blue.d_sprite.setTexture(render.getTexture("bTexture"));
    for (int i = 0; i < Num_Wall; i++){
        wall[i].d_sprite.setTexture(render.getTexture("wTexture"));
    }
    watch.setTexture(render.getTexture("timeTexture"));
    // 3. Grid
    // init static grid
    sgds::NxNSceneGraph grid(800, 608, 4);
    static_grid = grid;


    // 4. Controller
    // init AI controller
    mgc::RedGuardController AI1(render.window(), &static_grid, &state_machine);
    seek = AI1;
    mgc::BlueGuardController AI2(render.window(), &static_grid, &state_machine);
    chase = AI2;
    // init player controller
    mgc::PlayerController Pl(render.window(), &static_grid, &state_machine);
    play = Pl;
    //init maze generator
    mgc::Maze M(render.window(), &static_grid);
    maze = M;

    // 5. Actor
    // link actor to controller=
    // add to control
    play.add_instance(&player);
    seek.add_instance(&red);
    chase.add_instance(&blue);
    // add to generator
    for (int i = 0; i < Num_Wall; i++){
        maze.add_instance(&wall[i]);
    }
    for (int i = 0; i < Num_State; i++){
        state_machine.add_instance(&state[i]);
    }
    // fill the grid
    static_grid.addCollider(&player);
    static_grid.addCollider(&red);
    static_grid.addCollider(&blue);
    for (int i = 0; i < Num_Wall; i++){
        static_grid.addCollider(&wall[i]);
    }
    

    // 6. inital all 
    // inital state
    maze.init();
    state_machine.init();
    play.init();
    seek.init();
    chase.init();
    tag.setPosition(160, 144);
    watch.setPosition(385, 310);
    animation_time = clock();
}

// reset the data
void reset(){
    player.setOn();
    red.setOn();
    blue.setOn();
    // inital state
    play.init();
    seek.init();
    chase.init();
    lose = false;
    win = false;
    player.d_sprite.setTexture(render.getTexture("pTexture"));
    red.d_sprite.setTexture(render.getTexture("rTexture"));
    blue.d_sprite.setTexture(render.getTexture("bTexture"));
    render.removeSprite(&tag);
    render.removeSprite(&watch);
    // rest game time
    elapseCount = 0;
    game_time = clock();
    stopwatch = false;
}



// show the final result: win / lose
void ShowResult(){
    if (lose)
        tag.setTexture(render.getTexture("loseTexture"));
    if (win)
        tag.setTexture(render.getTexture("winTexture"));
    if (!render.hasSprite(&tag))
        render.addSprite(&tag);
    // draw current scene
    render.draw();
    // hold for 0.5 second
    while (holdCount<0.5){
        hold_time = clock();
        holdCount += ((float)(clock() - hold_time)) / CLOCKS_PER_SEC;
    }
    holdCount = 0;
}

// show the countdown clock
void timeTrigger(){
    // get shift model with certain time
    elapseCount += ((float)(clock() - game_time)) / CLOCKS_PER_SEC;
    game_time = clock();
    if (play.getModel() == 1){
        if (30 - elapseCount <= 0){
            elapseCount = 0;
            switchModel(2);
        }
        if (30 - elapseCount < 10){
            if (stopwatch){
                watch.setTextureRect((29 - (int)elapseCount) * 35, 0, 35, 50);
            }
            else{
                if (!render.hasSprite(&watch))
                    render.addSprite(&watch);
                stopwatch = true;
            }

        }
    }
    if (play.getModel() == 2){
        if (10 - elapseCount <= 0){
            elapseCount = 0;
            switchModel(1);
        }
        if (10 - elapseCount < 10){
            if (stopwatch){
                watch.setTextureRect((9 - (int)elapseCount) * 35, 0, 35, 50);
            }
            else{
                if (!render.hasSprite(&watch))
                    render.addSprite(&watch);
                stopwatch = true;
            }

        }
    }
    
    
}

// get the keyboard input
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
	// use key board space key close game
	if (sgdi::Input::inst().isDown(sgdi::InputType::SPACE_KEY)){
		switchModel(2);
	}
}

// update the data 
void Update(){
    timeTrigger();
    // do AI move
    seek.update();
    chase.update();
    sgdi::Input::inst().preTick();
    // check the result in model 1
    if (player.isOff()){
        lose = true;
        ShowResult();
        reset();
    }
    // check the result in model 2
    if (red.isOff() && blue.isOff()){
        win = true;
        ShowResult();
        reset();
    }

}

// display the game
void Display(){
	// do animation by swith the image every 0.1s
	frameCount += ((float)(clock() - animation_time)) / CLOCKS_PER_SEC;
	animation_time = clock();
	if (frameCount > 0.1){
		frameCount = 0;
		source[0]++;
		if ((unsigned int)source[0] * 32 >= render.getTexture("pTexture").getSize().x)
			source[0] = 0;
	}
	// choose the right image form the texture
	player.d_sprite.setTextureRect(source[0] * 32, source[1] * 32, 32, 32);
	red.d_sprite.setTextureRect(source[0] * 32, red.direction() * 32, 32, 32);
	blue.d_sprite.setTextureRect(source[0] * 32, blue.direction() * 32, 32, 32);

	// draw current scene
	render.draw();
}

// main function
int main()
{
    std::cout << "Hello CS585, I am ready to fight\n";
    init();

    // give the start time
    game_time = clock();
    std::cout << "time : " << game_time << std::endl;
    
    // start the game loop
    while (render.isActive())
    {    
        Update();
        Display();
        Keyboard();
    }

    return 0;
};
