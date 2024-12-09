#pragma once
#include "SFML/Graphics.hpp"
#include "Resource.h"
#include "Subtitle.h"

class Attribute{
private:
    std :: map<std :: string, int> attribute;
public:
    Attribute(const int &health, const int &attack, const int &defence);
    virtual ~Attribute();
    void set(const std :: string &type, const int &value);
    void add(const std :: string &type, const int &value);
    int get(const std :: string &type) const;
    void render(sf :: RenderTarget* target, sf :: Vector2f position, const std :: vector<std :: string> &types, const std :: string &color) const;
};