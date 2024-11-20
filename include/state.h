#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class State {
protected:
    //Variables
    sf :: RenderWindow* window;
    std :: vector<sf :: Texture> texture;
    bool isQuit;
public:
    //constructor & destructor
    State(sf :: RenderWindow* window);
    virtual ~State();
    //funtions
    const bool& checkQuit() const;
    virtual void updateQuit();
    virtual void updateKeybinds(const float& deltaTime) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf :: RenderTarget* target) = 0;
    virtual void quit() = 0;
};