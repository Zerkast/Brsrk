#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "LevelHandler.hpp"
#include "Utility.hpp"
#include <SDL2/SDL_render.h>


class Entity {
protected:
    int x;
    int y;
    int width;
    int height;
    int maxSpeed;
    int currentSpeed;
    int currentPosition;
    int currentAnimationFrame;
    Vector2 currentDirection;
    int acceleration; //
    int health;
    int maxHealth;
    SDL_Texture *spritesheet;
    Vector2 spriteSizes; 
    LevelHandler *currentLevel;
    int scaler;
    SDL_Texture *overlinedSpritesheet; 
    //AnimationStats 
    //RICORDA DI IMPLEMENTARE UN COSTRUTTORE, IN ENTITY NON C'È PERCHÈ È CLASSE ASTRATTA
public:
    int getX() { //con metodi piccoli la definizione può essere fatta direttamente nell'header
        return x;
    } 
    int getY() {
        return y;
    }
    void setX(int x) {
        this->x = x;
    }
    void setY(int y) {
        this->y = y;
    }
    int getWidth() {
        return width;
    }
    int getHeight() {
        return height;
    }
    void setMaxSpeed(int speed) {
        maxSpeed = speed;
    }
    void setCurrentDirection(int x, int y) {
        currentDirection.x = x;
        currentDirection.y = y;
    }
    void setAcceleration(int acceleration) {
        this->acceleration = acceleration;
    }
    void setCurrentSpeed(int speed) {
        currentSpeed = speed;
    }
    void setCurrentLevel(LevelHandler *lvl) {
        currentLevel = lvl;
    }
    void update();

    void setSpritesheet(SDL_Texture *spritesheet, Vector2 spritesize) {
        this->spritesheet = spritesheet;
        spriteSizes = spritesize;
    }

    void updateHealth(int value) {
        health += value;
    }
    void resetHealth() {
        health = maxHealth;
    }
    void setMaxHealth(int value) {
        maxHealth = value;
    }
    
    void setScaler(int value) {
        scaler = value;
    }
};
#endif