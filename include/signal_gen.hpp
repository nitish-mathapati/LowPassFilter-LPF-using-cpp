#ifndef signal_gen_hpp
#define signal_gen_hpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include "pHelpers.hpp"
#include "signalFlow.hpp"   


class SineSignal : public SignalFlow {

public:

    long int sSample;
    VecD SineSignalGen();
    double getSampleRate() const { return sample_rate; }

    VecD SineSignalGen(
        double freq,
        double sample_rate,
        int samples,
        double amplitude);
};


inline VecD SineSignal::SineSignalGen()
{
    std::cout<< "Enter frequency (Hz): "<< std::endl;
    if (!(std::cin >> freq)) {
        throw std::runtime_error("Invalid frequency.");
    }
    std::cout<< "Enter sample rate (Hz): "<< std::endl;
    if (!(std::cin >> sample_rate)) {
        throw std::runtime_error("Invalid sample rate.");
    }
    std::cout<< "Enter number of samples: "<< std::endl;
    if (!(std::cin >> samples)) {
        throw std::runtime_error("Invalid sample count.");
    }
    std::cout<< "Enter amplitude: "<< std::endl;
    if (!(std::cin >> amplitude)) {
        throw std::runtime_error("Invalid amplitude.");
    }
    if (!std::isfinite(freq) || !std::isfinite(sample_rate) ||
        !std::isfinite(amplitude) || sample_rate <= 0.0 || samples <= 0) {
        throw std::runtime_error("Frequency and amplitude must be finite; sample rate and sample count must be positive.");
    }

    return SineSignalGen(freq, sample_rate, samples, amplitude);
}

VecD SineSignal::SineSignalGen(
    double freq,
    double sample_rate,
    int samples,
    double amplitude)
{

    VecD signal(samples);
    sSample = samples;

    std::ofstream sFile("data/signal.csv");
    if (!sFile) {
        throw std::runtime_error("Could not open data/signal.csv for writing.");
    }

    for(int n=0; n<samples; n++){
        signal[n] = amplitude * sin(2 * M_PI * freq * n/static_cast<double>(sample_rate));
        double t = n / sample_rate;
        sFile<< t << "," << signal[n]<< std::endl;
    }
    sFile.close();
    return signal;
}

#endif // signal_gen_hpp