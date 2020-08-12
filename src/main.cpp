#include <iostream>

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;



json readJsonFile(string archivo){
    std::ifstream jsonFile(archivo);
    json Json;
    jsonFile >> Json;
    return Json;
}

int main(){
    string archivo = "../data/inputParedArriba.json";
    json newJson = readJsonFile(archivo);
    cout<<newJson.dump();

}