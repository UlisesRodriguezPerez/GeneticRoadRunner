#include <iostream>
// #include <unordered_map>
#include <fstream>
// #include <string>
#include <nlohmann/json.hpp>
// #include <list>

using json = nlohmann::json;
using namespace std;

#include "genetic/GeneticRoadRunner.h"
#include "genetic/Individual.h"

json readJsonFile(string archivo){
    std::ifstream jsonFile(archivo);
    json Json;
    jsonFile >> Json;

    return Json;
}

string readTxt(string filename){
    std::ifstream file(filename);
    string pointsTrack;
    string s;
    while(file >> s){
        pointsTrack += s;
    }
    return pointsTrack;
}

bool searchInHashTrack(string pKey){
    auto result = allTrackPoints.find(pKey);
    if(result != allTrackPoints.end()){
        cout<<"SÏ EXISTE";
        return true;
    }
    else{
        return false;
    }
}

int main(void){
    srand(time(NULL));
    GeneticRoadRunner running;
    running.running();

return 0;
}