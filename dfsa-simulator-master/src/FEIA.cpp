class FEIA : public Estimator{
  public:
      int getNextFrame(int collisions, int empties, int sucess) {
        return collisions * 2;
      }
};
