//
// Created by vadim on 03.05.2023.
//

#include "lab4.h"
#include "../NumericalMethods.h"
#include "../Reader.h"

#include <cmath>

double fx0(double x) {
    return 1;
}

double dFx0(double x) {
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
    std::function<double(double)> func = fx3;
    std::function<double(double)> dFunc = dFx3;
    auto reader = Reader<double>();
    auto readerInt = Reader<int>();
    double a = reader.Read("a=", 0), b = reader.Read("b=", 1);
    int n = readerInt.Read("m=", 10);

    NumericalMethods methods = NumericalMethods(func, NOTHING);
    double accurateDf = dFunc(b) - dFunc(a);
    std::cout << "Area= " << accurateDf << '\n';
    vector<Root> area;

    for (int i = LEFT_RECTANGLE_AREA; i <= THREE_EIGHTHS_AREA; ++i) {
        area.push_back(methods.CalculateArea(AreaFunc(i), a, b, n));
    }

    vector<std::string> methodNames = {"LeftRectangleArea", "RightRectangleArea", "MediumRectangleArea",
                                       "TrapezoidArea", "SimpsonArea", "ThreeEighthsArea"};
    for (int i = 0; i < area.size(); ++i) {
        std::cout << methodNames[i] << '\n';
        std::cout << "area = " << area[i].root << '\n';
        std::cout << "delta = " << std::abs(area[i].root - accurateDf) << '\n';
        std::cout << "theoretical delta: " << area[i].delta << '\n' << '\n';
    }
}

[[maybe_unused]] void lab4_3() {
    std::function<double(double)> func = fx3;
    std::function<double(double)> dFunc = dFx3;
    auto reader = Reader<double>();
    auto readerInt = Reader<int>();
    double a = reader.Read("a=", 0), b = reader.Read("b=", 1);
    int n = readerInt.Read("m=", 1), l = readerInt.Read("l=", 10);

    NumericalMethods methods = NumericalMethods(func, NOTHING);
    double accurateDf = dFunc(b) - dFunc(a);
    std::cout << "Area: " << accurateDf << '\n';

    vector<std::string> methodNames = {"LeftRectangleArea", "RightRectangleArea", "MediumRectangleArea",
                                       "TrapezoidArea", "SimpsonArea", "ThreeEighthsArea"};

    for (int i = LEFT_RECTANGLE_AREA; i <= SIMPSON_AREA; ++i) {
        Root area = methods.CalculateArea(AreaFunc(i), a, b, n);
        std::cout << methodNames[i] << '\n';
        std::cout << "--m--" << '\n';
        std::cout << "area = " << area.root << '\n';
        std::cout << "delta = " << std::abs(area.root - accurateDf) << '\n';
        std::cout << "theoretical delta: " << area.delta << "\n\n";

        Root area2 = methods.CalculateArea(AreaFunc(i), a, b, n*l);
        std::cout << "--m*l--" << '\n';
        std::cout << "area = " << area2.root << '\n';
        std::cout << "delta = " << std::abs(area2.root - accurateDf) << '\n';
        std::cout << "theoretical delta: " << area2.delta << "\n\n";

        double area3 = methods.RungeArea(AreaFunc(i), a, b, n, l);
        std::cout << "Runge " + methodNames[i] << '\n';
        std::cout << "area = " << area3 << '\n';
        std::cout << "delta = " << std::abs(area3 - accurateDf) << "\n\n";
    }
}