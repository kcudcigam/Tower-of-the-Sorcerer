#include "GameState.h"
//constructor & destructor
GameState :: GameState(sf :: RenderWindow* window, std :: stack<State*>* states, Resource* resource, const std :: string &map)
 : State(window, states, resource), map(resource, map) {
    
}
GameState :: ~GameState() {

}

//functions 
void GameState :: checkForQuit() {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Tab))
        this -> quit();
}
void GameState :: update(const float &deltaTime) {
    this -> checkForQuit();
    this -> map.update(deltaTime);
}
void GameState :: render(sf :: RenderTarget* target) {
    if(target == nullptr) target = this -> getWindow();
    this -> map.render(target);
}