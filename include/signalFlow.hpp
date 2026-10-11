#ifndef signalFlow_hpp
#define signalFlow_hpp

#include <iostream>
#include "pHelpers.hpp"

class SignalFlow {
public:
    // Function to split a signal
    Vector_VecD splitter(const VecD& input, int numChannels);

}; // class SignalFlow

#endif // signalFlow_hpp