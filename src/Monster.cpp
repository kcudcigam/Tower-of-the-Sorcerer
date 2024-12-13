#include "Monster.h"
extern std :: mt19937 rnd;
//Monster
Monster :: Monster(const std :: wstring &name) : name(name), cnt({0, 0}), skill(""), drop("") {

}
Monster :: ~Monster() {

}
bool Monster :: any() const {
    return cnt.second > 0;
}
const std :: pair<int, int>& Monster :: getCnt() const {
    return cnt;
}
const std :: wstring& Monster :: getName() const {
    return name;
}
const std :: string& Monster :: getSkill() const {
    return skill;
}
int Monster :: getDrop() const {
    if(drop.empty()) return -1;
    return drop[rnd() % drop.size()] - '0';
}
const std :: string& Monster :: getDropList() const {
    return drop;
}
void Monster :: setSkill(const std :: string &skill) {
    this -> skill = skill;
}
void Monster :: setDrop(const std :: string &drop) {
    this -> drop = drop;
}
Attribute& Monster :: attributeReference() {
    return attribute;
}
AnimationSet& Monster :: animationSetReference() {
    return animation;
}
void Monster :: insertAction(const std :: string &key, const Animation &action) {
    animation.insert(key, action);
}
void Monster :: setAttribute(const std :: string &key, const int &value) {
    attribute.set(key, value);
    if(key == "health") attribute.set("max_health", value);
}
void Monster :: add() {
    cnt.first++, cnt.second++;
}
void Monster :: del() {
    assert(cnt.first > 0); cnt.first--;
}