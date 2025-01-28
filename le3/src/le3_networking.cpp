#include "le3_networking.h"
using namespace le3;

#include <SDL2/SDL.h>
#include <fmt/core.h>
using fmt::print;

LE3Networking& LE3Networking::instance() {
    static LE3Networking* instance_ = new LE3Networking();
    return *instance_;
}
int LE3Networking::networkThreadPtr(void* data) {
    return LE3Networking::instance().networkThread(data);
}

int LE3Networking::networkThread(void* data) {
    while (true) {
        SDL_Delay(1000);
        print("networking...\n");
    }

    return 0;
}