#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// fx
double f1(double x, double y){

    return 1.4 + 0.3*y - pow(x, 2);
}

double f2(double x){

    return x;
}


// delta
double jd1(double q1, double q2, double x){

    return -2.0*x*q1 + 0.3*q2;
}

double jd2(double q1){

    return q1;
}


double norm(double a, double b){

    return sqrt(pow(a, 2) + pow(b, 2));
}

double sum(vector<double> a){
double b = 0.0;

    for (int i = 0; i < a.size(); i++)
    {
        b += a[i];
    }
    
    return b;
}

double algorithm(){

    // FILE *fp;

    double N = 2930.0;
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


    vector<double> x(N + 1);
    vector<double> y(N + 1);

    vector<double> dq1(N + 1);
    vector<double> dq2(N + 1);

    vector<double> logd(N + 1);

    double t = 0.0;
    double x0 = 1.0;
    double y0 = 1.0;

    double delta_norm = 0.0;

    // 初期値
    k1[0] = 0.0;
    k2[0] = 0.0;
    k3[0] = 0.0;
    k4[0] = 0.0;

    l1[0] = 0.0;
    l2[0] = 0.0;
    l3[0] = 0.0;
    l4[0] = 0.0;


    x[0] = x0;
    y[0] = y0;


    dq1[0] = jd1(1.0, 0.0, x[0]) / sqrt(pow(jd1(1.0, 0.0, x[0]), 2) + pow(jd2(1.0), 2));
    dq2[0] = jd2(1.0) / sqrt(pow(jd1(1.0, 0.0, x[0]), 2) + pow(jd2(1.0), 2));

    logd[0] = 0.0;

    FILE *fp;
    fp = fopen("lyapunov.dat", "w");

    for (int i = 1; i < x.size(); i++)
    {
        k1[i] = h * f1(x[i - 1], y[i - 1]);
        l1[i] = h * f2(x[i - 1]);

        k2[i] = h * f1(x[i - 1] + k1[i]/2.0, y[i - 1] + l1[i]/2.0);
        l2[i] = h * f2(x[i - 1] + k1[i]/2.0);

        k3[i] = h * f1(x[i - 1] + k2[i]/2.0, y[i - 1] + l2[i]/2.0);
        l3[i] = h * f2(x[i - 1] + k2[i]/2.0);

        k4[i] = h * f1(x[i - 1] + k3[i], y[i - 1] + l3[i]);
        l4[i] = h * f2(x[i - 1] + k3[i]);

        x[i] = x[i - 1] + (k1[i] + 2.0*k2[i] + 2.0*k3[i] + k4[i]) / 6.0;
        y[i] = y[i - 1] + (l1[i] + 2.0*l2[i] + 2.0*l3[i] + l4[i]) / 6.0;


        // delta
        k1[i] = h * jd1(dq1[i - 1], dq2[i - 1], x[i]);
        l1[i] = h * jd2(dq1[i - 1]);

        k2[i] = h * jd1(dq1[i - 1] + k1[i]/2.0, dq2[i - 1] + l1[i]/2.0, x[i]);
        l2[i] = h * jd2(dq1[i - 1] + k1[i]/2.0);

        k3[i] = h * jd1(dq1[i - 1] + k2[i]/2.0, dq2[i - 1] + l2[i]/2.0, x[i]);
        l3[i] = h * jd2(dq1[i - 1] + k2[i]/2.0);

        k4[i] = h * jd1(dq1[i - 1] + k3[i], dq2[i - 1] + l3[i], x[i]);
        l4[i] = h * jd2(dq1[i - 1] + k3[i]);

        dq1[i] = dq1[i - 1] + (k1[i] + 2.0*k2[i] + 2.0*k3[i] + k4[i]) / 6.0;
        dq2[i] = dq2[i - 1] + (l1[i] + 2.0*l2[i] + 2.0*l3[i] + l4[i]) / 6.0;

        // normalization
        delta_norm = norm(dq1[i], dq2[i]);
        dq1[i] = dq1[i] / delta_norm;
        dq2[i] = dq2[i] / delta_norm;

        logd[i] = log(delta_norm);

        t = t + h;

        // cout << sum(logd) / t << endl;
        fprintf(fp, "%lf %lf \n", t, sum(logd)/t);

    }
    fclose(fp);

    return sum(logd) / T;

}




int main(int argc, char const *argv[])
{
    double lambda = 0.0;
    
    lambda = algorithm();
    cout << lambda << endl;
    
    return 0;
}
