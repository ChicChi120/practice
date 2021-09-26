#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

double printvector(const vector<double> a){
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

// fx
double f1(double x, double y, double z){

    return (z - 0.7)*x - 3.5*y;
}

double f2(double x, double y, double z){

    return 3.5*x + (z - 0.7)*y;
}

double f3(double x, double y, double z){

    return 0.6 + z - pow(z, 3)/3.0 - (pow(x, 2) + pow(y, 2)) * (1 + 0.25*z) + 0.01*z*pow(x, 3);
}


// delta
double jd1(double q1, double q2, double q3, double x, double z){

    return (z - 0.7)*q1 - 3.5*q2 + x*q3;
}

double jd2(double q1, double q2, double q3, double y, double z){

    return 3.5*q1 + (z - 0.7)*q2 + y*q3;
}

double jd3(double q1, double q2, double q3, double x, double y, double z){

    return (-2*x*(1.0 + 0.25*z) + 0.03*z*pow(x, 2))*q1 + -2*y*(1.0 + 0.25*z)*q2 + (1.0 - pow(z, 2) - 0.25*(pow(x, 2) + pow(y, 2)) + 0.01*pow(x, 3))*q3;
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

    // FILE *fp;

    double N = 20000.0;
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

    vector<double> dq1(N + 1);
    vector<double> dq2(N + 1);
    vector<double> dq3(N + 1);

    vector<double> logd(N + 1);

    double t = 0.0;
    double x0 = 1.0;
    double y0 = 1.0;
    double z0 = 1.0;

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

    m1[0] = 0.0;
    m2[0] = 0.0;
    m3[0] = 0.0;
    m4[0] = 0.0;

    x[0] = x0;
    y[0] = y0;
    z[0] = z0;


    dq1[0] = jd1(1.0, 0.0, 0.0, x[0], z[0]) / sqrt(pow(jd1(1.0, 0.0, 0.0, x[0], z[0]), 2) + pow(jd2(1.0, 0.0, 0.0, y[0], z[0]), 2) + pow(jd3(1.0, 0.0, 0.0, x[0], y[0], z[0]), 2));
    dq2[0] = jd2(1.0, 0.0, 0.0, y[0], z[0]) / sqrt(pow(jd1(1.0, 0.0, 0.0, x[0], z[0]), 2) + pow(jd2(1.0, 0.0, 0.0, y[0], z[0]), 2) + pow(jd3(1.0, 0.0, 0.0, x[0], y[0], z[0]), 2));
    dq3[0] = jd3(1.0, 0.0, 0.0, x[0], y[0], z[0]) / sqrt(pow(jd1(1.0, 0.0, 0.0, x[0], z[0]), 2) + pow(jd2(1.0, 0.0, 0.0, y[0], z[0]), 2) + pow(jd3(1.0, 0.0, 0.0, x[0], y[0], z[0]), 2));

    logd[0] = 0.0;

    // fp = fopen("lyapunov.dat", "w");
    // fprintf(fp, "%lf %lf \n", t, logd[0]);

    for (int i = 1; i < x.size(); i++)
    {
        k1[i] = h * f1(x[i - 1], y[i - 1], z[i - 1]);
        l1[i] = h * f2(x[i - 1], y[i - 1], z[i - 1]);
        m1[i] = h * f3(x[i - 1], y[i - 1], z[i - 1]);

        k2[i] = h * f1(x[i - 1] + k1[i]/2.0, y[i - 1] + l1[i]/2.0, z[i - 1] + m1[i]/2.0);
        l2[i] = h * f2(x[i - 1] + k1[i]/2.0, y[i - 1] + l1[i]/2.0, z[i - 1] + m1[i]/2.0);
        m2[i] = h * f3(x[i - 1] + k1[i]/2.0, y[i - 1] + l1[i]/2.0, z[i - 1] + m1[i]/2.0);

        k3[i] = h * f1(x[i - 1] + k2[i]/2.0, y[i - 1] + l2[i]/2.0, z[i - 1] + m2[i]/2.0);
        l3[i] = h * f2(x[i - 1] + k2[i]/2.0, y[i - 1] + l2[i]/2.0, z[i - 1] + m2[i]/2.0);
        m3[i] = h * f3(x[i - 1] + k2[i]/2.0, y[i - 1] + l2[i]/2.0, z[i - 1] + m2[i]/2.0);

        k4[i] = h * f1(x[i - 1] + k3[i], y[i - 1] + l3[i], z[i - 1] + m3[i]);
        l4[i] = h * f2(x[i - 1] + k3[i], y[i - 1] + l3[i], z[i - 1] + m3[i]);
        m4[i] = h * f3(x[i - 1] + k3[i], y[i - 1] + l3[i], z[i - 1] + m3[i]);

        x[i] = x[i - 1] + (k1[i] + 2.0*k2[i] + 2.0*k3[i] + k4[i]) / 6.0;
        y[i] = y[i - 1] + (l1[i] + 2.0*l2[i] + 2.0*l3[i] + l4[i]) / 6.0;
        z[i] = z[i - 1] + (m1[i] + 2.0*m2[i] + 2.0*m3[i] + m4[i]) / 6.0;


        // delta
        k1[i] = h * jd1(dq1[i - 1], dq2[i - 1], dq3[i - 1], x[i], z[i]);
        l1[i] = h * jd2(dq1[i - 1], dq2[i - 1], dq3[i - 1], y[i], z[i]);
        m1[i] = h * jd3(dq1[i - 1], dq2[i - 1], dq3[i - 1], x[i], y[i], z[i]);

        k2[i] = h * jd1(dq1[i - 1] + k1[i]/2.0, dq2[i - 1] + l1[i]/2.0, dq3[i - 1] + m1[i]/2.0, x[i], z[i]);
        l2[i] = h * jd2(dq1[i - 1] + k1[i]/2.0, dq2[i - 1] + l1[i]/2.0, dq3[i - 1] + m1[i]/2.0, y[i], z[i]);
        m2[i] = h * jd3(dq1[i - 1] + k1[i]/2.0, dq2[i - 1] + l1[i]/2.0, dq3[i - 1] + m1[i]/2.0, x[i], y[i], z[i]);

        k3[i] = h * jd1(dq1[i - 1] + k2[i]/2.0, dq2[i - 1] + l2[i]/2.0, dq3[i - 1] + m2[i]/2.0, x[i], z[i]);
        l3[i] = h * jd2(dq1[i - 1] + k2[i]/2.0, dq2[i - 1] + l2[i]/2.0, dq3[i - 1] + m2[i]/2.0, y[i], z[i]);
        m3[i] = h * jd3(dq1[i - 1] + k2[i]/2.0, dq2[i - 1] + l2[i]/2.0, dq3[i - 1] + m2[i]/2.0, x[i], y[i], z[i]);

        k4[i] = h * jd1(dq1[i - 1] + k3[i], dq2[i - 1] + l3[i], dq3[i - 1] + m3[i], x[i], z[i]);
        l4[i] = h * jd2(dq1[i - 1] + k3[i], dq2[i - 1] + l3[i], dq3[i - 1] + m3[i], y[i], z[i]);
        m4[i] = h * jd3(dq1[i - 1] + k3[i], dq2[i - 1] + l3[i], dq3[i - 1] + m3[i], x[i], y[i], z[i]);

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

        // fprintf(fp, "%lf %lf \n", t, sum(logd)/t);
    }

    // fclose(fp);

    return sum(logd) / T;

}




int main(int argc, char const *argv[])
{
    double lambda = 0.0;
    
    lambda = runge_kutta();
    cout << lambda << endl;
    
    return 0;
}
