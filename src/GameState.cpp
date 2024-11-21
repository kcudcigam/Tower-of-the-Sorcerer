#include "GameState.h"
//constructor & destructor
GameState :: GameState(sf :: RenderWindow* window, std :: stack<State*>* states) : State(window, states) {
    
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
    this -> player.update(deltaTime);
}
void GameState :: render(sf :: RenderTarget* target) {
    if(target == nullptr) target = this -> getWindow();
    this -> player.render(target);
}