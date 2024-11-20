#include "State.h"
//constructor & destructor
State :: State(sf :: RenderWindow* window) {
    this -> window = window;
    this -> isQuit = false;
}
State :: ~State() {
    
}

//functions
void State :: updateQuit() {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape))
        this -> isQuit = true;
}
const bool& State :: checkQuit() const{
    return this -> isQuit;
}

