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

    FILE *fp, *gp;
    if ((gp = popen("gnuplot -persist", "w")) == NULL)
    {
        cout << "gnuplot open error" << endl;
        exit(EXIT_FAILURE);
    }

    double N = 200000;
    double T = 200.0;
    double h = T/N;

    vector<double> k1(N);
    vector<double> k2(N);
    vector<double> k3(N);
    vector<double> k4(N);

    vector<double> l1(N);
    vector<double> l2(N);
    vector<double> l3(N);
    vector<double> l4(N);

    vector<double> m1(N);
    vector<double> m2(N);
    vector<double> m3(N);
    vector<double> m4(N);
    
    vector<double> x(N);
    vector<double> y(N);
    vector<double> z(N);

    double t = 0.0;
    double x0 = 1.0;
    double y0 = 1.0;
    double z0 = 1.0;

    // 初期値
    x[0] = x0;
    y[0] = y0;
    z[0] = z0;

    fp = fopen("data.csv", "w");
    fprintf(fp, "%lf, %lf, %lf \n", x[0], y[0], z[0]);
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

        fprintf(fp, "%lf, %lf, %lf \n", x[i], y[i], z[i]);
    }
    fclose(fp);

    fprintf(gp, "reset \n");
    fprintf(gp, "set datafile separator ',' \n");  // csv
    fprintf(gp, "splot 'data.csv' w l \n");
    fflush(gp);
    fprintf(gp, "exit \n");
    pclose(gp);

    return 0.0;

}




int main(int argc, char const *argv[])
{
    
    runge_kutta();
    
    return 0;
}
