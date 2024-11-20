#include "GameState.h"
//constructor & destructor
GameState :: GameState(sf :: RenderWindow* window) : state(window) {
    
}
GameState :: ~GameState() {

}

//functions 
void GameState :: updateKeybinds(const float& deltaTime) {
    this -> updateQuit();

}
void GameState :: update(const float &deltaTime) {
    this -> updateKeybinds(deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: A))
        std :: cerr << 'A' << std :: endl;
    else if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: S))
        std :: cerr << 'S' << std :: endl;
    else if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: D))
        std :: cerr << 'D' << std :: endl;
    else if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: W))
        std :: cerr << 'W' << std :: endl;
}
void GameState :: render(sf :: RenderTarget* target = nullptr) {

}
void GameState :: quit() {
    std :: cerr << "Game State End!" << std :: endl;
}