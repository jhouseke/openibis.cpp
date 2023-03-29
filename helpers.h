#include <vector>
#include <iostream>

std::vector<double> piecewise(std::vector<double> x, std::vector<double> xp, std::vector<double> yp);

tuple<int, double> number_of_epochs(vector<double> eeg, double stride = 0.5, int Fs = 128);

bool isNotBurstSuppressed(std::vector<bool> bsrmap, int n, int strides);

std::vector<double> get_segment(std::vector<double> eeg, int start, int number, int nStride = 64);
