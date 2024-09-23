#include "Utility.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

using namespace std;

vector<string> split(string stringToSplit, char delimiter) {
    vector<string> result;
    int startIndex = 0;
    for (int i = 0; i<stringToSplit.size(); i++) {
        if (stringToSplit[i]==delimiter) {
            result.push_back(stringToSplit.substr(startIndex, i));
            startIndex=i+1;
        }
    }
    result.push_back(stringToSplit.substr(startIndex, stringToSplit.size()));
    return result;
}

int parseInt(string inputString) {
    int result = 0;
    string::const_iterator it = inputString.begin();
    for (int i = 0; i < inputString.size(); i++) {
        result*=10;
        result+=inputString[i]-48;
    }
    isdigit(*it);
    return result;
}

bool isNumber(string inputString) { //non parsa numeri negativi
    string::const_iterator it = inputString.begin();
    while (it != inputString.end() && isdigit(*it)) it++;
    return !inputString.empty() && it == inputString.end();
}

SDL_Texture *getTextTexture(SDL_Renderer *renderer, char *text, SDL_Rect *rect, int fontSize, SDL_Color color, int wrapSize) {
    TTF_Font* font = TTF_OpenFont("res/Comic-Sans.ttf", fontSize); //anche questo sarà poi un parametro
    if (font == NULL) {
        printf("Error opening font: %s\n", SDL_GetError());
    }
    SDL_Surface* textSurface;
    if (wrapSize > 0) {
         textSurface = TTF_RenderText_Blended_Wrapped(font, text, color, wrapSize); //va a capo dopo tot px
    } else {
         textSurface = TTF_RenderText_Blended(font, text, color); 
    }
    TTF_SizeText(font, text, &rect->w, &rect->h);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        printf("error creating texture: %s\n", SDL_GetError());
        TTF_CloseFont(font);
    }
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return textTexture;
}
