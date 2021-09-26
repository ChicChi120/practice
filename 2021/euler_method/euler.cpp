#include <iostream>
#include <vector>

using namespace std;


double f(double t, double x){

    return 2*t*x;
}


int main(int argc, char const *argv[])
{
    FILE *fp;

    double N = 200;
    double T = 1.0;
    double h = T/N;

    vector<double> x(N + 1);

    double t0 = 0.0;
    double x0 = 1.0;

    x[0] = x0;

    fp = fopen("data01.dat", "w");

    fprintf(fp, "%d %f \n", 0, x[0]);

    for (int i = 1; i < x.size(); i++)
    {
        x[i] = x[i-1] + h*f(t0, x[i-1]);

        fprintf(fp, "%f %f \n", h*i, x[i]);
        
        t0 = t0 + h;
    }
    
    fclose(fp);

    return 0;
}
