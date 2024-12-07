#include "GameState.h"
//constructor & destructor
GameState :: GameState(sf :: RenderWindow* window, std :: stack<State*>* states, Resource* resource, const std :: string &map)
 : State(window, states, resource), map(resource, map), subtitle(resource) {
    subtitle.setFont("pixel.ttf");
    subtitle.setPosition({this -> getWindow() -> getSize().x / 2.f, this -> getWindow() -> getSize().y - 100.f});
    subtitle.display(L"需要一把钥匙, 按F键打开", 1000.f);
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
    subtitle.render(target);
}