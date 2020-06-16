//
// Created by chenh on 6/16/2020.
//

#include "_utility.h"
using namespace std;

int operator*(const std::vector<int> &left, const std::vector<int> &right) {
    size_t min_len = left.size() < right.size() ? left.size() : right.size();
    int result = 0;
    for (int i = 0; i < min_len; i++) {
        result += left[i] * right[i];
    }
    return result;
}

std::vector<int> operator+(const std::vector<int> &left, const std::vector<int> &right) {
    size_t min_len = left.size() < right.size() ? left.size() : right.size();
    vector<int> ret(min_len, 0);
    for (size_t i = 0; i < min_len; i++) {
        ret[i] = left[i] + right[i];
    }
    return ret;
}

