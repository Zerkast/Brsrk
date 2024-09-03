#include "Utility.hpp"
#include <vector>
#include <string>

using namespace std;

vector<string> split(string stringToSplit, char delimiter) {
    vector<string> result;
    int startIndex = 0;
    for (int i = 0; i<stringToSplit.size(); i++) {
        if (stringToSplit[i]==delimiter) {
            result.push_back(stringToSplit.substr(startIndex, i));
            startIndex=i+1;
        }
    }
    result.push_back(stringToSplit.substr(startIndex, stringToSplit.size()));
    return result;
}

int parseInt(string inputString) {
    int result = 0;
    string::const_iterator it = inputString.begin();
    for (int i = 0; i < inputString.size(); i++) {
        result*=10;
        result+=inputString[i]-48;
    }
    isdigit(*it);
    return result;
}

bool isNumber(string inputString) { //non parsa numeri negativi
    string::const_iterator it = inputString.begin();
    while (it != inputString.end() && isdigit(*it)) it++;
    return !inputString.empty() && it == inputString.end();
}
