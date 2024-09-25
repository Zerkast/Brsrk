#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"
#include "Sound.hpp"
#include "Utility.hpp"
#include <SDL2/SDL_render.h>


class Character : public Entity {
private:
    int secondBar; //mana, rabbia o altre cose in base al personaggio effettivo
    int initialX;
    int initialY;
    int framesSpentMoving;
    Sound** sounds;
    //AnimationStats 
public:
    Character(int x, int y, int width, int height, SDL_Texture *spritesheet, SDL_Texture *overlinedSpritesheet, Vector2 spriteSize, Sound **sounds);
    void update();
    void render(SDL_Renderer *render);
    void renderOverline(SDL_Renderer * renderer);
    void setSecondBar(int value);
    int getSecondBar();
};
#endif