This project is related to digital signal processing (DSP).
It implements a cascaded first-order IIR (Infinite Impulse Response) low-pass filter to remove high-frequency noise from a signal while preserving its low-frequency components.
The project generates a clean sine wave, adds Gaussian white noise to create a noisy signal, and then applies the low-pass filter to recover the desired signal.

This is the structure folder of the project
LPF/
│
├── data/
├── helpers/
├── include/
├── scripts/
└── src/


-----------------------------------------------------------------------------------------------------------------------------------------------


data/
Stores generated signal data and output artifacts.
1. Stores signal samples in .csv format.
2. Stores plotted signal images (.png).

helpers/
Contains common utilities used throughout the project.
1. Custom type aliases.
2. Macros and helper definitions.

include/
Contains all project header files.
1. Signal generation modules.
2. Noise generation modules.
3. Filter implementation.
4. Utility headers.

scripts/
Contains Python scripts used for visualization and data export.
1. Plots generated signals.
2. Saves data in .csv format.
3. Generates signal plots in .png format.

src/
Contains the application's entry point.
1. The program execution starts from main.cpp.


-----------------------------------------------------------------------------------------------------------------------------------------------


Project Design

1. SineGen()
Purpose
SineGen() generates a discrete-time sinusoidal (sine wave) signal and returns the generated samples as a VecD (std::vector<double>).

Functionality
1. Creates a vector of size samples.
2. Computes each sample using the discrete-time sine-wave equation.
3. Calculates the sine value for every sample index.
4. Scales the result using the specified amplitude.
5. Stores the generated sample in the output vector.

Output
Returns a VecD containing the generated sine-wave samples.

----------------------

2. NoiseGen()
Purpose
NoiseGen() generates a sequence of random Gaussian (white noise) samples and returns them as a VecD (std::vector<double>).

Functionality
Generates noise samples with a mean value of 0.
Uses a Gaussian (normal) distribution.
Controls the noise level using the parameter N_amp.
Produces statistically independent noise samples.

Output
Returns a VecD containing N_samp randomly generated noise samples.

----------------------

3. NoisySignalGen()
Purpose
NoisySignalGen() generates a noisy sine-wave signal by combining a clean sinusoidal signal with randomly generated Gaussian noise.

Functionality
Generates a clean sine wave using SineGen().
Generates Gaussian white noise using NoiseGen().
Adds the generated noise to the sine wave on a sample-by-sample basis.
Produces a noisy version of the original signal.

Output
Returns a VecD containing the sine wave corrupted by Gaussian noise.

Process
A pure sinusoidal signal is generated using the specified frequency, sampling rate, amplitude, and sample count.
A Gaussian white-noise sequence is generated with zero mean and a noise level controlled by N_amp.
Each noise sample is added to the corresponding sine-wave sample.
The resulting signal simulates a real-world noisy measurement.

----------------------

4. LowPassFilter()
Purpose
LowPassFilter() applies a cascaded first-order IIR low-pass filter to an input signal.

Functionality
Attenuates high-frequency components, such as noise.
Preserves the desired low-frequency signal content.
Uses multiple cascaded first-order stages to achieve a steeper roll-off than a single-stage filter.
Returns the original signal unchanged if:
The input signal is empty.
The cutoff frequency is invalid.
The sampling rate is invalid.

Filter Calculations 
The filter is based on a first-order RC low-pass filter.
The following parameters are calculated:
Sampling interval (dt)
RC time constant (RC)
Smoothing coefficient (alpha)
Stage cutoff frequency

Multi-Stage Filtering
The signal is passed through four identical first-order IIR filter stages.
Each stage progressively reduces high-frequency content, resulting in stronger attenuation above the specified cutoff frequency.

Output
Returns a VecD containing the filtered signal.

{   Filter Design Summary
    LowPassFilter() implements a four-stage cascaded first-order IIR low-pass filter.
    The filter uses a recursive RC-based formulation to smooth the input signal and 
    suppress high-frequency noise. By cascading multiple filter stages, the overall 
    response achieves significantly stronger attenuation beyond the cutoff frequency 
    while maintaining low computational complexity, making it suitable for real-time DSP applications.  }


-----------------------------------------------------------------------------------------------------------------------------------------------


Future Enhancements

The project is currently under development, and several enhancements are planned for future implementation:
1. Implement a small signal-flow framework to model and process audio signals through multiple processing blocks.
2. Add a splitter block to divide the signal into two independent processing paths.
3. Configure one path as a direct path, where the signal is forwarded to the output without any additional processing.
4. Route the second path through one or more gain blocks and introduce a router block to manage signal routing.
5. Measure and analyze the delay introduced by each processing path to ensure proper signal synchronization.
6. Evaluate the overall system behavior and optimize the signal-flow architecture as needed.
7. Additional features and enhancements will be incorporated as the project evolves.