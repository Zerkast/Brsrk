#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <string>

using namespace std;

#define WWIDTH 1280 //le leggo poi da un config.json o un sqlite
#define WHEIGHT 720
typedef struct {
    int x;
    int y;
} Vector2; //magari lo sposto poi in un datatypes.h o comunque header apposta insieme ad altri tipi utili

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} Box;

vector<string> split(string stringToSplit, char delimiter);

int parseInt(string inputString);

bool isNumber(string inputString); //non parsa numeri negativi

SDL_Texture *getTextTexture(SDL_Renderer *renderer, char *text, SDL_Rect *rect, int fontSize, SDL_Color color, int wrapSize);

#endif