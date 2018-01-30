
using namespace std;

class Simulator{
  private:
    int tagMin;
    int tagMax;
    int tagStep;
    int repetitions;
    int slots;
    Estimator* estimator;
    int inUse[1000000];
    int removed[1000000];
    int it = 0;
    int size = 0;
    vector<vector<int> > results;
    vector<double> flow;
    vector<int> labels;
  public:
    Simulator(){}
    Simulator(int tagMin, int tagMax, int tagStep, int repetitions, int slots, Estimator* estimator){
      this->tagMin = tagMin;
      this->tagMax = tagMax;
      this->tagStep = tagStep;
      this->repetitions = repetitions;
      this->slots = slots;
      this->estimator = estimator;
      this->labels.assign(tagMax, -1);
      this->results.assign(tagMax, vector<int>());
    }
    void run(){
      for(int tags = tagMin; tags <= tagMax; tags += tagStep){
        labels[size] = tags;
        double collisionsMean = 0;
        double emptiesMean = 0;
        double slotsMean = 0;
        double timeMean = 0;
        double flowMean = 0;
        for(int i = 0; i < repetitions; i++){
          int totalSlots = 0;
          int sucessSlots = 0; 
          int toIdentify = tags;
          int slots = this->slots;
          timeval start, end;
          gettimeofday(&start, 0);
          while(toIdentify){
            it++;
            int collisions = 0;
            int sucess = 0;
            int empties = slots;
            int remaining = toIdentify;
            for(int j = 0; j < remaining; j++){
              int x = rand()%slots;
              if(inUse[x] == it){
                if(removed[x] != it){
                  collisions++;
                  removed[x] = it;
                  toIdentify++;
                  sucess--;
                }
              } else {
                inUse[x] = it;
                empties--;
                sucess++;
                toIdentify--;
              }
            }
            collisionsMean += collisions;
            emptiesMean += empties;
            slotsMean += slots;
            totalSlots += slots;
            sucessSlots += sucess;
            slots = estimator->getNextFrame(collisions, empties, sucess);
          }
          gettimeofday(&end, 0);
          int elapsed = (((end.tv_sec - start.tv_sec)*1000000L+end.tv_usec) - start.tv_usec);
          timeMean += elapsed;
          flowMean += sucessSlots/(double)totalSlots;
        }
        results[size].push_back(ceil(slotsMean/(double)repetitions));
        results[size].push_back(ceil(emptiesMean/(double)repetitions));
        results[size].push_back(ceil(collisionsMean/(double)repetitions));
        results[size].push_back(ceil(timeMean/(double)repetitions));
        flow.push_back(flowMean/(double)repetitions);
        size++;
      }
    }
    int getSize(){
      return size;
    }
    vector<vector<int> > getResult(){
      return results;
    }
    vector<int> getLabel(){
      return labels;
    }
    vector<double> getFlow(){
      return flow;
    }
};
