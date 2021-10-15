#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

double logistic(double x, double mu){

    return mu * x * (1.0 - x);
    
}



double l_map(){

    int T = 400;
    vector<double> x(T);

    double x0 = 0.01;
    double mu = 4.0;

    x[0] = x0;


    FILE *fp;
    fp = fopen("data.dat", "w");

    for (int i = 1; i < T; i++)
    {
        x[i] = logistic(x[i - 1], mu);


        fprintf(fp, "%d %lf \n", i, x[i]);
    }

    fclose(fp);

    return 0.0;
}


int main(int argc, char const *argv[])
{
    l_map();  // log2
    
    return 0;
}
