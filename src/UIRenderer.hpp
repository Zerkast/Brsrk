#ifndef UIRENDERER_HPP
#define UIRENDERER_HPP
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
void drawText(SDL_Renderer *renderer, char *text, int x, int y, int *width, int *height, int fontSize, SDL_Color color, int wrapSize);
void drawText(SDL_Renderer *renderer, char *text, SDL_Rect dstRect, int fontSize, SDL_Color color, int wrapSize);
int scale(float scaler, int originalSize);
void renderVideo(char* videoPath, SDL_Renderer *renderer);
//TODO: void drawUI()
#endif