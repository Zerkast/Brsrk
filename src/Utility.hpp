#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <vector>
#include <string>

using namespace std;

typedef struct {
    int x;
    int y;
} Vector2; //magari lo sposto poi in un datatypes.h o comunque header apposta insieme ad altri tipi utili

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} Box;

vector<string> split(string stringToSplit, char delimiter);

int parseInt(string inputString);

bool isNumber(string inputString); //non parsa numeri negativi

#endif