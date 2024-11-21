#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
class State {
private:
    //Variables
    sf :: RenderWindow* window;
    std :: vector<sf :: Texture> texture;
    bool isEnd;
public:
    //constructor & destructor
    State(sf :: RenderWindow* window);
    virtual ~State();
    //funtions
    void quit();
    const bool& end() const;
    sf :: RenderWindow* getWindow() const;
    virtual void update(const float& deltaTime) = 0;
    virtual void render() = 0;
};