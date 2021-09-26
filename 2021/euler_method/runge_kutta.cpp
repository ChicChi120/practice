// ルンゲ・クッタ法 (4次)

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

    vector<double> k1(N + 1);
    vector<double> k2(N + 1);
    vector<double> k3(N + 1);
    vector<double> k4(N + 1);
    vector<double> x(N + 1);

    double t = 0.0;
    double x0 = 1.0;

    k1[0] = 0.0;
    k2[0] = 0.0;
    k3[0] = 0.0;
    k4[0] = 0.0;
    x[0] = x0;

    fp = fopen("data03.dat", "w");

    fprintf(fp, "%d %f \n", 0, x[0]);

    for (int i = 1; i < x.size(); i++)
    {
        k1[i] = f(t, x[i-1]);
        k2[i] = f(t+h/2, x[i-1]+(h/2)*k1[i]);
        k3[i] = f(t+h/2, x[i-1]+(h/2)*k2[i]);
        k4[i] = f(t+h, x[i-1]+h*k3[i]);

        x[i] = x[i-1] + (h/6) * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);

        fprintf(fp, "%f %f \n", h*i, x[i]);

        t = t + h;
    }
    
    fclose(fp);
    
    return 0;
}
