#include <unordered_map>

void readJsonInput(){
    std::ifstream file_input("data/inputParedArriba.json");
    Json::Reader reader;
    Json::Value root;
    reader.parse(file_input, root);
    cout << root;
}





// void WordGraphRelation::addVertexGraph(Vertex *pVertex){
//     vertexMap.insert(std::make_pair(pVertex->word, pVertex));
// }


// void WordGraphRelation::testMap(){
//     cout<<vertexMap.size()<<endl;
// }
// auxiliarVertex = vertexMap[pWord];