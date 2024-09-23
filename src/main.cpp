#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include "Character.hpp"
#include "DialoguesHandler.hpp"
#include "LevelHandler.hpp"
#include "MainMenu.hpp"
#include "MainStates.hpp"
#include "Spritesheets.hpp"
#include "Utility.hpp"
using namespace std;

void playSound() { //asincrono

}

int main(void) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int status = 0;
    // int scaler = WWIDTH/426;
    int scaler = 3;
    bool quit = false;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        return 1;                               //controlla se si puo inizializzare SDL e in caso contrario fa il return di 1
        printf("SDL couldn't be initialized: %s\n", SDL_GetError());
    } //fai anche ttf init e img_init 
    if (TTF_Init() < 0) {
        printf("Error initializing TTF: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow("BRSRK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, SDL_WINDOW_OPENGL); //creazione finestra
    renderer = SDL_CreateRenderer(window, -1, 0); //index a -1 per fargli usare il primo driver disponibile per il rendering
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    LevelHandler *lvl;
    DialoguesHandler *dlg = new DialoguesHandler(renderer, scaler);
    // SDL_EnableKeyRepeat( 100, SDL_DEFAULT_REPEAT_INTERVAL);
    while(!quit) {
        switch(status) {
            case MainStates::GAMEPLAY: 
                { //ci sono le graffe perchè C++ è una merda con gli scope
                    bool inGame = true;
                    // while(inGame) {
                    printf("Starting gameplay...\n");
                    // drawText(renderer, "ciao", 400, 400, nullptr, nullptr, 40, Colors::OPAQUE_DARK_RED, 0);
                    // SDL_RenderPresent(renderer);
                    // SDL_Delay(1000);
                    SDL_Event keyboardEvent;
                    printf("Loading level...\n");
                    lvl = new LevelHandler("data/esempiolivello.dat", renderer);
                    lvl->setScaler(scaler);
                    Character guts(WWIDTH/2/3, WHEIGHT/2/3, 20, 30, IMG_LoadTexture(renderer, "res/guts.png"), IMG_LoadTexture(renderer, "res/gutsOverline.png"), Spritesheets::spritesheets.at("guts.png"));
                    Vector2 currentPlayerDirection {0, 0};
                    guts.setScaler(scaler);
                    guts.setCurrentLevel(lvl);
                    guts.setAcceleration(WWIDTH/1280);
                    guts.setMaxSpeed(scaler);
                    while (inGame) {
                        // currentPlayerDirection.x = 0;
                        // currentPlayerDirection.y = 0;
                        while (SDL_PollEvent(&keyboardEvent)) {
                            if (keyboardEvent.type == SDL_QUIT) {
                                inGame = false;
                            }
                            switch (keyboardEvent.type) {
                                case SDL_KEYDOWN:
                                    switch(keyboardEvent.key.keysym.sym ){
                                        case SDLK_LEFT:
                                            currentPlayerDirection.x=-1; 
                                            break;
                                        case SDLK_RIGHT:
                                            currentPlayerDirection.x=1;
                                            break;
                                        case SDLK_UP:
                                            currentPlayerDirection.y=-1;
                                            break;
                                        case SDLK_DOWN:
                                            currentPlayerDirection.y=1;
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                case SDL_KEYUP:
                                    switch(keyboardEvent.key.keysym.sym ){
                                        case SDLK_LEFT:
                                            if(currentPlayerDirection.x < 0 )
                                                currentPlayerDirection.x = 0;
                                            break;
                                        case SDLK_RIGHT:
                                            if(currentPlayerDirection.x > 0 )
                                                currentPlayerDirection.x = 0;
                                            break;
                                        case SDLK_UP:
                                            if(currentPlayerDirection.y < 0 )
                                                currentPlayerDirection.y = 0;
                                            break;
                                        case SDLK_DOWN:
                                            if(currentPlayerDirection.y > 0 )
                                                currentPlayerDirection.y = 0;
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                default:
                                    break;
                            } 
                        }
                        // printf("%d;%d\n", currentPlayerDirection.x, currentPlayerDirection.y);
                        guts.setCurrentDirection(currentPlayerDirection.x, currentPlayerDirection.y);
                        guts.update();
                        // printf("%d;%d", guts.getX(), guts.getY());
                        int trigger = lvl->checkTriggers(guts.getX(), guts.getY());
                        if (trigger !=-1) {
                            status = trigger;
                            break; 
                        }
                        SDL_RenderClear(renderer);
                        lvl->renderLayer(renderer, 0);
                        guts.render(renderer);
                        lvl->renderLayer(renderer, 1);
                        guts.renderOverline(renderer);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(16);
                    }
                }
                        // quit = true;
                    // }
                break;
            case MainStates::QTE:
                // COSE DA QTE
                break;
            case MainStates::CUTSCENE:
                // CONTROLLA NUMERO CUTSCENE
                // RIPRODUCI CUTSCENE.mp4
                break;
            case MainStates::DIALOGE:
                SDL_RenderClear(renderer);
                dlg->LoadFile("data/esempiodialogo.dat");
                dlg->playDialogue();
                // CONTROLLA NUMERO DIALOGO
                // RIPRODUCI DIALOGO
                break;
            case MainStates::MAINMENU: 
                //MOSTRA MAINMENU
                // IN BASE A OPZIONE SCELTA:
                //     1. CARICA SALVATAGGIO (PER SAPERE LIVELLO DA CARICARE)
                //     2. STATUS = GAMEPLAY
                //     3. BREAK DAL CASE
                { //ho già detto che odio lo scoping delle variabili in C++?
                    int choice = showMainMenu(WWIDTH, WHEIGHT, renderer); 
                    if (choice == -1) quit = true;
                    status = choice;
                }
                break;
            default:
                break;
        }
    }

    // SDL_Color white = {255, 255, 255, SDL_ALPHA_OPAQUE};
    // SDL_RenderClear(renderer); 
    // SDL_Rect rectanglebg = {0, 0, WWIDTH, WHEIGHT};
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); //imposta il colore del renderer in formato RGBA, come se fosse un pennello
    // SDL_RenderFillRect(renderer, &rectanglebg);
    // SDL_RenderPresent(renderer);
    // drawText(renderer, "Odio i negri", 0, 0, 0, 0, 30, white, 0);
    // SDL_RenderPresent(renderer);
    // SDL_Delay(1000);
    SDL_CloseAudio();
    SDL_Quit(); //una sorta di Free per ripulire il tutto prima di uscire
}