// scene.h
               
#ifndef INCLUDED_SCENE
#define INCLUDED_SCENE

#include "../containers/dynamic_array.h"
#include "../memory/iallocator.h"
#include "itickable.h"
#include "../rendering/renderer.h"

namespace sgds
{
//This one manages the lifecycle of objects in the world and the dissemination of ticks
class Scene{
  private:
    // for tickable iterations.
    sgdc::DynamicArray<ITickable*> d_tickables;
    // for renderer 
    sgdr::Renderer* d_renderer;

    // CONSTRUCTORS
    // default constructor.
    Scene();
    // copy constructor.
    Scene(const Scene &) = delete;
    // move constructor.
    Scene(Scene &&) = delete;
    // deconstructor.
    ~Scene();

    // OPERATOR OVERLOADS
    // copy assignment.
    Scene& operator =(const Scene &) = delete;
    // move assignment.
    Scene& operator =(Scene &&) = delete;
    
  public:
    // ACCESSORS
    // the access point of a singleton class.
    static Scene& inst();

    // MEMBER FUNCTIONS
    // aka update
    void tick();
    // add tickable aka scene components.
    void addTickable(ITickable* tickable);
    // remove tickable aka scene components.
    void removeTickable(ITickable* tickable);
    // allocate renderer on stack, 
    // we are going to have the renderer be part of 
    // the scene as it will be needed by other elements.
    void setRenderer(sgdr::Renderer* renderer); 
    
};


// default constructor.
inline
Scene::Scene() : d_renderer(nullptr){
}



// deconstructor.
inline
Scene::~Scene(){
}



// ACCESSORS
inline
Scene& Scene::inst(){
    static Scene scene;
    return scene;
}



// aka update
inline
void Scene::tick(){
    for (unsigned int i = 0; i < d_tickables.getLength(); ++i){

    }
    if (d_renderer){
        d_renderer->draw();
    }
}



// add tickable aka scene components.
inline
void Scene::addTickable(ITickable* tickable)
{
    assert(tickable);
    d_tickables.push(tickable);
}



// remove tickable aka scene components.
inline
void Scene::removeTickable(ITickable* tickable)
{
    assert(tickable);
    d_tickables.remove(tickable);
}


// allocate renderer on stack
inline
void Scene::setRenderer(sgdr::Renderer* renderer){
    assert(renderer);
    d_renderer = renderer;
}

};  // end namespace sgds
#endif