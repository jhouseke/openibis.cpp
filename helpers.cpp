#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <algorithm>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

tuple<int, double> number_of_epochs(vector<double> eeg, double stride = 0.5, int Fs = 128) {
    int nStride = Fs * stride;
    int nEpochs = floor((eeg.size() - Fs) / nStride) - 10;
    return make_tuple(nEpochs, nStride);
}

bool isNotBurstSuppressed(std::vector<bool> bsrmap, int n, int strides) {
    /* Checks for burst suppression

    Args:
        bsrmap (std::vector<bool>): BSR map
        n (int): epoch number
        strides (int): number of strides

    Returns:
        bool: True if not burst suppressed
    */
    if (n < strides) {
        return true;
    } else if (std::any_of(bsrmap.begin() + n, bsrmap.begin() + n + strides, [](bool b) {return b;})) {
        // if any of the bsr map is true (there is burst suppression)
        return false;
    } else { 
        return true;
    }
}

std::vector<double> get_segment(std::vector<double> eeg, int start, int number, int nStride = 64) {
    int a = start * nStride;
    int b = (number * nStride) + a;
    std::vector<double> seg(eeg.begin() + a, eeg.begin() + b);
    return seg;
}

vector<double> piecewise(vector<double> x, vector<double> xp, vector<double> yp) {
    vector<bool> cl;
    vector<bool> x_temp;
    vector<bool> x_temp2;

    //construct boolean vectors based on x
    for (size_t i = 0; i < xp.size()-1; i++) {
        x_temp.push_back(x >= xp[i]);
        x_temp2.push_back(x <= xp[i+1]);
    }
    
    for (size_t i = 0; i < x_temp.size()-1; i++) {
        cl.push_back(x_temp[i] && x_temp2[i]);
    }
    return std::piecewise_construct(x.begin(), x.end(), cl.begin(), yp.begin());
}

vector<double> baseline(vector<double> y, int deg=3, int max_it=100, double tol=1e-3) {
    int order = deg + 1;
    VectorXd coeffs = VectorXd::Ones(order);

    // try to avoid numerical issues
    double cond = pow(abs(*max_element(y.begin(), y.end())), 1.0 / order);
    VectorXd x = VectorXd::LinSpaced(y.size(), 0.0, cond);
    VectorXd base = Map<VectorXd>(y.data(), y.size());

    MatrixXd vander = MatrixXd::Ones(y.size(), order);
    for (int i = 0; i < order; i++) {
        vander.col(i) = x.array().pow(i);
    }

    // Pseudo-inverse of Vandermonde matrix
    MatrixXd vander_pinv = vander.completeOrthogonalDecomposition().pseudoInverse();

    for (int i = 0; i < max_it; i++) {
        VectorXd coeffs_new = vander_pinv * base;

        if ((coeffs_new - coeffs).norm() / coeffs.norm() < tol) {
            break;
        }

        coeffs = coeffs_new;
        base = vander * coeffs;
        base = base.array().min(Map<VectorXd>(y.data(), y.size()));
    }

    vector<double> baseline_values(base.data(), base.data() + base.size());
    return baseline_values;
}

std::vector<double> logistic(std::vector<double> x, double L=1, double x_0=0, double k=1) {
    std::vector<double> result(x.size());
    for (int i = 0; i < x.size(); i++) {
        result[i] = L / (1 + exp(-k * (x[i] - x_0)));
    }
    return result;
}

