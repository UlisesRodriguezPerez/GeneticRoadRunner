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
        // cout<<"0"<<endl;
        createPopulation();
        // cout<<population.front().listOfPoints.front().first<<endl;
        // fitness();
        int currentGeneration = 0;

        while(currentGeneration < this->numberGeneations){  //REVISAR colocar el parametro de public, por ahora así.
            cout<<"\n\nGeneracion: "<<currentGeneration+1<<endl;
            // cout<<"1"<<endl;
            fitness();
            // cout<<"2"<<endl;
            selectPopulation();
            // cout<<"Population despues de select: "<<population.size()<<endl;
            // cout<<"3"<<endl;
            fillPopulation();
            // cout<<"4"<<endl;
            currentGeneration ++;
            
            
        }     
        cout<<"The program is finished."<<endl;   
        // cout<<individual.front().first<<"INDIVIF¡DUO"<<endl;
                
    }

    void fillPopulation(){
        
        int newIndividuals =  initialPopulation - population.size();
        
        int zonesSize = population.front().listOfPoints.size(); //REVISAR tiene 11 y son 8.
        // cout<<"zone.size: "<<zonesSize<<endl;
        using pointMutate = std::pair<int, int>;int newIndividualCounter = 0;
        while(newIndividualCounter < newIndividuals){   //REVISAR no se si es < o <= queda pendiente.
            int firstIndividual = newRandom(population.size());
            int secondIndividual = newRandom(population.size());

            Individual individualFather = population[firstIndividual]; 
            Individual individualMother = population[secondIndividual]; //Jeje.

            pointZone point = individualFather.listOfPoints[0];

            using pointZoneTemp = std::pair<int, int>;
            using individualTemp = std::vector<pointZoneTemp>;

            individualTemp newListPoints;
            for(int counterZones = 0; counterZones < zonesSize; counterZones++){
                pointZoneTemp point;
                pointZone pointX1 = individualFather.listOfPoints[counterZones];
                pointZone pointY1 = individualFather.listOfPoints[counterZones];

                pointZone pointX2 = individualMother.listOfPoints[counterZones];
                pointZone pointY2 = individualMother.listOfPoints[counterZones];
                point = crossover(pointX1.first,pointY1.second,pointX2.first,pointY2.second);     //REVISAR cambiar por nombre significativo.
                newListPoints.push_back(point);
            }
            int randomMutate = newRandom(MAX_MUTATE_RANGE);
            int circleRange = (individualMother.circleRadius + individualFather.circleRadius)/PROM;
            if(randomMutate <= PORCENTAGE_MUTATE){
                int indexRange = newRandom(zonesSize);
                
                pointZone mutatedPoint = newListPoints[indexRange];
                mutatedPoint = mutate(mutatedPoint, indexRange,circleRange);
                newListPoints[indexRange] = mutatedPoint;
            }
            Individual newIndividual;
            float distance = 0;
            using pointZonePerDistane = std::pair<int, int>;int initialX = X_INITIAL;int initialY=Y_INITIAL;
            for(int counterListPoints = 0; counterListPoints < newListPoints.size();counterListPoints++){
                // cout<<"Size de newListPoints"<<newListPoints.size()<<endl;
                pointZonePerDistane point2 = newListPoints[counterListPoints];int X2=point2.first;int Y2=point2.second;
                distance += (distanceBetweenPointPerCrossover(initialX,initialY,X2,Y2)*PROM);
                initialX=X2,initialY=Y2;
            }
            // cout<<"\nDISTANCE"<<distance<<endl;
            // std::vector<pair<int,int>::iterator individualIterator;
            // for(individualIterator = this->newLis.begin(); individualIterator != this->population.end(); individualIterator++){
            newIndividual.circleRadius = circleRange;newIndividual.distance = distance;newIndividual.fitness=0;
            newIndividual.listOfPoints = newListPoints;newIndividual.pointsZones=individualFather.pointsZones;
            population.push_back(newIndividual);
            newIndividualCounter++;
        }
    }
    

    pair<int,int> mutate(pair<int,int> mutatedPoint, int indexRange, int circuleDiameter){
        using pointMutate = std::pair<int, int>;
        pointMutate point;
        int minX= mutatedPoint.first-(circuleDiameter/PROM);int minY=mutatedPoint.second-(circuleDiameter/PROM);
        point.first = newRandomForMutate(minX,circuleDiameter);
        point.second = newRandomForMutate(minY,circuleDiameter);
        return point;

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
        int poblationToEliminate = population.size() * POCENTAGE_TO_ELIMINATE; 
        sort(population.begin(),population.end(),[&] (Individual individualA, Individual individualB){ return individualA.fitness < individualB.fitness;});
        int counterPerEliminate = 0;
        while(counterPerEliminate < poblationToEliminate){
            population.erase(population.begin()); 
            counterPerEliminate ++;
        }
        Individual bestIndividual = population.back();
        cout<<"Best Individual in this Generation: \n"<<"\tDistacia total, al llegar a la meta: "<<bestIndividual.distance<<
        "\n\tFitness del mejor Individuo: "<<bestIndividual.fitness<<"\n\tTamaño del diametro de cada zona del Individuo: "<<bestIndividual.circleRadius<<endl;
    }

    int newRandomForMutate(int min, int max){
        int module = max - min;if(module==0){module=1;}
        int value = min + rand() % module;
        return value;
    }

    int newRandom( int max){
        if(max==0){max=1;}
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
        // cout<<"population size: "<<population.size()<<endl;
        for (individualIterator = this->population.begin(); individualIterator != this->population.end(); individualIterator++){
            float fitnessScore = 0.0;
            std::vector<Individual>::iterator sumOfDiferences;

            for(sumOfDiferences = this->population.begin(); sumOfDiferences != this->population.end(); sumOfDiferences++){
                fitnessScore += sumOfDiferences->distance - individualIterator->distance;
                
            }
            
        individualIterator->fitness = fitnessScore;
        // cout<<"Fitness: "<<individualIterator->fitness<<endl;
        }       
    }

    // void distanceNewIndividual(){
            
    //     float individualSum = 0.0; int initialX = X_INITIAL; int initialY = Y_INITIAL; //initial = punto inicial del bichillo, mientras va avanzando entre segmentos.
    //     float y;float x; float b; float m; 
    //     // pointsZones = {{265,146},{317,791},{754,772},{787,108},{936,107},{1076,748},{1534,700},{1801,126}};
    //     for(int counterZones = 0; counterZones < pointsZones.size(); counterZones++){
            
            
    //         int xPosition = pointsZones[counterZones][X];    //Revisar Cambiar por una constante X
    //         int yPosition = pointsZones[counterZones][Y];
            
    //         std::pair<int, int> newPoint;

    //         newPoint.first = pointUbication(xPosition, circuleRange);
            
    //         newPoint.second = pointUbication(yPosition, circuleRange);
            
    //         // this->x = newPoint.first; this->y = newPoint.second;
    //         xPosition = newPoint.first; yPosition = newPoint.second;

    //         m = slopeFuntion(initialX,initialY,xPosition,yPosition);
    //         b = initialY - (m * initialX); // y = (m*x) + b;
            
    //         int xRange = xPosition - initialX;
    //         float auxSum = isNiceLine(initialX,m,b,xRange);
    //         float distance = distanceBetweenPoints(initialX,initialY,xPosition,yPosition);
            
    //         individualSum += auxSum; individualSum += distance;

    //         listOfPoints.push_back(newPoint);
    //         initialX = xPosition; initialY = yPosition;
            
    //     // cout<<individualSum<<endl;
    //     //  xPosition = newPoint.first; yPosition = newPoint.second;
    //     this->distance = individualSum;
        
    //     }
    // }

    void createPopulation(){
        for( int counterOfIndividual = 0; counterOfIndividual < initialPopulation; counterOfIndividual++){
            Individual individual;
            // cout<<counterOfIndividual<<endl;
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
        // cout<<x1<<"\t"<<x2<<"\t"<<y1<<"\t"<<y2<<endl;
        float auxNumber = ((x2 - x1)*(x2 - x1 ) + (y2 - y1)*(y2 - y1));if(auxNumber<0){auxNumber=0;}
        float distance = sqrt(auxNumber);
        // float distance = sqrt((5 - 4)*(5 - 4 ) + (12 - 8)*(12 - 8));
        // cout<<"distancia: "<<distance<<endl;
        return (distance / 2);
        }
    float slopeFuntionCrossover(int X1, int Y1,int X2, int Y2){    // Pendiente de la función.
        int auxNumber = X2-X1;if(auxNumber==0){auxNumber=1;}
        float m = (Y2-Y1)/auxNumber;
        return m;
    }
};
#endif //GENETICROADRUNNER_H