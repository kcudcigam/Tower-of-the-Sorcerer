#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Attribute.h"

class Monster {
private:
    std :: wstring name;
    Attribute attribute;
    std :: pair<int, int> cnt;
    AnimationSet animation;
public:
    Monster(const std :: wstring &name);
    virtual ~Monster();

    const std :: wstring& getName() const;
    Attribute& getAttribute();
    AnimationSet& getAnimation();
    bool any() const;
    void insertAction(const std :: string &key, const Animation &action);
    void setAttribute(const std :: string &key, const int &value);
    void add();
    void del();
};