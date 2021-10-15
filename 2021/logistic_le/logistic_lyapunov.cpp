#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


double f(double x, double mu){

    return mu * x * (1.0 - x);
    
}

double df(double x, double mu){

    return mu * abs(1.0 - 2.0*x);
    
}

double sum(vector<double> a){
    double b = 0.0;

    for (int i = 0; i < a.size(); i++)
    {
        b += a[i];
    }
    
    return b;
}


double lyapunov_exp(){

    int T = 400;
    vector<double> x(T);
    vector<double> dx(T);
    vector<double> sumlog(T);

    double x0 = 0.01;
    double mu = 4.0;

    x[0] = x0;
    dx[0] = df(x[0], mu);
    sumlog[0] = log(dx[0]);


    FILE *fp;
    fp = fopen("lyapunov_exp.dat", "w");

    for (double a = 0.0; a < mu; a+=0.01)
    {
        for (int t = 1; t < T; t++)
        {
            x[t] = f(x[t - 1], a);
            dx[t] = df(x[t], a);
            sumlog[t] = log(dx[t]);
        }

        fprintf(fp, "%lf %lf \n", a, sum(sumlog) / T);
    }

    fclose(fp);

    return sum(sumlog) / T;
}


int main(int argc, char const *argv[])
{
    cout << lyapunov_exp() << endl;
    
    return 0;
}
