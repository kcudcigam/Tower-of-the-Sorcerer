#include "Game.h"
#include "Resource.h"
#include "Subtitle.h"
Resource resource("../resource");
Subtitle subtitle;
int main() {
    Game process;
    process.run();
    return 0;
}