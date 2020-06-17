#include "matrix.h"
#include "simple_ann.h"
#include <iostream>
#include <cstdio>

using namespace std;
using namespace mat;

static void run_network(const std::vector<int> &input);

int main() {
    // 识别代表0或1的12像素图片，每个像素只取0或1

    vector<int> input0{
            0, 1, 0,
            1, 0, 1,
            1, 0, 1,
            0, 1, 0
    };

    vector<int> input1{
            0, 1, 0,
            0, 1, 0,
            0, 1, 0,
            0, 1, 0
    };

    vector<int> input2{
            1, 1, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 1
    };

    run_network(input0);
    run_network(input1);
    run_network(input2);

    return 0;
}

static void run_network(const std::vector<int> &input) {
    // Weight matrix between layer 0 and layer 1
    static Matrix<int> L01{
            {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0}
    };

    // Weight matrix between layer 1 and layer 2
    static Matrix<int> L12{
            {1, 0, 1},
            {0, 1, 0}
    };

    cout << endl << "[Input]" << endl;
    int count = 0;
    for (int i: input) {
        if (i == 0)
            printf(".  ");
        else
            printf("%d  ", i);
        if ((count++) % 3 == 2)
            cout << endl;
    }

    auto &x0 = input;
    auto x1 = activate(L01 * x0);
    auto x2 = activate(L12 * x1);

    cout << endl << "[Output]" << endl;
    cout << "Zero: " << (x2[0] == 1 ? "Yes" : "No") << endl << "One: " << (x2[1] == 1 ? "Yes" : "No") << endl;
}

std::vector<int> activate(std::vector<int> input) {
    vector<int> ret(input.size(), 0);
    for (int i = 0; i < input.size(); i++) {
        if (input[i] > 0)
            ret[i] = 1;
        else
            ret[i] = 0;
    }
    return ret;
}

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