#include "MenuState.h"
//constructor & destructor
MenuState :: MenuState(sf :: RenderWindow* window, std :: stack<State*>* states, Resource* resource) : State(window, states, resource), subtitle(resource) {
    //init background
    this -> background.setSize(sf :: Vector2f (
        static_cast<float>(this -> getWindow() -> getSize().x), 
        static_cast<float>(this -> getWindow() -> getSize().y)
        )
    );
    this -> background.setTexture(this -> getResource() -> getImg("bg.png"));
    subtitle.setFont("pixel.ttf");
    subtitle.setPosition({this -> getWindow() -> getSize().x / 2.f, this -> getWindow() -> getSize().y / 2.f});
    subtitle.display(L"需要一把钥匙, 按F键打开", 100000.f); 
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
        this -> stateStack() -> push(new GameState(this -> getWindow(), this -> stateStack(), this -> getResource(), "prison.json"));
    subtitle.update(deltaTime);
}
void MenuState :: render(sf :: RenderTarget* target) {
    if(target == nullptr) target = this -> getWindow();
    target -> draw(this -> background);
    subtitle.render(target);
}