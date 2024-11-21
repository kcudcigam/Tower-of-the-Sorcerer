#include "MenuState.h"
//constructor & destructor
MenuState :: MenuState(sf :: RenderWindow* window, std :: stack<State*>* states) : State(window, states) {
    this -> shape.setSize(sf :: Vector2f(50.f, 50.f));
    this -> shape.setFillColor(sf :: Color :: Red);
}
MenuState :: ~MenuState() {

}

//functions 
void MenuState :: checkForQuit() {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape))
        this -> quit();
}
void MenuState :: update(const float &deltaTime) {
    this -> checkForQuit();
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Enter))
        this -> stateStack() -> push(new GameState(this -> getWindow(), this -> stateStack()));
}
void MenuState :: render(sf :: RenderTarget* target) {
    if(target == nullptr) target = this -> getWindow();
    target -> draw(this -> shape);
}