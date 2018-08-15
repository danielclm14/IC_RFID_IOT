class Chen : public Estimator{
private:
    long double* fatArr;
    long double fat(int n) {
        if (fatArr[n]<=0)
            fatArr[n] = fat(n - 1) * n;
        return fatArr[n];
    }
    double fatSimples (long double a, long double b, long double c, long double d)
    {
        long double result = 1;
        while (a > 1)
        {
            result = result*a;
            a=a-1;
            if (b > 1)
            {
                result = result / b;
                b=b-1;
            }
            if (c > 1)
            {
                result = result / c;
                c=c-1;
            }
            if (d > 1)
            {
                result = result / d;
                d=d-1;
            }

        }
        return result;
    }
public:
      int getNextFrame(int collisions, int empties, int sucess) {
        long double L = collisions + empties + sucess;
        long double N = sucess + 2*collisions;
        long double next = 0;
        long double previous = -1;
        long double pe, ps, pc;
        long double l1 = 1.0/L;
        while (previous < next)
        {
            long double n1 = N/L;
            pe = pow(1-l1, N);
            ps = (n1)*pow(1-l1, N-1);
            pc = 1-pe-ps;
            previous = next;
            long double fat = fatSimples(L, sucess, collisions, empties);
            long double doublenext = fat*pow(pe,empties)*pow(ps,sucess)*pow(pc,collisions);
            next = doublenext;
            N++;
        }
        return N-2-sucess;
      }
};
