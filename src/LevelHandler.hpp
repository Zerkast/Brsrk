#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Utility.hpp"
#include <SDL2/SDL_render.h>

class LevelHandler {
private:
    /*
    volendo si potrebbe invece memorizzare un array con le texture che rappresentano l'intera mappa; tuttavia potrebbe occupare troppo memoria in caso di scenari con sprite animati, 
    ma potrebbero esserci poi problemi con le animazioni di questi ultimi se hanno numeri diversi di frame per le animazioni in questione
    */
    Vector2 tilesizeOnScreen;
    int ***tilemaps;
    unsigned int layersNum;
    unsigned int tilemapsWidth;
    unsigned int tilemapsHeight;
    int *spritesheetsToUse;
    unsigned int spritesheetsNum;
    SDL_Texture **spritesheets;
    Vector2 *spritesheetsSizes;
    Vector2 *staticCollisions;
    unsigned int staticCollisionsNum;
    Vector2 *triggers;
    unsigned int triggersNum;
    Vector2 currentOffset;
    int scaler;
    unsigned int collisionLayer;
    Vector2 collisionSize;
    //unsigned int triggerLayer
    //AnimationStats 
public:
    LevelHandler(const char *filepath, SDL_Renderer *renderer);
    bool checkCollision(int x, int y);
    int checkTriggers(int currentX, int currentY);
    void setCurrentOffsetX(int x);
    void setCurrentOffsetY(int y);
    void render(SDL_Renderer *renderer);
    void renderLayer(SDL_Renderer *renderer, int i);
    void setScaler(int value); //con il float potrebbero esserci errori di approssimazione, ma va presso in considerazione
};
#endif