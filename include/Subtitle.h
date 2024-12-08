#pragma once
#include "SFML/Graphics.hpp"
#include "Resource.h"

class Subtitle {
private:
    sf :: Text text;
    float countdown;
public:
    Subtitle();
    virtual ~Subtitle();
    void setFont(const std :: string &file);
    void setPosition(const sf :: Vector2f &position);
    void display(const std :: wstring &sentence, const float &duration);
    void clear();
    void update(const float &deltaTime);
    void render(sf :: RenderTarget* target) const;
};