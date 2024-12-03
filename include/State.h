#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Resource.h"
class State {
private:
    //Variables
   
    sf :: RenderWindow* window;
    std :: vector<sf :: Texture> texture;
    std :: stack<State*>* states;
    Resource* resource;
    bool isEnd;
public:
    //constructor & destructor
    State(sf :: RenderWindow* window, std :: stack<State*>* states, Resource* resource);
    virtual ~State();
    //funtions
    void quit();
    const bool& end() const;
    Resource* getResource() const;
    sf :: RenderWindow* getWindow() const;
    std :: stack<State*>* stateStack() const;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf :: RenderTarget* target = nullptr) = 0;
};