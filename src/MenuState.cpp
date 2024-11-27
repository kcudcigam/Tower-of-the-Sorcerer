#include "MenuState.h"
//constructor & destructor
MenuState :: MenuState(sf :: RenderWindow* window, std :: stack<State*>* states) : State(window, states) {
    //init background
    this -> background.setSize(sf :: Vector2f (
        static_cast<float>(this -> getWindow() -> getSize().x), 
        static_cast<float>(this -> getWindow() -> getSize().y)
        )
    );
    if(!this -> backgroundTexture.loadFromFile("../res/background.png"))
        throw("ERROR :: MenuState :: FAILED_TO_LOAD_BACKGROUND_TEXTURE");
    this -> background.setTexture(&this -> backgroundTexture);
    
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
    target -> draw(this -> background);
}