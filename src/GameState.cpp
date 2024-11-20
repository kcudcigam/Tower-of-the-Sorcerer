#include "GameState.h"
//constructor & destructor
GameState :: GameState(sf :: RenderWindow* window) : State(window) {
    
}
GameState :: ~GameState() {

}

//functions 
void GameState :: updateKeybinds(const float& deltaTime) {
    this -> updateQuit();

}
void GameState :: update(const float &deltaTime) {
    this -> updateKeybinds(deltaTime);
    this -> player.update(deltaTime);
}
void GameState :: render(sf :: RenderTarget* target) {
    this -> player.render(this -> window);
}
void GameState :: quit() {
    std :: cerr << "Game State End!" << std :: endl;
}