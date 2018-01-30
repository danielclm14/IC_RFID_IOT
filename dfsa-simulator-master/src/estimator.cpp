#ifndef ESTIMATOR
#define ESTIMATOR

class Estimator{
  public:
    virtual int getNextFrame(int collisions, int empties, int sucess) {}
};

#endif