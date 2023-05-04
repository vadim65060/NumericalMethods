//
// Created by vadim on 03.05.2023.
//

#include "lab4.h"
#include "../NumericalMethods.h"
#include "../Reader.h"

#include <cmath>

double fx0(double x){
    return 1;
}

double dFx0(double x){
    return x;
}

double fx1(double x) {
    return x;
}

double dFx1(double x) {
    return x * x / 2;
}

double fx2(double x) {
    return x * x;
}

double dFx2(double x) {
    return 1.0 / 3 * x * x * x;
}

double fx3(double x) {
    return x * x * x;
}

double dFx3(double x) {
    return 1.0 / 4 * x * x * x * x;
}

double fSin(double x) {
    return std::sin(x);
}

double dfSin(double x) {
    return -std::cos(x);
}

[[maybe_unused]] void lab4() {
    std::function<double(double)> func = fx1;
    std::function<double(double)> dFunc = dFx1;
    auto reader = Reader<double>(true);
    double a = reader.Read("a=", 0), b = reader.Read("b=", 1);
    int n = 1;

    NumericalMethods methods = NumericalMethods(func, NOTHING);
    double accurateDf = dFunc(b) - dFunc(a);

    vector<double> area = {methods.LeftRectangleArea(a, b, n), methods.RightRectangleArea(a, b, n),
                           methods.MediumRectangleArea(a, b, n), methods.TrapezoidArea(a, b, n),
                           methods.SimpsonArea(a, b, n), methods.ThreeEighthsArea(a, b, n)};
    vector<std::string> methodNames = {"LeftRectangleArea", "RightRectangleArea", "MediumRectangleArea",
                                       "TrapezoidArea", "SimpsonArea", "ThreeEighthsArea"};
    for (int i = 0; i < area.size(); ++i) {
        std::cout << methodNames[i] << '\n';
        std::cout << "area = " << area[i] << '\n';
        std::cout << "delta = " << std::abs(area[i] - accurateDf) << '\n' << '\n';
    }


}