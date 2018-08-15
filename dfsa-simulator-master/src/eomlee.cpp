class EomLee : public Estimator {
  public:
    int getNextFrame(int collisions, int empties, int sucess){
        long double eps = 0.001;
        long double y = 0;
        long double py = 2;
        long double l = collisions+empties+sucess;
        long double euler = 2.71828183;
        while(1){
          long double b = l/(py*collisions+sucess);
          long double e = pow(euler, -(1/b));
          long double a = 1-e;
          long double eb = (1+(1/b))*e;
          long double nb = b*(1-eb);
          y = a/nb;
          if(fabs(y-py) < eps){
            break;
          }
          py = y;
        }
        return ceil(y*collisions);
    }
};
