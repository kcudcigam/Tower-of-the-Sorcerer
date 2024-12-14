#pragma once
#include<iostream>
#include "SFML/Graphics.hpp"
#include "Resource.h"
#include "Subtitle.h"
#include "Tilemap.h"
#include "Shade.h"

template<typename T> class Stack {
private:
    T *topState, *menu;
    std :: vector<T*> rub;
    std :: map<T*, T*> back;
    std :: map<T*, std :: vector<T*> > next;
public:
    Stack() : topState(nullptr), menu(nullptr) {

    }
    virtual ~Stack() {
        clear();
        for(auto it : rub) delete it;
        if(menu != nullptr) delete menu;
    }
    T* top() {
        return topState;
    }
    void setMenu(T* menu) {
        this -> menu = menu, this -> topState = menu;
    }
    bool hasForward() const {
        return next.find(topState) != next.end() && !next.at(topState).empty();
    }
    void pop() {
        assert(topState != menu);
        if(next.find(topState) != next.end()) {
            assert(next[topState].empty());
            next.erase(next.find(topState));
        }
        const auto newTop = back[topState];
        back.erase(back.find(topState));
        next[newTop].pop_back();
        rub.emplace_back(topState);
        topState = newTop;
    }
    void push(T* newState) {
        if(back.find(newState) != back.end()) {
            topState = newState; return;
        }
        next[topState].emplace_back(newState);
        back[newState] = topState;
        topState = newState;
    }
    T* getBackward() {
        assert(topState != menu);
        return back[topState];
    }
    T* getForward() {
        assert(hasForward());
        return next[topState].back();
    }
    void clear() {
        for(auto state : back) rub.emplace_back(state.first);
        back.clear(), next.clear();
        topState = menu;
    }
};

class State {
private:
    sf :: RenderWindow* window;
    Stack<State>* states;
public:
    State(sf :: RenderWindow* window, Stack<State>* states);
    virtual ~State();
    sf :: RenderWindow* getWindow() const;
    Stack<State>* stateStack() const;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf :: RenderTarget* target) = 0;
};

class MenuState : public State {
private:
    sf :: RectangleShape background;
    Shade startShade;
public:
    MenuState(sf :: RenderWindow* window, Stack<State>* states);
    ~MenuState();
    void login();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};

class GameState : public State {
private:
    Tilemap map;
    sf :: Text location;
    Shade startShade, endShade;
    State* newState;
public:
    GameState(sf :: RenderWindow* window, Stack<State>* states, const std :: string &map, const Attribute &attribute);
    ~GameState();
    const std :: wstring& getName() const;
    void login(const Attribute &attribute = Attribute(), const std :: wstring &text = L"");
    void logout(State* state);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};

class DictionaryState : public State {
private:
    sf :: Sprite sprite;
    sf :: RectangleShape background;
    std :: vector<Monster> monsters;
    sf :: Text text, beaten, drop, skill;
    size_t it; bool leftPress, rightPress;
public:
    DictionaryState(sf :: RenderWindow* window, Stack<State>* states, const std :: vector<Monster> &monsters);
    ~DictionaryState();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};

class BattleState : public State {
private:
    struct Object {
        sf :: Sprite sprite;
        AnimationSet animation;
        sf :: Text name;
        Attribute attribute;
        std :: string color, skill;
        std :: wstring wname;
        int turns, origin;
        void update(const float &deltaTime);
        void render(sf :: RenderTarget* target);
    }object[2];
    bool turn;
    sf :: RectangleShape background;
    bool inAttack, inHurt, end;
    float startTimer, endTimer;
    Shade endShade; int drop;
    void play(Object &u, Object &v);
public:
    BattleState(sf :: RenderWindow* window, Stack<State>* states, Player &player, Monster &monster);
    ~BattleState();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};

class WinState : public State {
private:
    sf :: RectangleShape background;
    sf :: Text text;
    bool enterPress;
public:
    WinState(sf :: RenderWindow* window, Stack<State>* states, int score);
    ~WinState();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};

class DeadState : public State {
private:
    sf :: RectangleShape background;
    sf :: Text text;
    bool enterPress;
public:
    DeadState(sf :: RenderWindow* window, Stack<State>* states, int score);
    ~DeadState();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};