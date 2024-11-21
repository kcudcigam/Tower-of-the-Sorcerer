#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>
class State {
private:
    //Variables
   
    sf :: RenderWindow* window;
    std :: vector<sf :: Texture> texture;
    std :: stack<State*>* states;
    bool isEnd;
public:
    //constructor & destructor
    State(sf :: RenderWindow* window, std :: stack<State*>* states);
    virtual ~State();
    //funtions
    void quit();
    const bool& end() const;
    sf :: RenderWindow* getWindow() const;
    std :: stack<State*>* stateStack() const;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf :: RenderTarget* target = nullptr) = 0;
};