#include "State.h"
extern Resource resource;
extern Subtitle subtitle;

//State
State :: State(sf :: RenderWindow* window, Stack<State>* states) : window(window ), states(states) {
}
State :: ~State() {
    
}
sf :: RenderWindow* State :: getWindow() const {
    return window;
}
Stack<State>* State :: stateStack() const {
    return states;
}

//MenuState
MenuState :: MenuState(sf :: RenderWindow* window, Stack<State>* states) : State(window, states) {
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
void MenuState :: update(const float &deltaTime) {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape)) stateStack() -> pop();

    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Enter))
        stateStack() -> push(new GameState(getWindow(), stateStack(), "prison.json", Attribute(100, 50, 5, 0)));
}
void MenuState :: render(sf :: RenderTarget* target) {
    target -> draw(background);
}

//GameState
GameState :: GameState(sf :: RenderWindow* window, Stack<State>* states, const std :: string &map, const Attribute &attribute)
 : State(window, states), map(map), startShade(0.5f, true), endShade(0.5f, false), newState(nullptr) {
    login(attribute, this -> map.getWelcome());
}
GameState :: ~GameState() {

}
void GameState :: login(const Attribute &attribute, const std :: wstring &text) {
    if(text != L"") subtitle.display(text, 2.f);
    if(!attribute.dead()) map.playerReference().attributeReference() = attribute;
    startShade.reset(), endShade.reset(); endShade.pause();
    map.playerReference().setBattle(""); 
    map.playerReference().setLocation(""); 
    map.playerReference().setHidden(false); 
    this -> map.playerReference().addTag("busy", 0.5f);
}
const std :: wstring& GameState :: getName() const {
    return map.getName();
}
void GameState :: logout(State* state) {
    newState = state; endShade.run();
}
void GameState :: update(const float &deltaTime) {
    startShade.update(deltaTime), endShade.update(deltaTime);
    if(endShade.end() && newState != nullptr) {
        endShade.reset(); endShade.pause();
        stateStack() -> push(newState);
        newState = nullptr;
        
        return;
    }
    subtitle.update(deltaTime);
    if(newState != nullptr) return;
    map.update(deltaTime);
    if(map.playerReference().dead()) {
        logout(new DeadState(getWindow(), stateStack())); return;
    }
    if(map.playerReference().getAttribute().dead()) return;

    if(map.playerReference().getLocation() != "") {
        if(map.playerReference().getLocation() == "forward") {
            if(stateStack() -> hasForward()) {
                GameState* forward = static_cast<GameState*>(stateStack() -> getForward());
                forward -> login(map.playerReference().attributeReference(), L"你来到了" + forward -> getName());
                logout(stateStack() -> getForward());
            }
            else logout(new GameState(getWindow(), stateStack(), map.getNext(), map.playerReference().attributeReference()));
        }
        else {
            GameState* backward = static_cast<GameState*>(stateStack() -> getBackward());
            backward -> login(map.playerReference().attributeReference(), L"你回到了" + backward -> getName());
            logout(stateStack() -> getBackward());
        }
        return;
    }

    if(map.playerReference().getBattle() != "") {
        logout(new BattleState(getWindow(), stateStack(), map.playerReference(), map.monsterReference(map.playerReference().getBattle()))); return;
    }
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: X)) {
        logout(new DictionaryState(getWindow(), stateStack(), map.getMonsterList())); return;
    }
}
void GameState :: render(sf :: RenderTarget* target) {
    map.render(target);
    if(newState == nullptr && startShade.end()) subtitle.render(target);
    startShade.render(target);
    endShade.render(target);
}

//DictionaryState
DictionaryState :: DictionaryState(sf :: RenderWindow* window, Stack<State>* states, const std :: vector<Monster> &monsters)
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
    if(!(attribute.dead() && !animation.hasPriority())) animation.play(&sprite, "idle", deltaTime, 4.f);
}
void BattleState :: Object :: render(sf :: RenderTarget* target) {
    target -> draw(sprite);
    target -> draw(name);
    attribute.render(target, sprite.getPosition() + sf :: Vector2f(-80.f, 60.f), {"health", "attack", "defence"}, color);
}

const float battleDuration = 2.f;
BattleState :: BattleState(sf :: RenderWindow* window, Stack<State>* states, Player &player, Monster &monster)
 : State(window, states), turn(false), inAttack(false), inHurt(true), end(false), startTimer(0.5f), endTimer(0.5f), endShade(0.5f, false) {
    subtitle.clear(); endShade.reset(); endShade.pause();
    background.setSize(sf :: Vector2f (
        static_cast<float>(getWindow() -> getSize().x), 
        static_cast<float>(getWindow() -> getSize().y)
        )
    );
    background.setTexture(resource.getImg("battle-background.png"));
    object[0].sprite.setPosition(getWindow() -> getSize().x * 0.25f, getWindow() -> getSize().y / 2.f);
    object[1].sprite.setPosition(getWindow() -> getSize().x * 0.75f, getWindow() -> getSize().y / 2.f);
    object[0].attribute = player.attributeReference();
    object[1].attribute = monster.attributeReference();
    object[0].color = "green", object[1].color = "brown";
    object[0].name.setFont(*resource.getFont("pixel.ttf"));
    object[1].name.setFont(*resource.getFont("pixel.ttf"));
    object[0].wname = L"你", object[1].wname = monster.getName();
    object[0].name.setString(L"勇士"), object[1].name.setString(object[1].wname);
    object[0].name.setPosition(object[0].sprite.getPosition() + sf :: Vector2f(-50.f, 20.f));
    object[1].name.setPosition(object[1].sprite.getPosition() + sf :: Vector2f(-50.f, 20.f));
    object[0].turns = object[1].turns = 0;
    for(const std :: string &action : {"idle", "attack", "hurt", "dead"}) {
        object[0].animation.insert(action, player.getAnimation(action + "_right"));
        object[1].animation.insert(action, flip(monster.animationSetReference().getAnimation(action)));
    }
}
BattleState :: ~BattleState() {

}
void BattleState :: play(Object &u, Object &v) {
    const int damage = std :: max(u.attribute.get("attack") - v.attribute.get("defence"), 0);
    v.attribute.add("health", -damage);
    v.animation.setPriority(v.attribute.dead() ? "dead" : "hurt");
    if(v.attribute.dead()) subtitle.display(u.wname + L"对" + v.wname + L"发动了一次攻击, 并击败了" + v.wname, 5.f);
    else if(damage) subtitle.display(u.wname + L"对" + v.wname + L"发动了一次攻击, 并造成" + std :: to_wstring(damage) + L"点伤害", 5.f);
    else subtitle.display(u.wname + L"对" + v.wname + L"发动了一次攻击, 但未产生伤害", 5.f);
}
void BattleState :: update(const float& deltaTime) {
    if(end) {
        endShade.update(deltaTime);
        if(endShade.end()) stateStack() -> push(new DeadState(getWindow(), stateStack()));
        return;
    }
    object[0].update(deltaTime), object[1].update(deltaTime), subtitle.update(deltaTime);
    startTimer = std :: max(0.f, startTimer - deltaTime); if(startTimer > 0.f) return;
    if(object[0].attribute.dead() && !object[0].animation.hasPriority()) {
        endShade.run(); end = true;
        return;
    }
    if(object[1].attribute.dead() && !object[1].animation.hasPriority()) {
        endTimer = std :: max(0.f, endTimer - deltaTime); if(endTimer > 0.f) return;
        subtitle.clear(); stateStack() -> pop();
        static_cast<GameState*>(stateStack() -> top()) -> login(object[0].attribute, L"你击败了" + object[1].wname + L"并获得");
        return;
    }
    if(inAttack && sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Enter))
        object[turn].animation.setPriority("");
    if(inAttack && !object[turn].animation.hasPriority()) {
        inAttack = false, inHurt = true;
        play(object[turn], object[turn ^ 1]);
        turn ^= 1;
    }
    if(inHurt && !object[turn].animation.hasPriority()) {
        inAttack = true, inHurt = false;
        object[turn].animation.setPriority("attack");
    }
}
void BattleState :: render(sf :: RenderTarget* target) {
    target -> draw(background);
    object[0].render(target);
    object[1].render(target);
    subtitle.render(target);
    endShade.render(target);
}

//DeadState
DeadState :: DeadState(sf :: RenderWindow* window, Stack<State>* states) : State(window, states), enterPress(false) {
    background.setSize(sf :: Vector2f (
        static_cast<float>(getWindow() -> getSize().x), 
        static_cast<float>(getWindow() -> getSize().y)
        )
    );
    background.setTexture(resource.getImg("dead-background.png"));
}
DeadState :: ~DeadState() {
    
}
void DeadState :: update(const float& deltaTime) {
    if(enterPress && !sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Enter)) {
        stateStack() -> clear(); return;
    }
    enterPress = sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Enter);
}
void DeadState :: render(sf :: RenderTarget* target) {
    target -> draw(background);
}