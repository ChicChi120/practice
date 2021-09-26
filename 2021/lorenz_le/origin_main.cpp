#include <iostream>
#include <vector>

using namespace std;


double f1(double x, double y){

    return -16*x + 16*y;
}

double f2(double x, double y, double z){

    return -x*z + 40*x - y;
}

double f3(double x, double y, double z){

    return x*y - 4.0*z;
}


double runge_kutta(){

    FILE *fp;

    double N = 200000;
    double T = 200.0;
    double h = T/N;

    vector<double> k1(N + 1);
    vector<double> k2(N + 1);
    vector<double> k3(N + 1);
    vector<double> k4(N + 1);

    vector<double> l1(N + 1);
    vector<double> l2(N + 1);
    vector<double> l3(N + 1);
    vector<double> l4(N + 1);

    vector<double> m1(N + 1);
    vector<double> m2(N + 1);
    vector<double> m3(N + 1);
    vector<double> m4(N + 1);
    
    vector<double> x(N + 1);
    vector<double> y(N + 1);
    vector<double> z(N + 1);

    double t = 0.0;
    double x0 = 1.0;
    double y0 = 1.0;
    double z0 = 1.0;

    // 初期値
    k1[0] = 0.0;
    k2[0] = 0.0;
    k3[0] = 0.0;
    k4[0] = 0.0;

    l1[0] = 0.0;
    l2[0] = 0.0;
    l3[0] = 0.0;
    l4[0] = 0.0;

    m1[0] = 0.0;
    m2[0] = 0.0;
    m3[0] = 0.0;
    m4[0] = 0.0;

    x[0] = x0;
    y[0] = y0;
    z[0] = z0;

    fp = fopen("data.dat", "w");

    fprintf(fp, "%lf %lf %lf \n", x[0], y[0], z[0]);

    for (int i = 1; i < x.size(); i++)
    {
        k1[i] = h * f1(x[i - 1], y[i - 1]);
        l1[i] = h * f2(x[i - 1], y[i - 1], z[i - 1]);
        m1[i] = h * f3(x[i - 1], y[i - 1], z[i - 1]);

        k2[i] = h * f1(x[i - 1] + k1[i]/2.0, y[i - 1] + l1[i]/2.0);
        l2[i] = h * f2(x[i - 1] + k1[i]/2.0, y[i - 1] + l1[i]/2.0, z[i - 1] + m1[i]/2.0);
        m2[i] = h * f3(x[i - 1] + k1[i]/2.0, y[i - 1] + l1[i]/2.0, z[i - 1] + m1[i]/2.0);

        k3[i] = h * f1(x[i - 1] + k2[i]/2.0, y[i - 1] + l2[i]/2.0);
        l3[i] = h * f2(x[i - 1] + k2[i]/2.0, y[i - 1] + l2[i]/2.0, z[i - 1] + m2[i]/2.0);
        m3[i] = h * f3(x[i - 1] + k2[i]/2.0, y[i - 1] + l2[i]/2.0, z[i - 1] + m2[i]/2.0);

        k4[i] = h * f1(x[i - 1] + k3[i], y[i - 1] + l3[i]);
        l4[i] = h * f2(x[i - 1] + k3[i], y[i - 1] + l3[i], z[i - 1] + m3[i]);
        m4[i] = h * f3(x[i - 1] + k3[i], y[i - 1] + l3[i], z[i - 1] + m3[i]);

        x[i] = x[i - 1] + (k1[i] + 2.0*k2[i] + 2.0*k3[i] + k4[i]) / 6.0;
        y[i] = y[i - 1] + (l1[i] + 2.0*l2[i] + 2.0*l3[i] + l4[i]) / 6.0;
        z[i] = z[i - 1] + (m1[i] + 2.0*m2[i] + 2.0*m3[i] + m4[i]) / 6.0;

        t = t + h;

        fprintf(fp, "%lf %lf %lf \n", x[i], y[i], z[i]);
    }
    
    fclose(fp);

    return 0.0;

}




int main(int argc, char const *argv[])
{
    
    runge_kutta();
    
    return 0;
}
