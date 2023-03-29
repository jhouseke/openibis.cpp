#include <fftw3.h>
#include <cmath>
using namespace std;

std::vector<double> fft(std::vector<double> x) {
    int N = x.size();
    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    for (int i = 0; i < N; i++) {
        in[i][0] = x[i];
        in[i][1] = 0;
    }

    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    std::vector<double> result(N);
    for (int i = 0; i < N; i++) {
        result[i] = sqrt(pow(out[i][0], 2) + pow(out[i][1], 2));
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    return result;
}