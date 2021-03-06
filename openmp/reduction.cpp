///
/// OpenMP example of reduction
///
#include<iostream>
#include<omp.h>
#include<chrono>
#include<random>

const int N = 10240;
double a[N], b[N];
const int MAX_VAL = 1024;

int main(){
    // Generating random numbers
    //
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> distribution(1,MAX_VAL);
    for (int i = 0; i < N; ++i) {
        a[i] = distribution(generator);
        b[i] = distribution(generator);
    }

    double sum = 0;
    // Parallel computation of scalar product
    #pragma omp parallel for shared(a) reduction(+:sum)
    for (int i = 0; i < N; ++i) {
        sum += a[i] * b[i];
    }


    std::cout << "Scalar product =  " << sum << std::endl;
}
