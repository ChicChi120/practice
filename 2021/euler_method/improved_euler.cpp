// 改良オイラー法
// ホイン法

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

    vector<double> xc(N + 1);
    vector<double> x(N + 1);

    double t = 0.0;
    double x0 = 1.0;

    xc[0] = 0.0;
    x[0] = x0;

    fp = fopen("data02.dat", "w");

    fprintf(fp, "%d %f \n", 0, x[0]);

    for (int i = 1; i < x.size(); i++)
    {
        xc[i] = x[i-1] + h * f(t, x[i-1]);
        x[i] = x[i-1] + (h/2) * (f(t, x[i-1]) + f(t+h, xc[i]));

        fprintf(fp, "%f %f \n", h*i, x[i]);

        t = t + h;
    }
    
    fclose(fp);



    return 0;
}
