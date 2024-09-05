#include "UIRenderer.hpp"
            
void drawText(SDL_Renderer *renderer, char *text, int x, int y, int *width, int *height, int fontSize, SDL_Color color, int wrapSize) {
    TTF_Font* font = TTF_OpenFont("res/Comic-Sans.ttf", fontSize); //anche questo sarà poi un parametro
    if (font == NULL) {
        printf("Error opening font: %s\n", SDL_GetError());
        return;
    }
    SDL_Surface* textSurface;
    if (wrapSize > 0) {
         textSurface = TTF_RenderText_Blended_Wrapped(font, text, color, wrapSize); //va a capo dopo tot px, definiti in wrapSize
    } else {
         textSurface = TTF_RenderText_Blended(font, text, color); 
    }
    if (width == nullptr) {
        width = new int;
        *width = 0; 
    }
    if (height == nullptr) {
        height = new int;
        *height = 0;
    }
    if (*width == 0 || *height == 0) {
        TTF_SizeText(font, text, width, height);
    }
    // for (int i = 0; i < width/120; i++) {
    //     height+=height;
    // }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        printf("error creating texture: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }
    SDL_Rect textTexture_rect = {x, y, *width, *height};
    SDL_RenderCopy(renderer, textTexture, NULL, &textTexture_rect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

void drawText(SDL_Renderer *renderer, char *text, SDL_Rect dstRect, int fontSize, SDL_Color color, int wrapSize) {
    TTF_Font* font = TTF_OpenFont("res/Comic-Sans.ttf", fontSize); //anche questo sarà poi un parametro
    if (font == NULL) {
        printf("Error opening font: %s\n", SDL_GetError());
        return;
    }
    SDL_Surface* textSurface;
    if (wrapSize > 0) {
         textSurface = TTF_RenderText_Blended_Wrapped(font, text, color, wrapSize); //va a capo dopo tot px
    } else {
         textSurface = TTF_RenderText_Blended(font, text, color); 
    }
    TTF_SizeText(font, text, &dstRect.w, &dstRect.h);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        printf("error creating texture: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }
    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}
int scale(float scaler, int originalSize) {
    return originalSize*scaler;
}

void drawMainMenu(int wwidth, int hheight, SDL_Window *window);
void renderVideo(char* videoPath, SDL_Renderer *renderer);