#include "Character.hpp"
#include "LevelHandler.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <cstdio>


Character::Character(int x, int y, int width, int height, SDL_Texture *spritesheet, SDL_Texture *overlinedSpritesheet, Vector2 spriteSize) {
    this->x = x;
    this->y = y;
    initialX = x;
    initialY = y;
    this->width = width;
    this->height = height; 
    this->spritesheet = spritesheet;
    this->spriteSizes = spriteSize;
    health = 100;
    secondBar = 100;
    this->overlinedSpritesheet = overlinedSpritesheet;
    setCurrentSpeed(0);
}

void Character::update() { //controlla bordi schermo
    bool hasMoved = false;
    if (currentSpeed<maxSpeed) { //anche la speed andrebbe scalata insieme alla risoluzione del gioco e delle tile
        currentSpeed += acceleration; 
        if (currentSpeed>maxSpeed) currentSpeed = maxSpeed;
    }
    if (currentDirection.x!=0) {
        if (currentLevel->checkCollision(x+(currentSpeed*currentDirection.x), y)) {
            hasMoved = true;
            x+=(currentSpeed*currentDirection.x);
            currentLevel->setCurrentOffsetX(x-initialX);
        }
    }
    if (currentDirection.y!=0) {
        if (currentLevel->checkCollision(x, y+(currentSpeed*currentDirection.y))) {
            hasMoved = true;
            y+=(currentSpeed*currentDirection.y);
            currentLevel->setCurrentOffsetY(y-initialY);
        }
    }
    if (!hasMoved) currentSpeed = 0;
}

void Character::render(SDL_Renderer * renderer) {
    SDL_Rect dstRect = {640, 360, width*scaler, height*scaler};
    SDL_Rect srcRect = {0, 0, spriteSizes.x, spriteSizes.y};
    SDL_RenderCopy(renderer, spritesheet, &srcRect, &dstRect);
    // SDL_RenderFillRect(renderer, &dstRect);
}

void Character::renderOverline(SDL_Renderer * renderer) {
    SDL_Rect dstRect = {640, 360, width*scaler, height*scaler};
    SDL_Rect srcRect = {0, 0, spriteSizes.x, spriteSizes.y};
    SDL_RenderCopy(renderer, overlinedSpritesheet, &srcRect, &dstRect);
}

void Character::setSecondBar(int value) {
    this->secondBar = value;
}

int Character::getSecondBar() {
    return secondBar;
}



