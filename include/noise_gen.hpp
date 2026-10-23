#ifndef noise_gen_hpp
#define noise_gen_hpp

#include <iostream>
#include <random>
#include "signal_gen.hpp"
#include "pHelpers.hpp"
#include "signalFlow.hpp"


class NoiseGenerator : public SignalFlow {

public:

    VecD NoiseGen(long int signalSamples);

    VecD NoiseGen(double N_amp, int N_samp);
};


inline VecD NoiseGenerator::NoiseGen(long int signalSamples)
{
    std::cout<< "Enter noise amplitude: "<< std::endl;
    if (!(std::cin >> SignalFlow::N_amp)) {
        throw std::runtime_error("Invalid noise amplitude.");
    }
    std::cout<< "Enter number of noise samples: "<< std::endl;
    if (!(std::cin >> SignalFlow::N_samp)) {
        throw std::runtime_error("Invalid number of noise samples. It must match the number of signal samples.");
    }
    if (signalSamples != SignalFlow::N_samp) {
        std::cout << "samples: " << signalSamples << ", N_samp: " << SignalFlow::N_samp << std::endl;
        throw std::runtime_error("Number of noise samples must match the number of signal samples.");
    }

    return NoiseGen(SignalFlow::N_amp, SignalFlow::N_samp);
}


// Noise Generator
VecD NoiseGenerator::NoiseGen(double N_amp, int N_samp)
{

    VecD noise(N_samp);

    std::ofstream nFile("data/noise.csv");
    if (!nFile) {
        throw std::runtime_error("Could not open data/noise.csv for writing.");
    }

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

    for(int n=0; n<N_samp; n++){
        noise[n] = noiseDist(gen);
        nFile<< n << "," << noise[n]<< std::endl;
    }
    nFile.close();
    return noise;
}

#endif // noise_gen_hpp