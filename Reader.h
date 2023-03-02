//
// Created by vadim on 02.03.2023.
//

#ifndef NUMERICALMETHODS_READER_H
#define NUMERICALMETHODS_READER_H

#include <iostream>

template<class T>
class Reader {
public:
    Reader() = default;

    explicit Reader(bool off) {
        this->off = off;
    }

    T Read(const std::string &text, const T defaultVar = T()) {
        if (off)
            return defaultVar;
        T var;
        std::cout << text;
        std::cin >> var;
        return var;
    }

private:
    bool off;
};


#endif //NUMERICALMETHODS_READER_H
