#ifndef lpf_hpp
#define lpf_hpp

#include <iostream>
#include <cmath>
#include "noisySignal.hpp"
#include "signal_gen.hpp"
#include "pHelpers.hpp"
#include "signalFlow.hpp"


class LowPassFilterClass : public SignalFlow {

public:
    VecD LowPassFilter(
        const VecD& input,
        double cutoff_freq,
        double sample_rate);
};



// Cascaded first-order IIR low-pass filter.
// Repeating the same RC stage improves attenuation of high-frequency noise
// while preserving the existing function signature.
inline VecD LowPassFilterClass::LowPassFilter(
	const VecD& input,
	double cutoff_freq,
	double sample_rate)
{
	if (input.empty() || cutoff_freq <= 0.0 || sample_rate <= 0.0) {
		return input;
	}

	// constexpr double PI = 3.14159265358979323846;
	constexpr int stage_count = 4;
	const double dt = 1.0 / sample_rate;
	const double stage_cutoff_scale = std::sqrt(std::pow(2.0, 1.0 / stage_count) - 1.0);
	const double stage_cutoff_freq = cutoff_freq / stage_cutoff_scale;
	const double rc = 1.0 / (2.0 * M_PI * stage_cutoff_freq);
	const double alpha = dt / (rc + dt);

	VecD output = input;
	VecD stage_output(input.size());

	for (int stage = 0; stage < stage_count; ++stage) {
		stage_output[0] = output[0];

		for (size_t n = 1; n < output.size(); ++n) {
			stage_output[n] = stage_output[n - 1] + alpha * (output[n] - stage_output[n - 1]);
		}

		output.swap(stage_output);
	}

	return output;
}



#endif // lpf_hpp