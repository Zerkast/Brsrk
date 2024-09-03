#ifndef ACTORS_HPP
#define ACTORS_HPP

#include "Utility.hpp"
#include <SDL2/SDL_render.h>
class Actor { 
    private: 
        SDL_Texture *spritesheet;
        Vector2 spritesheetSizes;
        const char **dialogues;
        int totalNumberOfDialogues;
    
    public:
        Actor(SDL_Texture *spritesheet, const char **dialogues, Vector2 spritesheetSizes);
        const char* getDialogueText(int index);
        int getTotalNumberOfDialogues();
        SDL_Texture* getSprite(int index, SDL_Renderer *renderer); //potrebbe avere un nome più significativo
};
#endif