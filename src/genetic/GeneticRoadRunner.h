#ifndef GENETICROADRUNNER_H
#define GENETICROADRUNNER_H

#include <vector>
#include <math.h>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <algorithm>

#include "Individual.h"

class GeneticRoadRunner{

    // using namespace std;

    public:
        friend class Individual;
        int initialPopulation = INITIAL_POPULATION;
        int numberGeneations = NUMBER_GENERATION;
        std::vector<Individual> population;
        using pointZone = std::pair<int, int>;
        using individual = std::vector<pointZone>;
        

    void running(){
        
        // initializeHashTrack();
        createPopulation();
        // cout<<population.front().listOfPoints.front().first<<endl;
        fitness();
        int currentGeneration = 0;
        while(currentGeneration < this->numberGeneations){  //REVISAR colocar el parametro de public, por ahora así.
            fitness();
            selectPopulation();
            fillPopulation();
            currentGeneration ++;

        }        
        // cout<<individual.front().first<<"INDIVIF¡DUO"<<endl;
                
    }

    void fillPopulation(){
        // cout<<"1"<<endl;
        int newIndividualsCounter =  initialPopulation - population.size();
        int zonesSize = population.front().listOfPoints.size();
        cout<<"size: "<<zonesSize<<endl;
        while(newIndividualsCounter < initialPopulation){   //REVISAR no se si es < o <= queda pendiente.
            int firstIndividual = newRandom(population.size());
            int secondIndividual = newRandom(population.size());

            Individual individualFather = population[firstIndividual]; 
            Individual individualMother = population[secondIndividual]; //Jeje.
            pointZone point = individualFather.listOfPoints[0];
            using pointZoneTemp = std::pair<int, int>;
            using individualTemp = std::vector<pointZoneTemp>;
            individualTemp newListPoints;
            for(int counterZones = 0; counterZones <= zonesSize; counterZones++){
                pointZoneTemp point;
                pointZone pointX1 = individualFather.listOfPoints[counterZones];
                pointZone pointY1 = individualFather.listOfPoints[counterZones];

                pointZone pointX2 = individualMother.listOfPoints[counterZones];
                pointZone pointY2 = individualMother.listOfPoints[counterZones];
                point = crossover(pointX1.first,pointY1.second,pointX2.first,pointY2.second);     //REVISAR cambiar por nombre significativo.
                newListPoints.push_back(point);
            }
            newIndividualsCounter++;
            cout<<"bkjbjlb"<<newIndividualsCounter<<endl;
        }
    }

    pair<int,int> crossover(int x1,int y1, int x2,int y2){
        int y;int x; float b; float m; 
        using point = std::pair<int, int>;
        point newPoint; 
        float distance = distanceBetweenPointPerCrossover(x1,y1,x2,y2);
        m = slopeFuntionCrossover(x1,y1,x2,y2);
        b = y1 - (m * x1); // y = (m*x) + b;
        x = (x1+x2)/2;
        y = (y1+y2)/2;
        int minX = x1;if(x2 < x1){minX = x2;}
        int minY = y1;if(y2 < y1){minY = y2;}
        // y = m*x+b;
        newPoint.first = minX + newRandom(abs(x2-x1));
        newPoint.second = minY + newRandom(abs(y2-y1));
            
        return newPoint;
    }

    void selectPopulation(){
        int poblationToEliminate = initialPopulation * POCENTAGE_TO_ELIMINATE; 
        sort(population.begin(),population.end(),[&] (Individual individualA, Individual individualB){ return individualA.fitness < individualB.fitness;});
        int counterPerEliminate = 0;
        while(counterPerEliminate < poblationToEliminate){
            population.erase(population.begin()); 
            counterPerEliminate ++;
        }
    }

    int newRandomForCrossover(int min, int max){
        int module = max - min;
        int value = min + rand() % module;
        return value;
    }

    int newRandom( int max){
        // int module = max - min;
        int value = rand() % max;
        return value;
    }

    bool miComparacion(int num1, int num2) {
        if (num1 < num2) {
            return false;
        } else {
            return true;
        }
    }

                    //population -> [ [{x,y},{x,y}], [  {x,y}] ]
    void fitness(){
        std::vector<Individual>::iterator individualIterator;
        for (individualIterator = this->population.begin(); individualIterator != this->population.end(); individualIterator++){
            float fitnessScore = 0.0;
            std::vector<Individual>::iterator sumOfDiferences;
            // cout<<individualIterator->distance<<endl;
            for(sumOfDiferences = this->population.begin(); sumOfDiferences != this->population.end(); sumOfDiferences++){
                fitnessScore += sumOfDiferences->distance - individualIterator->distance;
            }
        individualIterator->fitness = fitnessScore;
        // cout<<"Fitness: "<<individualIterator->fitness<<endl;
        }
            
    }
    void createPopulation(){
        for( int counterOfIndividual = 0; counterOfIndividual < initialPopulation; counterOfIndividual++){
            Individual individual;
            
            population.push_back(individual);
        }

    }

    // bool searchInHashTrack(string pKey){
    //     auto result = this->allTrackPoints.find(pKey);
    //     if(result != this->allTrackPoints.end()){
    //         cout<<"SÏ EXISTE";
    //         return true;
    //     }
    //     else{
    //         return false;
    //     }
    // }

    float distanceBetweenPointPerCrossover(int x1,int y1, int x2, int y2){
            float distance = sqrt((x2 - x1)*(x2 - x1 ) + (y2 - y1)*(y2 - y1));
            // float distance = sqrt((5 - 4)*(5 - 4 ) + (12 - 8)*(12 - 8));
            // cout<<"distancia: "<<distance<<endl;
            return (distance / 2);
        }
    float slopeFuntionCrossover(int X1, int Y1,int X2, int Y2){    // Pendiente de la función.
        float m = (Y2-Y1)/(X2-X1);
        return m;
    }
};
#endif //GENETICROADRUNNER_H