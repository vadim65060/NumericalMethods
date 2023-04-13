//
// Created by vadim on 29.03.2023.
//

#include "lab3.h"

#include <cmath>
#include <iomanip>
#include "../NumericalMethods.h"
#include "../Reader.h"

double func3(double x) {
    return std::sin(x) + (x * x) / 2;
}

double func3_2(double x) {
    int k = 11 % 5 + 1;
    return exp(1.5 * k * x);
}

double dFunc3_2(double x) {
    int k = 11 % 5 + 1;
    return k * 1.5 * exp(1.5 * k * x);
}

double ddFunc3_2(double x) {
    int k = 11 % 5 + 1;
    return std::pow(k * 1.5, 2) * exp(1.5 * k * x);
}

vector<pair<double, double>> SwapTable(const vector<pair<double, double>> &table) {
    vector<pair<double, double>> swappedTable = table;
    for (auto &el: swappedTable) {
        std::swap(el.first, el.second);
    }
    return swappedTable;
}

void AddVectorToTable(vector<vector<double>> &table, const vector<double> &vector1) {
    for (int i = 0; i < vector1.size(); ++i) {
        table[i].push_back(vector1[i]);
    }
}

[[maybe_unused]] void lab3() {
    auto reader = Reader<double>(true);
    auto intReader = Reader<int>(true);
    int m = intReader.Read("m+1=", 10) - 1;
    double a = reader.Read("a=", 0), b = reader.Read("b=", 1);
    auto methods = NumericalMethods(func3, NOTHING);
    Logger logger = Logger();
    vector<pair<double, double>> table = methods.GetFuncValueTable(a, b, m);
    vector<pair<double, double>> swappedTable = SwapTable(table);
    logger.Log("table", table, ANSWER);
    std::cout << std::endl;
    while (true) {
        double x = reader.Read("x=", 0.81);
        methods.SortTableForDX(table, x);
        methods.SortTableForDX(swappedTable, x);

        int n = intReader.Read("(n<=" + std::to_string(m) + ")n=", 10);
        while (n > m) {
            n = intReader.Read("(n<=" + std::to_string(m) + ")n=", 7);
        }

        Root root = methods.InterpolationNewtonMethod(swappedTable, x, n);
        std::cout << "X=" << root.root << std::endl;
        std::cout << "|f(x)-F|=" << std::abs(func3(root.root) - x) << std::endl;

        auto coefficients = methods.InterpolationNewtonCoefficients(table, n);
        auto func = methods.Polynomial(table, coefficients, x);
        auto methods2 = NumericalMethods(func, ANSWER);
        root = methods2.TangentsMethod(a, b);
        std::cout << "X=" << root.root << std::endl;
        std::cout << "|f(x)-F|=" << std::abs(func3(root.root) - x) << std::endl;
        break;
    }
}

[[maybe_unused]] void lab3_2() {
    auto reader = Reader<double>(true);
    auto intReader = Reader<int>(true);
    auto methods = NumericalMethods(func3_2, NOTHING);
    while (true) {
        int m = intReader.Read("m+1=", 10) - 1;
        double a = reader.Read("a=", 0), b = reader.Read("b=", 1);

        vector<pair<double, double>> table = methods.GetFuncValueTable(a, b, m);
        vector<vector<double>> tableDf(m + 1);

        for (int i = 0; i < m + 1; ++i) {
            tableDf[i].push_back(table[i].first);
            tableDf[i].push_back(table[i].second);
        }

        AddVectorToTable(tableDf, methods.TableDf(table));
        for (int i = 0; i < m + 1; ++i) {
            tableDf[i].push_back(std::abs(dFunc3_2(table[i].first) - tableDf[i][2]));
        }

        AddVectorToTable(tableDf, methods.TableDdf(table));
        for (int i = 0; i < m + 1; ++i) {
            tableDf[i].push_back(std::abs(ddFunc3_2(table[i].first) - tableDf[i][4]));
        }

//        double h = (b - a) / m;
//        for (int i = 0; i < m+1; ++i) {
//            double x = table[i].first;
//            tableDf[i].push_back(x);
//            tableDf[i].push_back(table[i].second);
//            tableDf[i].push_back(methods.df(x, h, i));
//            tableDf[i].push_back(std::abs(dFunc3_2(x) - tableDf[i][2]));
//            tableDf[i].push_back(methods.ddf(x, h, i));
//            tableDf[i].push_back(std::abs(ddFunc3_2(x) - tableDf[i][4]));
//        }
        Logger logger = Logger();
        int wrap = 14;
        std::cout << std::setw(wrap) << "x" << std::setw(wrap) << "f(x)" << std::setw(wrap) << "f'(x)"
                  << std::setw(wrap) << "|f'(x)|" << std::setw(wrap) << "f''(x)" << std::setw(wrap) << "|f''(x)|"
                  << std::endl;
        logger.Log("table", tableDf, ANSWER);
        break;
    }
}