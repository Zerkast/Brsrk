#include "Utility.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "Actor.hpp"

        Actor::Actor(SDL_Texture *spritesheet, const char **dialogues, Vector2 spritesheetSizes) {
            this->spritesheet = spritesheet;
            this->spritesheetSizes = spritesheetSizes;
            this->dialogues = dialogues;
        }
        const char* Actor::getDialogueText(int index) {
            if (index<totalNumberOfDialogues) { //si potrebbe poi pensare a un sistema di eccezioni
                return dialogues[index];
            } else {
                return "ERROR";
            }
        }

        int Actor::getTotalNumberOfDialogues() {
            return totalNumberOfDialogues;
        }

        SDL_Texture* Actor::getSprite(int index, SDL_Renderer *renderer) {
            SDL_Rect src = {index*spritesheetSizes.x, 0, spritesheetSizes.x, spritesheetSizes.y}; 
            SDL_Texture* result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, src.w, src.h);          
            SDL_SetRenderTarget(renderer, result);
            SDL_RenderCopy(renderer, spritesheet, &src, NULL);
            SDL_SetRenderTarget(renderer, NULL);
            return result;  
        }
