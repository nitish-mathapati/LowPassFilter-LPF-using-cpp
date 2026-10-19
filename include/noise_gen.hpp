#ifndef noise_gen_hpp
#define noise_gen_hpp

#include <iostream>
#include <random>
#include "signal_gen.hpp"
#include "pHelpers.hpp"
#include "signalFlow.hpp"


class NoiseGenerator : public SignalFlow {

public:
    VecD NoiseGen(double N_amp, int N_samp);
};


// Noise Generator
VecD NoiseGenerator::NoiseGen(double N_amp, int N_samp)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    /*@@@ Here the noise level depends on the stddev
    *     std::normal_distribution<double> noiseDist(mean, stddev);
    *     stddev = (amplitude / 3.0);       Adjust the standard deviation as needed
    *     
    *     stddev = 0.01;                    Very little noise
    *     stddev = 0.1;                     Moderate noise
    *     stddev = 0.5;                     High noise
    *     stddev = 1.0;                     Very high noise
    *     
    */
    std::normal_distribution<double> noiseDist(0.0, N_amp / 3.0); // Adjust the standard deviation as needed

    VecD noise(N_samp);
    for(int n=0; n<N_samp; n++){
        noise[n] = noiseDist(gen);
    }

    return noise;
}

#endif // noise_gen_hpp