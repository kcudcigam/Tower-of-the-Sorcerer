#include "State.h"
extern Resource resource;
extern Subtitle subtitle;

//State
State :: State(sf :: RenderWindow* window, std :: stack<State*>* states) : window(window ), states(states), isEnd(false) {
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
        stateStack() -> push(new GameState(getWindow(), stateStack(), "prison1.json"));
}
void MenuState :: render(sf :: RenderTarget* target) {
    target -> draw(background);
}

//GameState
GameState :: GameState(sf :: RenderWindow* window, std :: stack<State*>* states, const std :: string &map) : State(window, states), map(map) {
    
}
GameState :: ~GameState() {

}
void GameState :: checkForQuit() {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Tab)) quit();
}
void GameState :: update(const float &deltaTime) {
    checkForQuit();
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: X)) {
        stateStack() -> push(new DictionaryState(getWindow(), stateStack(), map.getMonster())); return;
    }
    subtitle.update(deltaTime);
    map.update(deltaTime);
}
void GameState :: render(sf :: RenderTarget* target) {
    map.render(target);
    subtitle.render(target);
}

//DictionaryState
DictionaryState :: DictionaryState(sf :: RenderWindow* window, std :: stack<State*>* states, const std :: vector<Monster> &monsters)
: State(window, states), monsters(monsters), it(0), leftPress(false), rightPress(false) {
    assert(monsters.size());
    background.setSize(sf :: Vector2f (
        static_cast<float>(getWindow() -> getSize().x), 
        static_cast<float>(getWindow() -> getSize().y)
        )
    );
    background.setTexture(resource.getImg("dictionary-background.png"));
    sprite.setPosition({getWindow() -> getSize().x / 2.f, getWindow() -> getSize().y / 2.f});
    text.setFont(*resource.getFont("pixel.ttf"));
    text.setPosition({getWindow() -> getSize().x / 2.f - 100.f, getWindow() -> getSize().y / 2.f + 100.f});
}
DictionaryState :: ~DictionaryState() {

}

void DictionaryState :: update(const float& deltaTime) {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Z)) {
        stateStack() -> pop(); return;
    }
    if(!sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left) && leftPress)
        (it += monsters.size() - 1) %= monsters.size();
    if(!sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right) && rightPress)
        (it += 1) %= monsters.size();
    leftPress  = sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left);
    rightPress = sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right);
    monsters[it].getAnimation().play(&sprite, "idle", deltaTime, 4.f);
    text.setString(monsters[it].getName());
}
void DictionaryState :: render(sf :: RenderTarget* target) {
    target -> draw(background);
    target -> draw(sprite);
    target -> draw(text);
    monsters[it].getAttribute().render(target, {getWindow() -> getSize().x / 2.f - 100.f, getWindow() -> getSize().y / 2.f + 150.f}, {"health", "attack", "defence"}, "brown");
}