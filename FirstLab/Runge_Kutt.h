#pragma once
#include <vector>

void init(double coef_1, double coef_2, double coef_3, double coef_4);

double func(double x, double y, double z);

void Runge_Kutt(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z,
    double t0, double t1, double h);