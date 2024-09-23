#include "MainMenu.hpp"
#include "Colors.hpp"
#include "UIRenderer.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <cstdio>
int showMainMenu(int wwidth, int wheight, SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    float scaler = (float)wwidth/1280;
    SDL_Rect titleRect = {scale(scaler, 50), scale(scaler, 50), scale(scaler, 200), scale(scaler, 100)};
    SDL_Rect startButtonRect = {scale(scaler, 60), scale(scaler, 200), 0, 0};
    SDL_Rect quitButtonRect = {scale(scaler, 60), scale(scaler, 250), 0, 0}; 
    SDL_Rect background = {0, 0, wwidth, wheight};
    SDL_Texture *backgroundTexture = IMG_LoadTexture(renderer, "res/mainmenu.jpg");
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &background);
    int smallFontSize = scale(scaler, 30);
    drawText(renderer, "BRSRK", 50, 50, nullptr, nullptr, scale(scaler, 100), Colors::OPAQUE_DARK_RED, 0);
    drawText(renderer, "Start game", startButtonRect.x, startButtonRect.y, &startButtonRect.w , &startButtonRect.h, smallFontSize, Colors::OPAQUE_DARK_RED, 0);
    drawText(renderer, "Quit", quitButtonRect.x, quitButtonRect.y, &quitButtonRect.w , &quitButtonRect.h, smallFontSize, Colors::OPAQUE_DARK_RED, 0);
    SDL_Event event;
    SDL_RenderPresent(renderer);
    bool choiceHasBeenMade = false;
    while (!choiceHasBeenMade) {
        while (SDL_PollEvent(&event)) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (event.button.x>=startButtonRect.x&&event.button.x<=startButtonRect.x+startButtonRect.w&&event.button.y>=startButtonRect.y&&event.button.y<=startButtonRect.y+startButtonRect.h) {
                    printf("Game starting...");
                    return 1;
                }
                else if (event.button.x>=quitButtonRect.x&&event.button.x<=quitButtonRect.x+quitButtonRect.w&&event.button.y>=quitButtonRect.y&&event.button.y<=quitButtonRect.y+quitButtonRect.h) {
                    printf("Closing window...");
                    return -1;
                }    
            }
        }
        SDL_Delay(16);
    }
}