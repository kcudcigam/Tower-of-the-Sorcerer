#pragma once
#include <random>
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Attribute.h"

class Monster {
private:
    std :: wstring name;
    Attribute attribute;
    std :: pair<int, int> cnt;
    AnimationSet animation;
    std :: string skill, drop;
public:
    Monster(const std :: wstring &name);
    virtual ~Monster();

    const std :: wstring& getName() const;
    Attribute& attributeReference();
    AnimationSet& animationSetReference();
    bool any() const;
    const std :: pair<int, int>& getCnt() const;
    const std :: string& getSkill() const;
    int getDrop() const;
    void setSkill(const std :: string &skill);
    void setDrop(const std :: string &drop);
    const std :: string& getDropList() const;
    void insertAction(const std :: string &key, const Animation &action);
    void setAttribute(const std :: string &key, const int &value);
    void add();
    void del();
};