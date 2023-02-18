//
// Created by vadim on 18.02.2023.
//

#ifndef NUMERICALMETHODS_ROOT_H
#define NUMERICALMETHODS_ROOT_H


class Root {
public:
    Root(double root, double delta, int k) {
        this->root = root;
        this->delta = delta;
        this->k = k;
    }

    double root, delta;
    int k;
};

#endif //NUMERICALMETHODS_ROOT_H