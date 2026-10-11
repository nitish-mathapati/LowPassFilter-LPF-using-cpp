#include <iostream>
#include "pHelpers.hpp"
#include "signalFlow.hpp"

Vector_VecD SignalFlow::splitter(const VecD& input, int numChannels){
    Vector_VecD output;
    if(numChannels <= 0) {
        std::cerr << "Error: Number of channels must be greater than zero." << std::endl;
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
