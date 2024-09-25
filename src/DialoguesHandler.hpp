#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include "Utility.hpp"
#include <SDL2/SDL_rect.h>
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
    int fontSize;
    SDL_Texture *textToShow;
    SDL_Rect textToShowRect;
    int currentCharInText;
    char **names;
    bool *leftOrRight;
    int *dialoguesSizes;
    int actorsNum;
    int dialogNums;
    int currentDialog;
    char **dialogues;
    bool nextDialogue();
    bool nextChar();
public:
    DialoguesHandler(SDL_Renderer *renderer);
    DialoguesHandler(SDL_Renderer *renderer, int scaler);
    void LoadFile(const char* filepath);
    void setScaler(int value); //con il float potrebbero esserci errori di approssimazione, ma va presso in considerazione
    void playDialogue();
    void reset();
};
#endif