#ifndef COLORS_HPP
#define COLORS_HPP
#include <SDL2/SDL_pixels.h>
#include <string>
#include <unordered_map>
#include "Utility.hpp"

namespace Spritesheets {
        static unordered_map<string, Vector2> spritesheets = {{"foresta.png", {50, 50}}, 
                        {"vegetazione.png", {70, 120}},
                        {"guts.png", {35, 50}}}; //50; 91
}
#endif