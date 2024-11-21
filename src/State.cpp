#include "State.h"
//constructor & destructor
State :: State(sf :: RenderWindow* window) {
    this -> window = window;
    this -> isEnd = false;
}
State :: ~State() {
    
}

//functions
sf :: RenderWindow* State :: getWindow() const{
    return this -> window;
}
const bool& State :: end() const{
    return this -> isEnd;
}
void State :: quit() {
    this -> isEnd = true;
    std :: cerr << "Game State End!" << std :: endl;
}


