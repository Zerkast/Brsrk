#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include "Utility.hpp"
#include <SDL2/SDL_render.h>

class DialoguesHandler {
private:
    SDL_Texture **spritesheets;
    SDL_Texture *textboxBackground; //volendo posso poi consentire di avere textbox diversi
    Vector2 textboxSize;
    SDL_Renderer *renderer;
    Vector2 *spritesheetsSizes;
    int *actor; //Si potrebbe poi incapsulare la parte con actor, dialogueText e spritesheet
    int *spriteToUse;
    int scaler;
    char **names;
    bool *leftOrRight;
    int actorsNum;
    int dialogNums;
    int currentDialog;
    char **dialogues;
public:
    DialoguesHandler(SDL_Renderer *renderer);
    DialoguesHandler(SDL_Renderer *renderer, int scaler);
    void LoadFile(const char* filepath);
    void setScaler(int value); //con il float potrebbero esserci errori di approssimazione, ma va presso in considerazione
    bool nextDialogue();
};
#endif