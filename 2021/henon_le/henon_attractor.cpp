#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

double f1(double x, double y){
    
    return 1.4 + 0.3*y - pow(x, 2.0);
    
}

double f2(double x){

    return x;
}

double attractor(){

    int N = 10000;
    vector<double> x(N);
    vector<double> y(N);

    double x0 = 0.0;
    double y0 = 0.0;

    x[0] = x0;
    y[0] = y0;


    FILE *fp;
    fp = fopen("data.dat", "w");

    for (int i = 1; i < N; i++)
    {
        x[i] = f1(x[i - 1], y[i - 1]);
        y[i] = f2(x[i - 1]);

        fprintf(fp, "%lf %lf \n", x[i], y[i]);
    }

    fclose(fp);

    return 0.0;
}


int main(int argc, char const *argv[])
{
    attractor();
    
    return 0;
}
