#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// fx
double f1(double x, double y){

    return -16*x + 16*y;
}

double f2(double x, double y, double z){

    return -x*z + 40*x - y;
}

double f3(double x, double y, double z){

    return x*y - 4.0*z;
}


// delta
double jd1(double q1, double q2){

    return -16*q1 + 16*q2;
}

double jd2(double q1, double q2, double q3, double x, double z){

    return (40 - z)*q1 - q2 - x*q3;
}

double jd3(double q1, double q2, double q3, double x, double y){

    return y*q1 + x*q2 - 4.0*q3;
}


double norm(double a, double b, double c){

    return sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
}

double sum(vector<double> a){
double b = 0.0;

    for (int i = 0; i < a.size(); i++)
    {
        b += a[i];
    }
    
    return b;
}

double runge_kutta(){

    double N = 200000.0;
    double T = 2000.0;
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

    vector<double> dq1(N);
    vector<double> dq2(N);
    vector<double> dq3(N);

    vector<double> logd(N);

    double t = 0.0;
    double x0 = 10.0;
    double y0 = 0.0;
    double z0 = 30.0;

    double delta_norm = 0.0;

    // 初期値
    x[0] = x0;
    y[0] = y0;
    z[0] = z0;


    dq1[0] = jd1(1.0, 0.0) / sqrt(pow(jd1(1.0, 0.0), 2) + pow(jd2(1.0, 0.0, 0.0, x[0], z[0]), 2) + pow(jd3(1.0, 0.0, 0.0, x[0], y[0]), 2));
    dq2[0] = jd2(1.0, 0.0, 0.0, x[0], z[0]) / sqrt(pow(jd1(1.0, 0.0), 2) + pow(jd2(1.0, 0.0, 0.0, x[0], z[0]), 2) + pow(jd3(1.0, 0.0, 0.0, x[0], y[0]), 2));
    dq3[0] = jd3(1.0, 0.0, 0.0, x[0], y[0]) / sqrt(pow(jd1(1.0, 0.0), 2) + pow(jd2(1.0, 0.0, 0.0, x[0], z[0]), 2) + pow(jd3(1.0, 0.0, 0.0, x[0], y[0]), 2));

    logd[0] = 0.0;

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


        // delta
        k1[i] = h * jd1(dq1[i - 1], dq2[i - 1]);
        l1[i] = h * jd2(dq1[i - 1], dq2[i - 1], dq3[i - 1], x[i], z[i]);
        m1[i] = h * jd3(dq1[i - 1], dq2[i - 1], dq3[i - 1], x[i], y[i]);

        k2[i] = h * jd1(dq1[i - 1] + k1[i]/2.0, dq2[i - 1] + l1[i]/2.0);
        l2[i] = h * jd2(dq1[i - 1] + k1[i]/2.0, dq2[i - 1] + l1[i]/2.0, dq3[i - 1] + m1[i]/2.0, x[i], z[i]);
        m2[i] = h * jd3(dq1[i - 1] + k1[i]/2.0, dq2[i - 1] + l1[i]/2.0, dq3[i - 1] + m1[i]/2.0, x[i], y[i]);

        k3[i] = h * jd1(dq1[i - 1] + k2[i]/2.0, dq2[i - 1] + l2[i]/2.0);
        l3[i] = h * jd2(dq1[i - 1] + k2[i]/2.0, dq2[i - 1] + l2[i]/2.0, dq3[i - 1] + m2[i]/2.0, x[i], z[i]);
        m3[i] = h * jd3(dq1[i - 1] + k2[i]/2.0, dq2[i - 1] + l2[i]/2.0, dq3[i - 1] + m2[i]/2.0, x[i], y[i]);

        k4[i] = h * jd1(dq1[i - 1] + k3[i], dq2[i - 1] + l3[i]);
        l4[i] = h * jd2(dq1[i - 1] + k3[i], dq2[i - 1] + l3[i], dq3[i - 1] + m3[i], x[i], z[i]);
        m4[i] = h * jd3(dq1[i - 1] + k3[i], dq2[i - 1] + l3[i], dq3[i - 1] + m3[i], x[i], y[i]);

        dq1[i] = dq1[i - 1] + (k1[i] + 2.0*k2[i] + 2.0*k3[i] + k4[i]) / 6.0;
        dq2[i] = dq2[i - 1] + (l1[i] + 2.0*l2[i] + 2.0*l3[i] + l4[i]) / 6.0;
        dq3[i] = dq3[i - 1] + (m1[i] + 2.0*m2[i] + 2.0*m3[i] + m4[i]) / 6.0;

        // normalization
        delta_norm = norm(dq1[i], dq2[i], dq3[i]);
        dq1[i] = dq1[i] / delta_norm;
        dq2[i] = dq2[i] / delta_norm;
        dq3[i] = dq3[i] / delta_norm;

        logd[i] = log(delta_norm);

        t = t + h;

    }

    return sum(logd) / T;

}




int main(int argc, char const *argv[])
{
    double lambda;
    
    lambda = runge_kutta();
    cout << lambda << endl;
    
    return 0;
}
