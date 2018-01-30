#include <cmath>
#include "estimator.cpp"
#include <iostream>

#ifndef DSMAP
#define DSMAP

class DsMap : public Estimator {
  private:
    int getSubFrameSize(int frames) {
        if (frames < 16)
            return 4;
        if (frames < 64)
            return 8;
        if (frames < 256)
            return 16;
        if (frames < 1024)
            return 32;
        return 64;
    }
    double* fatArr;
    double fat(int n) {
        if (fatArr[n]<=0)
            fatArr[n] = fat(n - 1) * n;
        return fatArr[n];
    }
    double P(int n, int p) {
        return (fat(n)/(fat(p)*fat(n-p)));
    }
    double P1(int e, int f, int n) {
        return pow((1-(e/f)),n);
    }
    double P2(int s, int e, int f, int n) {
        return P(n, s)*((pow((f-e-s), (n-s)))/(pow((f-e), n)))*fat(s);
    }
    // using vaedhi algorithm
    int map(int e, int s, int c) {
        int l = e+s+c;
        int n = s + 2*c;
        double next = 0;
        double prev = -1;
        while (prev < next) {
            double p1 = P1(e, l, n);
            double p2 = P2(s, e, l, n);
            double p3 = 0;
            for (int k=0;k<c;++k) {
                for (int v=0;v<(c-k);++v) {
                    int ck = c - k;
                    int ckv = c - k - v;
                    int ns = n - s;
                    int nsk = n - s - k;
                    p3 = p3 + (pow(-1, k+v) * ((fat(c)/(fat(k)*fat((ck)))*(fat(ck)/(fat(v)*fat(ckv))*(fat(ns)/fat(nsk))*(pow((ckv), (nsk))/pow(c, (ns)))))));
                }
            }
            prev = next;
            next = ((fat(l))/(fat(e)*fat(s)*fat(c)))*p1*p2*p3;
            n++;
        }
        return round(n/2);
    }
    bool fitsNEst(int fCur, int nEst) {
        // estimated function for max for later nMax = (11x/8) + floor(log2(x)/5)
        return ((fCur - fCur / 2) >= nEst) && ((fCur + fCur / 2) <= nEst);
    }
public:
    DsMap() {
        fatArr = new double[100000];
        fatArr[0] = 1;
        fatArr[1] = 1;
    }
    ~DsMap() {
        delete fatArr;
    }
    int getNextFrame(int collisions, int empties, int sucess) {
        int fIni = collisions + empties + sucess;
        int fCur = fIni;
        int fSub = getSubFrameSize(fIni);
        int k = fIni / fSub;
        int ns = sucess / k;
        int nc = collisions / k;
        int n = map(ns, nc, fSub);
        int nEst = n * k;
        return (int)pow(2, round(log2((double)nEst)));
        // int nBack;
        // if (fitsNEst(fCur, nEst)) {
            
        //     return 1;
        // } else {
        //     nBack = nEst - ns;
        //     return 1;
        // }
    }
};

#endif