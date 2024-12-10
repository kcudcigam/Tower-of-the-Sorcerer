#pragma once
#include <stack>
#include "SFML/Graphics.hpp"
#include "Resource.h"
#include "Subtitle.h"
#include "Tilemap.h"

class State {
private:
    sf :: RenderWindow* window;
    std :: vector<sf :: Texture> texture;
    std :: stack<State*>* states;
    bool isEnd;
public:
    State(sf :: RenderWindow* window, std :: stack<State*>* states);
    virtual ~State();
    void quit();
    const bool& end() const;
    sf :: RenderWindow* getWindow() const;
    std :: stack<State*>* stateStack() const;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf :: RenderTarget* target) = 0;
};

class MenuState : public State {
private:
    sf :: RectangleShape background;
    sf :: Texture backgroundTexture;
public:
    MenuState(sf :: RenderWindow* window, std :: stack<State*>* states);
    ~MenuState();
    void checkForQuit();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};

class GameState : public State {
private:
    Tilemap map;
public:
    GameState(sf :: RenderWindow* window, std :: stack<State*>* states, const std :: string &map, const Attribute &attribute);
    ~GameState();
    void checkForQuit();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};

class DictionaryState : public State {
private:
    sf :: Sprite sprite;
    sf :: RectangleShape background;
    std :: vector<Monster> monsters;
    sf :: Text text;
    size_t it; bool leftPress, rightPress;
public:
    DictionaryState(sf :: RenderWindow* window, std :: stack<State*>* states, const std :: vector<Monster> &monsters);
    ~DictionaryState();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};