// maze.h
    
#ifndef INCLUDED_MAZE
#define INCLUDED_MAZE

#include "../../engine/rendering/renderable_sprite.h"
#include "../../engine/containers/dynamic_array.h"
#include "../actors/wall.h"
#include "../../engine/scene/nxn_scene_graph.h"

namespace mgc
{
// The Maze generate the maze
class Maze{
  private:
    // save all sprites, I do this list in case in the future
    // there are multiply sprites can use this contoller
    sgdc::DynamicArray<sgda::Wall *> walls;
    sf::RenderWindow *d_window;
    unsigned int num = 0;
    sgds::NxNSceneGraph* d_grid;

  public:
    // constructor
    Maze();
    // creat controller with relate window and grid 
    Maze(sf::RenderWindow* window, sgds::NxNSceneGraph* grid);
    // Operator overload
    const Maze& operator=(const Maze &other);
    // Deconstructor
    ~Maze();

    // initial data
    void init();
    // add sprite
    void add_instance(sgda::Wall*  wall);
    // remove sprite
    void remove_instance(sgda::Wall* wall);

};// end of class


// constructor
inline
Maze::Maze(){
}

// creat controller with relate window and grid 
inline
Maze::Maze(sf::RenderWindow* window, sgds::NxNSceneGraph* grid){
    d_window = window;
    d_grid = grid;
};

// Operator overload
inline
const Maze& Maze::operator = (const Maze &other){
    if (this != &other){
        this->d_window = other.d_window;
        this->d_grid = other.d_grid;
        this->walls = other.walls;
        this->num = other.num;
    }
    return *this;
}

// Deconstructor
inline
Maze::~Maze(){
}

// init the position of all walls hard code hear
inline
void Maze::init(){
    unsigned int i;
    float x, y;
    // build the maze
    for (i = 0; i < num; i++){
        // hard code generate the outside bound
        if (i < 25){
            x = (float)i * 32;
            y = 0;
        }
        else if (i < 50){
            x = (float)(i-25) * 32;
            y = (float)18 * 32;
        }
        else if (i < 68){
            x = 0;
            y = (float)(i-50) * 32;
        }
        else if (i < 86){
            x = (float)24 * 32;
            y = (float)(i-68) * 32;
        }
        // build inside (hard code)
        //-----------------------//
        else if (i < 95){
            x = (float)(i - 86+2) * 32;
            y = (float)2 * 32;
        }
        else if (i < 104){
            x = (float)(i - 95 + 2) * 32;
            y = (float)4 * 32;
        }
        else if (i == 104){
            x = (float)2 * 32;
            y = (float)3 * 32;
        }
        else if (i == 105){
            x = (float)10 * 32;
            y = (float)3 * 32;
        }
        //-----------------------//
        else if (i < 111){
            x = (float)12 * 32;
            y = (float)(i-105) * 32;
        }
        //-----------------------//
        else if (i < 120){
            x = (float)(i - 111 + 14) * 32;
            y = (float)2 * 32;
        }
        else if (i < 129){
            x = (float)(i - 120 + 14) * 32;
            y = (float)4 * 32;
        }
        else if (i == 129){
            x = (float)14 * 32;
            y = (float)3 * 32;
        }
        else if (i == 130){
            x = (float)22 * 32;
            y = (float)3 * 32;
        }
        //-----------------------//
        else if (i < 137){
            x = (float)(i-131+2) * 32;
            y = (float)6 * 32;
        }
        else if (i < 144){
            x = (float)(i - 137 + 9) * 32;
            y = (float)6 * 32;
        }
        else if (i < 150){
            x = (float)(i - 144 + 17) * 32;
            y = (float)6 * 32;
        }
        //-----------------------//
        else if (i < 156){
            x = (float)(i - 150 + 1) * 32;
            y = (float)8 * 32;
        }
        else if (i < 162){
            x = (float)(i - 156 + 1) * 32;
            y = (float)12 * 32;
        }
        else if (i < 165){
            x = (float)6 * 32;
            y = (float)(i-162+9)* 32;
        }
        //-----------------------//
        else if (i < 174){
            x = (float)(i - 165 + 8) * 32;
            y = (float)8 * 32;
        }
        else if (i < 183){
            x = (float)(i - 174 + 8) * 32;
            y = (float)12 * 32;
        }
        else if (i < 186){
            x = (float)8 * 32;
            y = (float)(i - 183 + 9) * 32;
        }
        else if (i < 189){
            x = (float)16 * 32;
            y = (float)(i - 186 + 9) * 32;
        }
        ////-----------------------//
        else if (i < 195){
            x = (float)(i - 189 + 18) * 32;
            y = (float)8 * 32;
        }
        else if (i < 201){
            x = (float)(i - 195 + 18) * 32;
            y = (float)12 * 32;
        }
        else if (i < 204){
            x = (float)18 * 32;
            y = (float)(i - 201 + 9) * 32;
        }
        ////-----------------------//
        else if (i < 214){
            x = (float)(i - 204 + 2) * 32;
            y = (float)14 * 32;
        }
        else if (i < 224){
            x = (float)(i - 214 + 13) * 32;
            y = (float)14 * 32;
        }
        else if (i < 229){
            x = (float)(i - 224 + 1) * 32;
            y = (float)16 * 32;
        }
        //-----------------------//
        else if (i < 231){
            x = (float)7 * 32;
            y = (float)(i - 229 + 15) * 32;
        }
        //-----------------------//
        else if (i < 233){
            x = (float)9 * 32;
            y = (float)(i - 231 + 16) * 32;
        }
        else if (i < 235){
            x = (float)15 * 32;
            y = (float)(i - 233 + 16) * 32;
        }
        else if (i < 242){
            x = (float)(i - 235 + 9) * 32;
            y = (float) 16* 32;
        }
        //-----------------------//
        else if (i < 244){
            x = (float)17 * 32;
            y = (float)(i - 242 + 15) * 32;
        }
        //-----------------------//
        else if (i < 249){
            x = (float)(i - 244 + 19) * 32;
            y = (float) 16* 32;
        }
        //-----------------------//
    walls[i]->d_sprite.setPosition(x, y);
    // update the bound
    walls[i]->updata();

    int place = d_grid->getCellindex(walls[i]->d_bound);
    if (place != walls[i]->getCell()){
        d_grid->removeCollider(walls[i], walls[i]->getCell());
        d_grid->addCollider(walls[i], place);
        }
    }
};


// add new sprite to the list
inline
void Maze::add_instance(sgda::Wall*  wall){
    assert(wall);
    walls.push(wall);
    num++;
};

// remove a exist sprite from list
inline
void Maze::remove_instance(sgda::Wall*  wall){
    assert(wall);
    walls.remove(wall);
    num--;
};


} // end of namespace
#endif