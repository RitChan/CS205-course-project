#include "matrix.h"
#include "simple_ann.h"
#include <iostream>
#include "_utility.h"
#include <cstdio>

using namespace std;

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
        cout << i << " ";
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