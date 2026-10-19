#ifndef signal_gen_hpp
#define signal_gen_hpp

#include <iostream>
#include <vector>
#include <cmath>
#include "pHelpers.hpp"
#include "signalFlow.hpp"


class SineSignal : public SignalFlow {

public:
    VecD SineSignalGen(
        double freq,
        double sample_rate,
        int samples,
        double amplitude);
};


VecD SineSignal::SineSignalGen(
    double freq,
    double sample_rate,
    int samples,
    double amplitude)
{
    VecD signal(samples);
    for(int n=0; n<samples; n++){
        signal[n] = amplitude * sin(2 * M_PI * freq * n/static_cast<double>(sample_rate));
    }
    return signal;
}

#endif // signal_gen_hpp