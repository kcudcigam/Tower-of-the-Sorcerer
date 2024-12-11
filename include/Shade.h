#pragma once
#include "SFML/Graphics.hpp"

class Shade {
private:
    sf :: RectangleShape background;
    float duration, alpha; bool lighter, paused;
public:
    Shade(const float &duration, const bool &lighter);
    virtual ~Shade();
    bool end() const;
    void update(const float &deltaTime);
    void render(sf :: RenderTarget* target);
    void reset();
    void pause();
    void run();
};