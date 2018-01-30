#include <vector>
#include <stdio.h>
#include <cmath>
#include <sys/time.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "estimator.cpp"
#include "eomlee.cpp"
#include "lowerBound.cpp"
#include "dsMap.cpp"
#include "simulator.cpp"

using namespace std;

void export_csv(string path, vector<Simulator> &simulators, int id){
  ofstream file;
  file.open(path);
  for(int k = 0; k < simulators[0].getSize(); k++){
    file << simulators[0].getLabel()[k];
    for(int j = 0; j < simulators.size(); j++){
      file << ", " << simulators[j].getResult()[k][id];
    }
    file << "\n";
  }
  file.close();
}

void export_flow(string path, vector<Simulator> simulators){
  ofstream file;
  file.open(path);
  for(int k = 0; k < simulators[0].getSize(); k++){
    file << simulators[0].getLabel()[k];
    for(int j = 0; j < simulators.size(); j++){
      file << ", " << simulators[j].getFlow()[k];
    }
    file << "\n";
  }
  file.close();
}

int main(){
  srand(time(NULL));
  int tagMin, tagMax, tagStep, slots, repetitions;
  printf("Enter starting number of tags, tag step, maximum number of tags, initial number of slots and number of repetitions\n");
  scanf("%d %d %d %d %d", &tagMin, &tagStep, &tagMax, &slots, &repetitions);
  printf("\n -- Configuration Entered --\n");
  printf("Starting number of tags: %d", tagMin);
  printf("\nTag step: %d", tagStep);
  printf("\nMaximum number of tags: %d", tagMax);
  printf("\nStarting number of slot: %d", slots);
  printf("\nNumber of repetitions: %d\n", repetitions);

  vector<Estimator*> estimators;
  LowerBound lowerBound;
  EomLee eomLee;
  DsMap dsMap;

  estimators.push_back(&lowerBound);
  estimators.push_back(&eomLee);
  estimators.push_back(&dsMap);

  vector<Simulator> simulators;

  for(int i = 0; i < estimators.size(); i++){
    simulators.push_back(Simulator(tagMin, tagMax, tagStep, repetitions, slots, estimators[i]));
    simulators[i].run();
  }

  export_csv("output/slots.csv", simulators, 0);
  export_csv("output/empties.csv", simulators, 1);
  export_csv("output/collisions.csv", simulators, 2);
  export_csv("output/time.csv", simulators, 3);
  export_flow("output/flow.csv", simulators);

  return 0;
}
