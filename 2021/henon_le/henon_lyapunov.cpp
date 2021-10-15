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
double df1(double q1, double q2, double x){

    return -2.0*x*q1 + 0.3*q2;
}

double df2(double q1){

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

    double T = 500;
    vector<double> x(T);
    vector<double> y(T);
    vector<double> dx(T);
    vector<double> dy(T);

    vector<double> sumlog(T);

    double x0 = 0.0;
    double y0 = 0.0;
    double dnorm = 0.0;

    x[0] = x0;
    y[0] = y0;
    dx[0] = df1(1.0, 0.0, x[0]);
    dy[0] = df2(1.0);
    dnorm = norm(dx[0], dy[0]);
    dx[0] = dx[0] / dnorm;
    dy[0] = dy[0] / dnorm;
    sumlog[0] = log(dnorm);


    for (int i = 1; i < T; i++)
    {
        x[i] = f1(x[i - 1], y[i - 1]);
        y[i] = f2(x[i - 1]);

        dx[i] = df1(dx[i - 1], dy[i - 1], x[i]);
        dy[i] = df2(dx[i - 1]);

        dnorm = norm(dx[i], dy[i]);
        sumlog[i] = log(dnorm);

        // normalization
        dx[i] = dx[i] / dnorm;
        dy[i] = dy[i] / dnorm;

    }

    return sum(sumlog) / T;

}




int main(int argc, char const *argv[])
{
    cout << algorithm() << endl;
    
    return 0;
}
