#ifndef COLORS_HPP
#define COLORS_HPP
#include <SDL2/SDL_pixels.h>

namespace Colors { //anche qui si potrebbe fare un hashmap come per gli spritesheets
        static const SDL_Color OPAQUE_BLACK = {0, 0, 0, SDL_ALPHA_OPAQUE};
        static const SDL_Color OPAQUE_DARK_RED = {139, 0, 0, SDL_ALPHA_OPAQUE};
}
#endif