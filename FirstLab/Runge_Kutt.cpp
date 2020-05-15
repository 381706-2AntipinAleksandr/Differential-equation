#include <cmath>
#include "Runge_Kutt.h"

double coef1 = 1.0;

void init(double coef_1) {
    coef1 = coef_1;
}

// Уравнение маятника с диссипацией
double func(double x, double y, double z) {
    return -coef1 * z - sin(y);
}

// Рунге-Кутт
void Runge_Kutt(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z,
    double t0, double t1, double h, double eps) {
    size_t i = 0;
    while (t0 < t1) {
        // вычисление коэффициентов
        double k1 = h * z[i];
        double q1 = h * func(x[i], y[i], z[i]);

        double k2 = h * (z[i] + q1 / 2);
        double q2 = h * func(x[i] + h / 2, y[i] + k1 / 2, z[i] + q1 / 2);

        double k3 = h * (z[i] + q2 / 2);
        double q3 = h * func(x[i] + h / 2, y[i] + k2 / 2, z[i] + q2 / 2);

        double k4 = h * (z[i] + q2);
        double q4 = h * func(x[i] + h, y[i] + k3, z[i] + q3);

        double yt = y[i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        double zt = z[i] + (q1 + 2 * q2 + 2 * q3 + q4) / 6;

        if (eps > 0)
        {
            h /= 2; // уменьшаем шаг в 2 раза и проходим раза по промежутку
            double ux_temp = y[i];
            double uy_temp = z[i];
            for (int j = 0; j < 2; j++)
            {
                double uk1 = h * z[i];
                double ul1 = h * func(x[i], y[i], z[i]);

                double uk2 = h * (z[i] + q1 / 2);
                double ul2 = h * func(x[i] + h / 2, y[i] + k1 / 2, z[i] + q1 / 2);

                double uk3 = h * (z[i] + q2 / 2);
                double ul3 = h * func(x[i] + h / 2, y[i] + k2 / 2, z[i] + q2 / 2);

                double uk4 = h * (z[i] + q2);
                double ul4 = h * func(x[i] + h, y[i] + k3, z[i] + q3);

                ux_temp += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
                uy_temp += (q1 + 2 * q2 + 2 * q3 + q4) / 6;
            }

            double S = abs((yt - ux_temp) / 15); // высчитываем погрешность
            if (S > eps) {
                continue;
                //если погрешность не устраивает, уменьшаем шаг, считаем заново
                //добавления точек при этом не происходит и i не увеличивается
            }
            else if (S < eps / 32) { //если вычисления слишком точные, то увеличиваем шаг
                h *= 2; // шаг можно увеличить
            }
            h *= 2; // т.к. мы перед этим уменьшали в 2 раза, т.е. возвращаем в исходное
        }

        x.push_back(x[i] + h);
        y.push_back(yt);
        z.push_back(zt);
        ++i;
        t0 += h;
    }
}