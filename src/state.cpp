#include "state.h"
//constructor & destructor
state :: state(sf :: RenderWindow* window) {
    this -> window = window;
    this -> isQuit = false;
}
state :: ~state() {
    
}

//functions
void state :: updateQuit() {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape))
        this -> isQuit = true;
}
const bool& state :: checkQuit() const{
    return this -> isQuit;
}

