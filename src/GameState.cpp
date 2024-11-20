#include "GameState.h"
GameState :: GameState(sf :: RenderWindow* window) : state(window) {
    
}
GameState :: ~GameState() {

}
void GameState :: update(const float &deltaTime) {
    std :: cerr << deltaTime << std :: endl;
}
void GameState :: render(sf :: RenderTarget* target = nullptr) {

}
void GameState :: end() {

}