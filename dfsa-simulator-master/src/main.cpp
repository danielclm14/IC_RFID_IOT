#include <vector>
#include <stdio.h>
//#include <stdlib.h>
#include <cmath>
#include <sys/time.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
// #include "estimator.cpp"
// #include "eomlee.cpp"
// #include "lowerBound.cpp"
// #include "dsMap.cpp"
//#include "FEIA.cpp"
// #include "CHEN.cpp"
// #include "simulator.cpp"
// #include "QALGORITHM.cpp"

using namespace std;

typedef struct Tags{
  int RandNum;
  struct Tags* next;
}tags;

void insert(tags* tag, int slots)
{
  tags* aux;
  aux = (tags*) malloc (sizeof(tags));
  aux->RandNum = rand()%slots;
  aux->next = tag->next;
  tag->next = aux;
}

void Query (tags* tag, int numTags)
{
  while (numTags)
  {
    numTags -- ;
    insert(tag, 15);
  }
}

void QueryAdjust (tags* tag)
{
  tags* aux = tag;
  while (aux != NULL)
  {
    aux->RandNum --;
    aux = aux->next;
  }
}

void QueryRep (tags* tag, int Q)
{
  int slots = pow(2,Q) - 1;
  tags* aux = tag;
  while (aux != NULL)
  {
    aux->RandNum = rand()%slots;
    aux = aux->next;
  }
}

void TagRemov (tags* tag)
{
  tags* aux, *aux2;
  aux = tag;
  aux2 = tag->next;
  while (aux2 != NULL && aux2->RandNum != 0)
  {
    aux = aux2;
    aux2 = aux2->next;
  }
  if (aux2 != NULL)
  {
    aux->next = aux2->next;
    free(aux2);
  }
}

int Qverify (int remaining)
{

  if (remaining == 1)
  {
    return 0;
  }
  else if (remaining <= 2)
  {
    return 1;
  }
  else if (remaining <= 4)
  {
    return 2;
  }
  else if (remaining <= 8)
  {
    return 3;
  }
  else if (remaining <= 16)
  {
    return 4;
  }
  else if (remaining <= 32)
  {
    return 5;
  }
  else if (remaining <= 64)
  {
    return 6;
  }
  else if (remaining <= 128)
  {
    return 7;
  }
  else if (remaining <= 256)
  {
    return 8;
  }
  else if (remaining <= 512)
  {
    return 9;
  }

  return 10; 
}

void QueryO (tags* tag, int numTags)
{
  while (numTags)
  {
    numTags -- ;
    insert(tag, numTags - 1);
  }
}

// void export_csv(string path, vector<Simulator> &simulators, int id){
//   ofstream file;
//   file.open(path);
//   for(int k = 0; k < simulators[0].getSize(); k++){
//     file << simulators[0].getLabel()[k];
//     for(int j = 0; j < simulators.size(); j++){
//       file << ", " << simulators[j].getResult()[k][id];
//     }
//     file << "\n";
//   }
//   file.close();
// }

// void export_flow(string path, vector<Simulator> simulators){
//   ofstream file;
//   file.open(path);
//   for(int k = 0; k < simulators[0].getSize(); k++){
//     file << simulators[0].getLabel()[k];
//     for(int j = 0; j < simulators.size(); j++){
//       file << ", " << simulators[j].getFlow()[k];
//     }
//     file << "\n";
//   }
//   file.close();
// }

// void export_Efficiency(string path, vector<Simulator> simulators){
//   ofstream file;
//   file.open(path);
//   for(int k = 0; k < simulators[0].getSize(); k++){
//     file << simulators[0].getLabel()[k];
//     for(int j = 0; j < simulators.size(); j++){
//       file << ", " << simulators[j].getEfficiency()[k];
//     }
//     file << "\n";
//   }
//   file.close();
// }

void runQ(int tagMin, int tagMax, int tagStep, int repetitions, int slotes){
  ofstream fileS;
  fileS.open("output/QSlots.csv");
  ofstream fileC;
  fileC.open("output/QCollision.csv");
  ofstream fileM;
  fileM.open("output/Qempities.csv");
  ofstream fileT;
  fileT.open("output/QTime.csv");
  ofstream fileE;
  fileE.open("output/Qefficience.csv");
  ofstream DebugF;
  DebugF.open("output/DebugF.txt");

  long double CqC = 0.2, CqE = 0.1;
  int Q = 0;
  int auxi = 0;
  long double Qfp = 0;
  DebugF << " Debug 2: Q = " << Q << ", Qfp = " << Qfp << "\n";
  for(int tagz = tagMin; tagz <= tagMax; tagz += tagStep){
    // labels[size] = tags;
    if (auxi == 1)
    {
      fileS << "\n";
      fileM << "\n";
      fileT << "\n";
      fileC << "\n";
      fileE << "\n";
    }
    auxi = 1;
    fileS << tagz;
    fileM << tagz;
    fileT << tagz;
    fileE << tagz;
    fileC << tagz;
    long double collisionsMean = 0;
    long double emptiesMean = 0;
    long double slotsMean = 0;
    long double timeMean = 0;
    long double flowMean = 0;
    long double efficiency = 0;
    for(int i = 0; i < repetitions; i++){
      //Q = Qverify(tagz);
      //Qfp = Qverify(tagz);
      Q = 4;
      Qfp = 4;
      int totalSlots = 0;
      int sucessSlots = 0;
      int collision = 0;
      int emptie = 0; 
      timeval start, end;
      gettimeofday(&start, 0);
      tags* tag, *aux;
      tag = (tags*) malloc (sizeof(tags));
      Query(tag, tagz);
      while(tag->next != NULL)
      {
        int sendFlag = 0;
        for(aux = tag->next; aux != NULL; aux = aux->next)
        {
          if(aux->RandNum == 0)
          {
            sendFlag = sendFlag + 1;
          } 
        }
        if (sendFlag == 1)
        {
          sucessSlots = sucessSlots + 1;
          TagRemov(tag);
          QueryAdjust(tag);
        }
        else if(sendFlag > 1)
        {
          collision = collision + 1;
          Qfp = Qfp + CqC;
          if( Qfp >= (Q+1) )
          {
            if( Qfp <= 15 )
            {
              Q = Qfp;
            }
            else
            {
              // DebugF << " Debug 4: Q = " << Q << ", Qfp = " << Qfp << "\n";
              Q = 15;
            }
            //DebugF << " Debug 5: Q = " << Q << ", Qfp = " << Qfp << "\n";
          }
          else if ( Qfp <= Q-1 )
          {
            if( Qfp > 0)
            {
              Q = Qfp;
            }
            else
            {
              Q = 1;
            }
          }
          QueryRep(tag, Q);
          //DebugF << " Debug 4: Q = " << Q << ", Qfp = " << Qfp << "\n";
        }
        else 
        {
          Qfp = Qfp - CqE;
          emptie = emptie + 1;
          QueryAdjust(tag);
          if( Qfp >= (Q+1) )
          {
            if( Qfp <= 15 )
            {
              Q = Qfp;
              QueryRep(tag, Q);
            }
            else
            {
              // DebugF << " Debug 4: Q = " << Q << ", Qfp = " << Qfp << "\n";
              Q = 15;
            }
            //DebugF << " Debug 4: Q = " << Q << ", Qfp = " << Qfp << "\n";
          }
          else if ( Qfp <= Q-1 )
          {
            if( Qfp > 0)
            {
              Q = Qfp;
              QueryRep(tag, Q);
            }
            else
            {
              Q = 1;
            }
            //DebugF << " Debug 4: Q = " << Q << ", Qfp = " << Qfp << "\n";
          }
        }
        DebugF << " Debug tester: Q = " << Q << ", Qfp = " << Qfp << "\n";
      }
      gettimeofday(&end, 0);
      int elapsed = (((end.tv_sec - start.tv_sec)*1000000L+end.tv_usec) - start.tv_usec);
      timeMean += elapsed;
      totalSlots += sucessSlots + collision + emptie;
      slotsMean += totalSlots;
      emptiesMean += emptie;
      collisionsMean += collision;
      flowMean += sucessSlots/(double)totalSlots;
      efficiency += tagz/(double)totalSlots;
    }
    // printf(" Debug 0: Q = %lf, Qfp = %lf \n ", Q, Qfp);
    DebugF << " Debug 0: Q = " << Q << ", Qfp = " << Qfp << "\n";
    // results[size].push_back(ceil(slotsMean/(double)repetitions));
    fileS << ", " << ceil(slotsMean/(double)repetitions);
    // results[size].push_back(ceil(emptiesMean/(double)repetitions));
    fileM << ", " << ceil(emptiesMean/(double)repetitions);
    // results[size].push_back(ceil(collisionsMean/(double)repetitions));
    fileC << ", " << ceil(collisionsMean/(double)repetitions);
    // results[size].push_back(ceil(timeMean/(double)repetitions));
    fileT << ", " << ceil(timeMean/(double)repetitions);
    // Efficiency.push_back(efficiency/(double)repetitions);
    fileE << ", " << efficiency/(double)repetitions;
    // flow.push_back(flowMean/(double)repetitions);
  }
  fileS.close();
  fileM.close();
  fileC.close();
  fileT.close();
  fileE.close();
  DebugF.close();
}

// void runQ2(int tagMin, int tagMax, int tagStep, int repetitions, int slotes){
//   ofstream fileS;
//   fileS.open("output/QSlots2.csv");
//   ofstream fileC;
//   fileC.open("output/QCollision2.csv");
//   ofstream fileM;
//   fileM.open("output/Qempities2.csv");
//   ofstream fileT;
//   fileT.open("output/QTime2.csv");
//   ofstream fileE;
//   fileE.open("output/Qefficience2.csv");
//   ofstream DebugF;
//   DebugF.open("output/DebugF2.txt");

//   int Q = 0;
//   long double leaux = 0;
//   int auxi = 0;
//   int tagaux = 0;
//   // long double Qfp = 0;
//   for(int tagz = tagMin; tagz <= tagMax; tagz += tagStep){
//     // labels[size] = tags;
    
//     if (auxi == 1)
//     {
//       fileS << "\n";
//       fileM << "\n";
//       fileT << "\n";
//       fileC << "\n";
//       fileE << "\n";
//     }
//     auxi = 1;
//     fileS << tagz;
//     fileM << tagz;
//     fileT << tagz;
//     fileE << tagz;
//     fileC << tagz;
//     long double collisionsMean = 0;
//     long double emptiesMean = 0;
//     long double slotsMean = 0;
//     long double timeMean = 0;
//     long double flowMean = 0;
//     long double efficiency = 0;
//     for(int i = 0; i < repetitions; i++){
//       tagaux = tagz;
//       Q = Qverify (tagaux);
//       int totalSlots = 0;
//       int sucessSlots = 0;
//       int collision = 0;
//       int emptie = 0; 
//       timeval start, end;
//       gettimeofday(&start, 0);
//       tags* tag2, *aux2;
//       tag2 = (tags*) malloc (sizeof(tags));
//       Query(tag2, tagz);
//       while(tag2->next != NULL)
//       {
//         int sendFlag = 0;
//         for(aux2 = tag2->next; aux2 != NULL; aux2 = aux2->next)
//         {
//           if(aux2->RandNum == 0)
//           {
//             sendFlag = sendFlag + 1;
//           } 
//         }
//         if (sendFlag == 1)
//         {
//           sucessSlots = sucessSlots + 1;
//           tagaux = tagaux - 1;
//           TagRemov(tag2);
//           QueryAdjust(tag2);
//         }
//         else if(sendFlag > 1)
//         {
//           collision = collision + 1;
//           Q = Qverify (tagaux);
//           QueryRep(tag2, Q);
//           //DebugF << " Debug 4: Q = " << Q << ", Qfp = " << Qfp << "\n";
//         }
//         else 
//         {
//           emptie = emptie + 1;
//           leaux = leaux + 0.2;
//           QueryAdjust(tag2);
//           if (leaux >= 1)
//           {
//             leaux = 0;
//             Q = Qverify (tagaux);
//             QueryRep(tag2, Q);
//           }
          
//         }
//         //DebugF << " Debug tester: Q = " << Q << "\n";
//       }
//       gettimeofday(&end, 0);
//       int elapsed = (((end.tv_sec - start.tv_sec)*1000000L+end.tv_usec) - start.tv_usec);
//       timeMean += elapsed;
//       totalSlots += sucessSlots + collision + emptie;
//       slotsMean += totalSlots;
//       emptiesMean += emptie;
//       collisionsMean += collision;
//       flowMean += sucessSlots/(double)totalSlots;
//       efficiency += tagz/(double)totalSlots;
//     }
//     // printf(" Debug 0: Q = %lf, Qfp = %lf \n ", Q, Qfp);
//     //DebugF << " Debug 0: Q = " << Q << "\n";
//     // results[size].push_back(ceil(slotsMean/(double)repetitions));
//     fileS << ", " << ceil(slotsMean/(double)repetitions);
//     // results[size].push_back(ceil(emptiesMean/(double)repetitions));
//     fileM << ", " << ceil(emptiesMean/(double)repetitions);
//     // results[size].push_back(ceil(collisionsMean/(double)repetitions));
//     fileC << ", " << ceil(collisionsMean/(double)repetitions);
//     // results[size].push_back(ceil(timeMean/(double)repetitions));
//     fileT << ", " << ceil(timeMean/(double)repetitions);
//     // Efficiency.push_back(efficiency/(double)repetitions);
//     fileE << ", " << efficiency/(double)repetitions;
//     // flow.push_back(flowMean/(double)repetitions);
//   }
//   fileS.close();
//   fileM.close();
//   fileC.close();
//   fileT.close();
//   fileE.close();
//   DebugF.close();
// }

int main(){
  srand(time(NULL));
  int tagMin, tagMax, tagStep, slots, repetitions;
  printf(" -- ----- Starting ------ --\n");
  scanf("%d %d %d %d %d", &tagMin, &tagStep, &tagMax, &slots, &repetitions);
  printf("\n -- Configuration Entered --\n");
  printf("Starting number of tags: %d", tagMin);
  printf("\nTag step: %d", tagStep);
  printf("\nMaximum number of tags: %d", tagMax);
  printf("\nStarting number of slot: %d", slots);
  printf("\nNumber of repetitions: %d\n", repetitions);
  printf("\n -- --------------------- --\n");

  //printf("here1\n");

  // vector<Estimator*> estimators;
  // LowerBound lowerBound;
  // //printf("here2\n");
  // EomLee eomLee;
  // //printf("here3\n");
  // DsMap dsMap;
  // //printf("here4\n");
  // Chen CHEN;
  // //printf("here5\n"); 

  // estimators.push_back(&lowerBound);
  // estimators.push_back(&eomLee);
  // estimators.push_back(&dsMap);
  // //estimators.push_back(&FEIA);
  // estimators.push_back(&CHEN);

  // vector<Simulator> simulators;
  // for(int i = 0; i < estimators.size(); i++){
  //   printf("initializing estimator %d\n", i);
  //   simulators.push_back(Simulator(tagMin, tagMax, tagStep, repetitions, slots, estimators[i]));
  //   printf("running estimator %d\n", i);
  //   simulators[i].run();
  // }


  printf("running Algorith Q\n");
  runQ(tagMin, tagMax, tagStep, repetitions, slots);
  printf("Almost there...\n");
  //runQ2(tagMin, tagMax, tagStep, repetitions, slots);

  // if (slots == 64)
  // {
  //   export_csv("output/slots.csv", simulators, 0);
  //   export_csv("output/empties.csv", simulators, 1);
  //   export_csv("output/collisions.csv", simulators, 2);
  //   export_csv("output/time.csv", simulators, 3);
  //   export_Efficiency("output/efficiency.csv", simulators);
  //   export_flow("output/flow.csv", simulators);
  // }
  // else 
  // {
  //   export_csv("output/slots128.csv", simulators, 0);
  //   export_csv("output/empties128.csv", simulators, 1);
  //   export_csv("output/collisions128.csv", simulators, 2);
  //   export_csv("output/time128.csv", simulators, 3);
  //   export_Efficiency("output/efficiency128.csv", simulators);
  //   export_flow("output/flow128.csv", simulators);
  // }

  printf("Thats all folks.\n");

  return 0;
}
