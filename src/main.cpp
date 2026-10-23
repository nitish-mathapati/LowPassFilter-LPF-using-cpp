#include <iostream>
#include <fstream>
#include <cstdlib>
#include "signal_gen.hpp"
#include "noise_gen.hpp"
#include "noisySignal.hpp"
#include "lpf.hpp"
#include "pHelpers.hpp"
#include "signalFlow.hpp"

int main(){

    // Instantiate signal generators and filter objects
    SineSignal sineGenerator;
    NoiseGenerator noiseGenerator;
    LowPassFilterClass filter;
    NoisySignal noisySignalGenerator;
    SignalFlow SignalFlowObj;

    VecD signal = sineGenerator.SineSignalGen();

    VecD noise = noiseGenerator.NoiseGen(sineGenerator.sSample);

    VecD noisySignal = noisySignalGenerator.NoisySignalGen(signal, noise, sineGenerator.getSampleRate());

    VecD filteredSignal = filter.LowPassFilter(noisySignal, sineGenerator.getSampleRate());

    // /*  The signal flow is split into multiple channels using
    // *   SignalFlow::splitter(const std::vector<double>& input, int numChannels)
    // *
    // *   Here the filtered signal is split into multiple channels for further processing.
    // */

    system("python ./scripts/plot.py");

    return 0;
}