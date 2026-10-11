#ifndef noisySignal_hpp
#define noisySignal_hpp

#include <iostream>
#include <random>
#include "signal_gen.hpp"
#include "noise_gen.hpp"
#include "pHelpers.hpp"

// Here in this func, we generate a sineWave and add noise to it, returning the noisy signal
VecD NoisySignalGen(
    double freq,
    double sample_rate,
    int samples,
    double amplitude,
    double N_amp,
    int N_samp)
{
    VecD signal = SineGen(freq, sample_rate, samples, amplitude);
    VecD noise = NoiseGen(N_amp, N_samp);

    /* Here we combine the sine wave and noise to create a noisy signal.
    *  The noise is added to the sine wave sample by sample.
    *  The resulting noisy signal is returned as a vector of doubles.
    *
    */
    VecD NoisySignal(samples);
    for(int n=0; n<samples; n++){
        NoisySignal[n] = signal[n] + noise[n];
    }

    return NoisySignal;
}

#endif // noisySignal_hpp