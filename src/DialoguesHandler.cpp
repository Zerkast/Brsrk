#include "Spritesheets.hpp"
#include "Colors.hpp"
#include "UIRenderer.hpp"
#include "Utility.hpp"
#include "DialoguesHandler.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>

using namespace std; 
DialoguesHandler::DialoguesHandler(SDL_Renderer *renderer) {
    this->renderer = renderer;
    scaler = 1;
    fontSize = 30;
}
DialoguesHandler::DialoguesHandler(SDL_Renderer *renderer, int scaler) {
    this->renderer = renderer;
    this->scaler = scaler/3;
    textboxSize.x = 1280;
    textboxSize.y = 300;
    fontSize = 30;

}
void DialoguesHandler::LoadFile(const char* filepath) {
    std::ifstream dialoguesFile;
    std::string line;
    dialoguesFile.open(filepath);
    std::getline(dialoguesFile, line);
    actorsNum = parseInt(line);
    spritesheets = new SDL_Texture*[actorsNum];
    spritesheetsSizes = new Vector2[actorsNum];
    names = new char*[actorsNum];
    int index = 0;
    if (dialoguesFile.is_open()) {
        while (std::getline(dialoguesFile, line) && line != "\n" && line != "") {
            string path = "res/"+line;
            spritesheets[index] = IMG_LoadTexture(renderer, path.c_str());
            spritesheetsSizes[index] = Spritesheets::spritesheets.at(line);
            if (spritesheets[index]==NULL) {
                printf("Error loading spritesheet: %s", path.c_str());
            }
            std::getline(dialoguesFile, line);
            names[index] = new char[line.length()];
            strcpy(names[index], line.c_str());
            index++;
        }
        textboxBackground = IMG_LoadTexture(renderer, "res/textbox.png");
        std::getline(dialoguesFile, line);
        dialogNums = parseInt(line);
        // dialogues  = (char**)malloc(dialogNums*sizeof(char*));
        dialogues = new char*[dialogNums];
        actor = new int[dialogNums];
        spriteToUse = new int[dialogNums];
        leftOrRight = new bool[dialogNums];
        dialoguesSizes = new int[dialogNums];
        currentDialog = 0;
        while (std::getline(dialoguesFile, line)) {
            std::getline(dialoguesFile, line);
            actor[currentDialog] = parseInt(line);
            std::getline(dialoguesFile, line);
            spriteToUse[currentDialog] = parseInt(line);
            std::getline(dialoguesFile, line);
            leftOrRight[currentDialog] = (int)true == parseInt(line);
            std::getline(dialoguesFile, line);
            dialoguesSizes[currentDialog] = line.size();
            dialogues[currentDialog] = new char[line.length()];
            strcpy(dialogues[currentDialog], line.c_str());
            currentDialog++;
        }
        for (int i = 0; i < dialogNums; i++) {
            printf("%s - actor: %d with sprite: %d on side: %d\n", dialogues[i], actor[i], spriteToUse[i], leftOrRight[i]);
        }
        currentDialog = 0;
    }
}
void DialoguesHandler::setScaler(int value) {
    scaler = value;
} 
bool DialoguesHandler::nextDialogue() { //nel dialogo.dat bisogna aggiungere un parametro che dice se il personaggio che parla si deve trovare a sinistra o a destra
    if (currentDialog>=dialogNums) return false;
    SDL_Rect src = {spriteToUse[currentDialog]*spritesheetsSizes[actor[currentDialog]].x, 0, spritesheetsSizes[actor[currentDialog]].x, spritesheetsSizes[actor[currentDialog]].y};
    int xdst = 0;
    if (leftOrRight[currentDialog]) xdst = WWIDTH-(spritesheetsSizes[actor[currentDialog]].x*scaler);
    SDL_Rect dst = {xdst, WHEIGHT-spritesheetsSizes[actor[currentDialog]].y*scaler-textboxSize.y*scaler, spritesheetsSizes[actor[currentDialog]].x*scaler, spritesheetsSizes[actor[currentDialog]].y*scaler};
    SDL_RenderCopy(renderer, spritesheets[actor[currentDialog]], &src, &dst);
    if (currentDialog>0 && leftOrRight[currentDialog-1]!=leftOrRight[currentDialog]) {
        src = {spriteToUse[currentDialog-1]*spritesheetsSizes[actor[currentDialog-1]].x, 0, spritesheetsSizes[actor[currentDialog-1]].x, spritesheetsSizes[actor[currentDialog-1]].y};
        xdst = 0;
        if (leftOrRight[currentDialog-1]) xdst = WWIDTH-(spritesheetsSizes[actor[currentDialog-1]].x*scaler);
        dst = {xdst, WHEIGHT-spritesheetsSizes[actor[currentDialog-1]].y*scaler-textboxSize.y*scaler, spritesheetsSizes[actor[currentDialog-1]].x*scaler, spritesheetsSizes[actor[currentDialog-1]].y*scaler};
        SDL_RenderCopy(renderer, spritesheets[actor[currentDialog-1]], &src, &dst);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
        SDL_RenderFillRect(renderer, &dst);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }
    src = {0, 0, textboxSize.x, textboxSize.y};
    dst = {0, WHEIGHT-textboxSize.y, textboxSize.x*scaler, textboxSize.y*scaler}; 
    SDL_RenderCopy(renderer, textboxBackground, &src, &dst);
    dst.x = 40;
    dst.w-=40;
    dst.y+=40;
    dst.h-=40;
    drawText(renderer, names[actor[currentDialog]], dst, 38, Colors::OPAQUE_DARK_RED, WWIDTH-40);
    dst.y+=46;
    printf("%s", dialogues[currentDialog]);
    textToShowRect = dst;
    return true;
}

bool DialoguesHandler::nextChar() {
    if (currentCharInText==dialoguesSizes[currentDialog]) return false;
    char* currentString = new char[currentCharInText+2];
    for (int i = 0; i < currentCharInText + 1; i++) {
        currentString[i] = dialogues[currentDialog][i];
    }
    currentString[currentCharInText+1]='\0';
    drawText(renderer, currentString, textToShowRect, fontSize, Colors::OPAQUE_WHITE, 0);
    SDL_RenderCopy(renderer, textToShow, NULL, &textToShowRect);
    currentCharInText++;
    return true;
}

void DialoguesHandler::playDialogue() {
    while (nextDialogue()) {
        currentCharInText = 0;
        int delay = 200;
        SDL_Event keyboardEvent;
        while (nextChar()) {
            while (SDL_PollEvent(&keyboardEvent)) {
                if (keyboardEvent.type==SDL_KEYUP) {
                    delay = 0;
                } 
            }
            SDL_Delay(delay);
            SDL_RenderPresent(renderer);
        }
        currentDialog++;
        SDL_RenderClear(renderer);
    }
}