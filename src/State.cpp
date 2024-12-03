#include "State.h"
//constructor & destructor
State :: State(sf :: RenderWindow* window, std :: stack<State*>* states, Resource* resource) : resource(resource) {
    this -> window = window;
    this -> states = states;
    this -> isEnd = false;
}
State :: ~State() {
    
}

//functions
sf :: RenderWindow* State :: getWindow() const {
    return this -> window;
}
std :: stack<State*>* State :: stateStack() const {
    return this -> states;
}
const bool& State :: end() const{
    return this -> isEnd;
}
Resource* State :: getResource() const {
    return this -> resource;
}
void State :: quit() {
    std :: cerr << "Game State End!" << ' ' << (this -> isEnd) << std :: endl;
    this -> isEnd = true;
}


