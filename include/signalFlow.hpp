#ifndef signalFlow_hpp
#define signalFlow_hpp

#include <iostream>
#include "pHelpers.hpp"

class SignalFlow {
public:
    // Function to split a signal
    Vector_VecD splitter(const VecD& input, int numChannels);

protected:
    double freq, sample_rate, amplitude, N_amp, cutoff_freq;
    int samples, N_samp;

}; // class SignalFlow


Vector_VecD SignalFlow::splitter(const VecD& input, int numChannels){
    Vector_VecD output;
    if(numChannels <= 1) {
        std::cerr << "Error: Number of channels must be greater than one." << std::endl;
        return output; // Return empty output
    }

    // Split the input signal into numchannels
    output.resize(numChannels);
    for(int ch=0; ch<numChannels; ch++){
        // Fill each channel with the input signal
        output[ch] = input;
    }
    return output;
}

#endif // signalFlow_hpp