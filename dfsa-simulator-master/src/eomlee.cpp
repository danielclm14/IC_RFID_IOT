class EomLee : public Estimator {
  public:
    int getNextFrame(int collisions, int empties, int sucess){
        double eps = 0.001;
        double y = 0;
        double py = 2;
        double l = collisions+empties+sucess;
        double euler = 2.71828183;
        while(1){
          double b = l/(py*collisions+sucess);
          double e = pow(euler, -(1/b));
          double a = 1-e;
          double eb = (1+(1/b))*e;
          double nb = b*(1-eb);
          y = a/nb;
          if(fabs(y-py) < eps){
            break;
          }
          py = y;
        }
        return ceil(y*collisions);
    }
};
