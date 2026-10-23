#ifndef noisySignal_hpp
#define noisySignal_hpp

#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include "signal_gen.hpp"
#include "noise_gen.hpp"
#include "pHelpers.hpp"
#include "signalFlow.hpp"


class NoisySignal : public SignalFlow {

public:

    VecD NoisySignalGen(const VecD& signal, const VecD& noise, double sampleRate);

    VecD NoisySignalGen(
        double freq,
        double sample_rate,
        int samples,
        double amplitude,
        double N_amp,
        int N_samp);
    
    NoiseGenerator NG;
    SineSignal SG;

};

inline VecD NoisySignal::NoisySignalGen(
    const VecD& signal, const VecD& noise, double sampleRate)
{
    if (signal.empty() || signal.size() != noise.size()) {
        throw std::runtime_error("Signal and noise must have the same positive sample count.");
    }
    if (!std::isfinite(sampleRate) || sampleRate <= 0.0) {
        throw std::runtime_error("Sample rate must be finite and positive.");
    }

    std::ofstream noisyFile("data/noisySignal.csv");
    if (!noisyFile) {
        throw std::runtime_error("Could not open data/noisySignal.csv for writing.");
    }

    VecD noisySignal(signal.size());
    for (std::size_t n = 0; n < signal.size(); ++n) {
        noisySignal[n] = signal[n] + noise[n];
        noisyFile << n / sampleRate << "," << noisySignal[n] << "\n";
    }
    noisyFile.close();
    return noisySignal;
}

// Here in this func, we generate a sineWave and add noise to it, returning the noisy signal
VecD NoisySignal::NoisySignalGen(
    double freq,
    double sample_rate,
    int samples,
    double amplitude,
    double N_amp,
    int N_samp)
{

    if (samples <= 0 || samples != N_samp) {
        throw std::runtime_error("Signal and noise must have the same positive sample count.");
    }

    VecD signal = SG.SineSignalGen(freq, sample_rate, samples, amplitude);
    VecD noise = NG.NoiseGen(N_amp, N_samp);

    return NoisySignalGen(signal, noise, sample_rate);
}

#endif // noisySignal_hpp