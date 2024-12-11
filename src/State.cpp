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
        stateStack() -> push(new GameState(getWindow(), stateStack(), "prison.json", Attribute(100, 50, 5, 0)));
}
void MenuState :: render(sf :: RenderTarget* target) {
    target -> draw(background);
}

//GameState
GameState :: GameState(sf :: RenderWindow* window, std :: stack<State*>* states, const std :: string &map, const Attribute &attribute) : State(window, states), map(map, attribute) {
    
}
GameState :: ~GameState() {

}
void GameState :: checkForQuit() {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Tab)) quit();
}
void GameState :: update(const float &deltaTime) {
    checkForQuit();
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: X)) {
        stateStack() -> push(new DictionaryState(getWindow(), stateStack(), map.getMonsterList())); return;
    }
    subtitle.update(deltaTime);
    map.update(deltaTime);
    if(map.PlayerReference().getBattle() != "") {
        stateStack() -> push(new BattleState(getWindow(), stateStack(), map.PlayerReference(), map.MonsterReference(map.PlayerReference().getBattle())));
        map.PlayerReference().setBattle(""); return;
    }
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
    monsters[it].animationSetReference().play(&sprite, "idle", deltaTime, 4.f);
    text.setString(monsters[it].getName());
}
void DictionaryState :: render(sf :: RenderTarget* target) {
    target -> draw(background);
    target -> draw(sprite);
    target -> draw(text);
    monsters[it].attributeReference().render(target, {getWindow() -> getSize().x / 2.f - 100.f, getWindow() -> getSize().y / 2.f + 150.f}, {"max_health", "attack", "defence"}, "brown");
}

//BattleState
void BattleState :: Object :: update(const float &deltaTime) {
    animation.play(&sprite, "idle", deltaTime);
}
void BattleState :: Object :: render(sf :: RenderTarget* target) {
    sf :: Text text; text.setFont(*resource.getFont("pixel.ttf"));
    const sf :: Vector2f &position = sprite.getPosition();
    text.setPosition(position + sf :: Vector2f(0.f, 100.f)); text.setString(name);
    target -> draw(sprite);
    target -> draw(text);
    attribute.render(target, position + sf :: Vector2f(-50.f, 200.f), {"health", "attack", "defence"}, color);
}

const float battleDuration = 2.f;
BattleState :: BattleState(sf :: RenderWindow* window, std :: stack<State*>* states, Player &player, Monster &monster)
 : State(window, states), player(player), turn(false), timer(0.f) {
    background.setSize(sf :: Vector2f (
        static_cast<float>(getWindow() -> getSize().x), 
        static_cast<float>(getWindow() -> getSize().y)
        )
    );
    background.setTexture(resource.getImg("dictionary-background.png"));
    object[0].sprite.setPosition(200.f, 400.f);
    object[1].sprite.setPosition(600.f, 400.f);
    object[0].attribute = player.attributeReference();
    object[1].attribute = monster.attributeReference();
    object[0].color = "green", object[1].color = "brown";
    object[0].name = L"勇士"; object[1].name = monster.getName();
    object[0].turns = object[1].turns = 0;
    for(const std :: string &action : {"idle", "attack", "hurt", "dead"}) {
        object[0].animation.insert(action, player.getAnimation(action + "_right"));
        object[1].animation.insert(action, flip(monster.animationSetReference().getAnimation(action)));
    }
}
BattleState :: ~BattleState() {

}
void BattleState :: play(Object &u, Object &v) {
    v.attribute.add("health", -std :: max(u.attribute.get("attack") - v.attribute.get("defence"), 0));
}
void BattleState :: update(const float& deltaTime) {
    timer += deltaTime;
    if(timer > battleDuration) {
        timer = 0.f;
        play(object[turn], object[turn ^ 1]);
        turn ^= 1;
    }
    if(object[0].attribute.dead() || object[1].attribute.dead()) {
        player.attributeReference() = object[0].attribute;
        stateStack() -> pop(); return;
    }
    object[0].update(deltaTime), object[1].update(deltaTime);
}
void BattleState :: render(sf :: RenderTarget* target) {
    object[0].render(target);
    object[1].render(target);
}