#include "State.h"
extern Resource resource;
extern Subtitle subtitle;

//State
State :: State(sf :: RenderWindow* window, std :: stack<State*>* states) : window(window), states(states), isEnd(false) {
}
State :: ~State() {
    
}
sf :: RenderWindow* State :: getWindow() const {
    return window;
}
std :: stack<State*>* State :: stateStack() const {
    return states;
}
const bool& State :: end() const{
    return isEnd;
}
void State :: quit() {
    isEnd = true;
}

//MenuState
MenuState :: MenuState(sf :: RenderWindow* window, std :: stack<State*>* states) : State(window, states) {
    //init background
    background.setSize(sf :: Vector2f (
        static_cast<float>(getWindow() -> getSize().x), 
        static_cast<float>(getWindow() -> getSize().y)
        )
    );
    background.setTexture(resource.getImg("bg.png"));
}
MenuState :: ~MenuState() {

}
void MenuState :: checkForQuit() {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape)) quit();
}
void MenuState :: update(const float &deltaTime) {
    checkForQuit();
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Enter))
        stateStack() -> push(new GameState(getWindow(), stateStack(), "prison.json"));
}
void MenuState :: render(sf :: RenderTarget* target) {
    target -> draw(background);
}

//GameState
GameState :: GameState(sf :: RenderWindow* window, std :: stack<State*>* states, const std :: string &map) : State(window, states), map(map) {
    subtitle.setFont("pixel.ttf");
    subtitle.setPosition({getWindow() -> getSize().x / 2.f, getWindow() -> getSize().y - 100.f});
    subtitle.display(L"需要一把钥匙, 按F键打开", 1000.f);
}
GameState :: ~GameState() {

}
void GameState :: checkForQuit() {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Tab)) quit();
}
void GameState :: update(const float &deltaTime) {
    checkForQuit();
    map.update(deltaTime);
}
void GameState :: render(sf :: RenderTarget* target) {
    map.render(target);
    subtitle.render(target);
}