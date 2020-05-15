#pragma once
#include <vector>

void init(double coef_1);

double func(double x, double y, double z);

void Runge_Kutt(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z,
    double t0, double t1, double h, double eps);