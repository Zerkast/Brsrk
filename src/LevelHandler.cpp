#include "LevelHandler.hpp"
#include "Spritesheets.hpp"
#include "UIRenderer.hpp"
#include "Utility.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

    LevelHandler::LevelHandler(const char *filepath, SDL_Renderer *renderer) { 
        std::ifstream levelFile;
        std::string line;
        levelFile.open(filepath);
        std::getline(levelFile, line);
        currentOffset.x = 0;
        currentOffset.y = 0;
        spritesheetsNum = parseInt(line);
        spritesheets = new SDL_Texture*[spritesheetsNum];
        spritesheetsSizes = new Vector2[spritesheetsNum];
        int index = 0;
        if (levelFile.is_open()) {
            while (std::getline(levelFile, line) && line != "\n" && line != "") {
                string path = "res/"+line;
                spritesheets[index] = IMG_LoadTexture(renderer, path.c_str());
                spritesheetsSizes[index] = Spritesheets::spritesheets.at(line);
                if (spritesheets[index]==NULL) {
                    printf("Error loading spritesheet: %s", path.c_str());
                }
                index++;
            }
            std::getline(levelFile, line);
            layersNum = parseInt(line);
            tilemaps = new int**[layersNum];
            spritesheetsToUse = new int[layersNum];
            std::getline(levelFile, line);
            vector<string> sizes = split(line,';'); 
            tilemapsWidth = parseInt(sizes[0]);
            tilemapsHeight = parseInt(sizes[1]);
            for (int i = 0; i < layersNum; i++) {
                tilemaps[i] = new int*[tilemapsHeight];
                for (int j = 0; j < tilemapsHeight; j++) {
                    tilemaps[i][j] = new int[tilemapsWidth];
                }
            }
            int currentLayer = 0;
            while (std::getline(levelFile, line) && line != "") {
                printf("Loading tilemap layer num: %d\n", currentLayer);
                std::getline(levelFile, line);
                spritesheetsToUse[currentLayer] = parseInt(line);
                int row = 0;
                while (std::getline(levelFile, line) && line != "") {
                    for (int col = 0; col < line.size(); col++) {
                        tilemaps[currentLayer][row][col] = line[col]-65;
                        printf("%d", line[col]-65);
                    }
                    printf("\n");
                    row++;
                }
                currentLayer++;
            }
            std::getline(levelFile, line);
            staticCollisionsNum = parseInt(line);
            staticCollisions = new Vector2[staticCollisionsNum];
            std::getline(levelFile, line);
            collisionSize.x = parseInt(split(line, ';')[0]);
            collisionSize.y = parseInt(split(line, ';')[1]);
            printf("Loading collision size: %d;%d", collisionSize.x, collisionSize.y);
            int currentCollision = 0;
            while (std::getline(levelFile, line) && line!="\n" && line != "") { //questo metodo di prendere le collisioni fa un po' cagare, ma per ora non mi viene in mento altro di migliore, per ora basta che funzioni
                int y = parseInt(split(line, ';')[1]);
                int x = parseInt(split(line, ';')[0]);
                printf("Loading collision at (%d;%d)\n", y, x);
                staticCollisions[currentCollision] = {x, y};
                currentCollision++;
            }
            std::getline(levelFile, line);
            triggersNum = parseInt(line);
            triggers = new Vector2[triggersNum];
            int currentTrigger = 0;
            while (std::getline(levelFile, line) && line!="\n" && line != "") { //questo metodo di prendere le collisioni fa un po' cagare, ma per ora non mi viene in mento altro di migliore, per ora basta che funzioni
                int y = parseInt(split(line, ';')[1]);
                int x = parseInt(split(line, ';')[0]);
                printf("Loading trigger at (%d;%d)\n", y, x);
                triggers[currentTrigger] = {x, y};
                currentTrigger++;
            }

        } else {
            printf("Error opening level file: %s", filepath);
        }
    }
    bool LevelHandler::checkCollision(int x, int y) {
        printf("Current player position: %d:%d\n", x, y);
        for (int i = 0; i < staticCollisionsNum; i++) {
            printf("Current collision: %d-%d\n", staticCollisions[i].x*spritesheetsSizes[0].x, staticCollisions[i].y*spritesheetsSizes[0].y);
            printf("Current collision tile: %d-%d\n", staticCollisions[i].x, staticCollisions[i].y);
            if (x >= staticCollisions[i].x*spritesheetsSizes[0].x&& x<=(staticCollisions[i].x*spritesheetsSizes[0].x+collisionSize.x) &&
                y >= staticCollisions[i].y*spritesheetsSizes[0].y&& y<=(staticCollisions[i].y*spritesheetsSizes[0].y+collisionSize.y)) { //fai la modifica per controllare dal basso verso l'alto e non viceversa
                return false; //poi farò un Vector3, così che ogni trigger sia collegato al numero di evento corretto
            }
        }
        return true;
    }
    int LevelHandler::checkTriggers(int x, int y) { //restituisce poi il numero dell'evento
        for (int i = 0; i < triggersNum; i++) {
            if (x >= triggers[i].x*spritesheetsSizes[0].x && x<=(triggers[i].x+1)*spritesheetsSizes[0].x &&
                y >= triggers[i].y*spritesheetsSizes[0].y && y<=(triggers[i].y+1)*spritesheetsSizes[0].y) { 
                return 4; //poi farò un Vector3, così che ogni trigger sia collegato al numero di evento corretto
            }
        }
        return -1;
    }
    void LevelHandler::setCurrentOffsetX(int x) {
        currentOffset.x=x;
    }
    void LevelHandler::setCurrentOffsetY(int y) {
        currentOffset.y=y;
    }
    void LevelHandler::render(SDL_Renderer *renderer) {
        for (int i = 0; i < layersNum; i++) {
            int currentSpritesheetInUse = spritesheetsToUse[i];
            for (int row = 0; row < tilemapsHeight; row++) {
                for (int col = 0; col < tilemapsWidth; col++) {
                    if (tilemaps[i][row][col]!=-2) { //al posto di creare nuovi rect ogni volta, potrei farne uno solo e aggiornare le sue coordinate (e dimensioni in base al layer)
                        SDL_Rect dstRect = {col*spritesheetsSizes[0].x*scaler-currentOffset.x*scaler, (row*spritesheetsSizes[0].y-(spritesheetsSizes[currentSpritesheetInUse].y-spritesheetsSizes[0].y))*scaler-currentOffset.y*scaler, spritesheetsSizes[currentSpritesheetInUse].x*scaler, spritesheetsSizes[currentSpritesheetInUse].y*scaler};
                        SDL_Rect srcRect = {tilemaps[i][row][col]*spritesheetsSizes[currentSpritesheetInUse].x, 0, spritesheetsSizes[currentSpritesheetInUse].x, spritesheetsSizes[currentSpritesheetInUse].y};
                        SDL_RenderCopy(renderer, spritesheets[currentSpritesheetInUse], &srcRect, &dstRect);
                    }
                }
            }
        } 
    }
    
    void LevelHandler::renderLayer(SDL_Renderer *renderer, int i) {
        int currentSpritesheetInUse = spritesheetsToUse[i];
        for (int row = 0; row < tilemapsHeight; row++) {
            for (int col = 0; col < tilemapsWidth; col++) {
                if (tilemaps[i][row][col]!=-2) { //al posto di creare nuovi rect ogni volta, potrei farne uno solo e aggiornare le sue coordinate (e dimensioni in base al layer)
                    SDL_Rect dstRect = {col*spritesheetsSizes[0].x*scaler-currentOffset.x*scaler, (row*spritesheetsSizes[0].y-(spritesheetsSizes[currentSpritesheetInUse].y-spritesheetsSizes[0].y))*scaler-currentOffset.y*scaler, spritesheetsSizes[currentSpritesheetInUse].x*scaler, spritesheetsSizes[currentSpritesheetInUse].y*scaler};
                    SDL_Rect srcRect = {tilemaps[i][row][col]*spritesheetsSizes[currentSpritesheetInUse].x, 0, spritesheetsSizes[currentSpritesheetInUse].x, spritesheetsSizes[currentSpritesheetInUse].y};
                    SDL_RenderCopy(renderer, spritesheets[currentSpritesheetInUse], &srcRect, &dstRect);
                }
            }
        }
    }



    void LevelHandler::setScaler(int value) {
        scaler = value;
    }