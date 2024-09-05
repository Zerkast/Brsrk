#ifndef SPRITESHEETS_HPP
#define SPRITESHEETS_HPP
#include <SDL2/SDL_pixels.h>
#include <string>
#include <unordered_map>
#include "Utility.hpp"

namespace Spritesheets {
        static unordered_map<string, Vector2> spritesheets = {{"foresta.png", {50, 50}}, 
                        {"vegetazione.png", {70, 120}},
                        {"gutsPortrait.png", {300, 415}},
                        {"caskaPortrait.png", {260, 258}},
                        {"guts.png", {35, 50}}}; //50; 91
};
#endif