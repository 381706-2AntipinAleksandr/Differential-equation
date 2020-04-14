#include "Runge_Kutt.h"

double coef1 = 1.0, coef2 = 1.0, coef3 = 2.0, coef4 = 0.8;

void init(double coef_1, double coef_2, double coef_3, double coef_4) {
    coef1 = coef_1; coef2 = coef_2;
    coef3 = coef_3; coef4 = coef_4;
}

double func(double x, double y, double z) {
    return (coef2 * x * z - coef3 * x * y - coef4) / coef1;
}

void Runge_Kutt(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z,
    double t0, double t1, double h) {
    size_t i = 0;
    while (t0 < t1 - 0.00000001) {
        double k1 = z[i];
        double q1 = func(x[i], y[i], z[i]);

        double k2 = z[i] + q1 * h / 2;
        double q2 = func(x[i] + h / 2, y[i] + k1 * h / 2, z[i] + q1 * h / 2);

        double k3 = z[i] + q2 * h / 2;
        double q3 = func(x[i] + h / 2, y[i] + k2 * h / 2, z[i] + q2 * h / 2);

        double k4 = z[i] + q2 * h;
        double q4 = func(x[i] + h, y[i] + k3 * h, z[i] + q3 * h);

        double yt = y[i] + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        double zt = z[i] + h * (q1 + 2 * q2 + 2 * q3 + q4) / 6;

        x[i + 1] = x[i] + h;
        y[i + 1] = yt;
        z[i + 1] = zt;
        ++i;
        t0 += h;
    }
}