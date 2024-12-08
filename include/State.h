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
    GameState(sf :: RenderWindow* window, std :: stack<State*>* states, const std :: string &map);
    ~GameState();
    void checkForQuit();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};