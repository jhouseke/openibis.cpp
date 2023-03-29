#include "helpers.h"
using namespace std;

int main() {
    // Test case 1
    vector<double> x1 = {-2.0, -1.0, 0.0, 1.0, 2.0};
    vector<double> xp1 = {-1.0, 0.0, 1.0};
    vector<double> yp1 = {0.0, 1.0, 0.0};
    vector<double> expected1 = {0.0, 0.5, 1.0, 0.5, 0.0};
    vector<double> result1 = piecewise(x1, xp1, yp1);
    if (result1 != expected1) {
        std::cerr << "Test case 1 failed" << std::endl;
    }

    // Test case 2
    vector<double> x2 = {-2.0, -1.0, 0.0, 1.0, 2.0};
    vector<double> xp2 = {-2.0, 0.0, 2.0};
    vector<double> yp2 = {1.0, 0.0, 1.0};
    vector<double> expected2 = {1.0, 0.5, 0.0, 0.5, 1.0};
    vector<double> result2 = piecewise(x2, xp2, yp2);
    if (result2 != expected2) {
        std::cerr << "Test case 2 failed" << std::endl;
    }

    // Test case 3
    vector<double> x3 = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    vector<double> xp3 = {1.0, 4.0, 7.0};
    vector<double> yp3 = {2.0, 1.0, 3.0};
    vector<double> expected3 = {0.0, 2.0, 1.0, 1.0, 3.0, 3.0, 3.0, 2.0, 0.0, 0.0};
    vector<double> result3 = piecewise(x3, xp3, yp3);
    if (result3 != expected3) {
        std::cerr << "Test case 3 failed" << std::endl;
    }

    std::cout << "All test cases passed" << std::endl;
    return 0;
}

