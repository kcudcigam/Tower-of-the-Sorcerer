#include "GameState.h"
//constructor & destructor
GameState :: GameState(sf :: RenderWindow* window) : State(window) {
    
}
GameState :: ~GameState() {

}

//functions 
void GameState :: checkForQuit() {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape))
        this -> quit();
}
void GameState :: update(const float &deltaTime) {
    this -> checkForQuit();
    this -> player.update(deltaTime);
}
void GameState :: render() {
    this -> player.render(this -> getWindow());
}