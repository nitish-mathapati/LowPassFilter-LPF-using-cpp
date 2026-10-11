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
    // Variables for signal generation
    double freq, sample_rate, amplitude;
    int samples;

    // Variables for noise generation
    double N_amp;
    int N_samp;

    // Variables for low-pass filter
    double cutoff_freq;




    /*  Sine wave is generated using 
    *   SineGen(double freq, double sample_rate, int samples, double amplitude)
    *   
    * 
    */
    std::cout<< "Enter frequency (Hz): "<< std::endl;
    std::cin>> freq;
    std::cout<< "Enter sample rate (Hz): "<< std::endl;
    std::cin>> sample_rate;
    std::cout<< "Enter number of samples: "<< std::endl;
    std::cin>> samples;
    std::cout<< "Enter amplitude: "<< std::endl;
    std::cin>> amplitude;

    std::ofstream file("data/signal.csv");

    VecD sine_Wave = SineGen(freq, sample_rate, samples, amplitude);
    std::cout<< "Generated signal: "<< std::endl;
    for(int n=0; n<samples; n++){
        double t = n/static_cast<double>(sample_rate);
        // std::cout<< sine_Wave[n]<< std::endl;
        file<< t << "," << sine_Wave[n]<< std::endl;
    }
    file.close();





    /*  Noise is generated using
    *   NoiseGen(double N_amp, int N_samp)
    *
    * 
    */
    std::cout<< "Enter noise amplitude: "<< std::endl;
    std::cin>> N_amp;
    std::cout<< "Enter number of noise samples: "<< std::endl;
    std::cin>> N_samp;

    std::ofstream Nfile("data/noise.csv");

    VecD noise = NoiseGen(N_amp, N_samp);
    std::cout<< "Generated noise: "<< std::endl;
    for(int n=0; n<N_samp; n++){
        Nfile<< noise[n]<< std::endl;
    }
    Nfile.close();





    /*  The noisy signal is generated using
    *   NoisySignalGen(double freq, double sample_rate, int samples, double amplitude, double N_amp, int N_samp)
    *
    *   Here the sine wave and noise are combined to create a noisy signal.
    * 
    */
    std::ofstream NoisyFile("data/NoisySignal.csv");

    VecD NoisySignal = NoisySignalGen(freq, sample_rate, samples, amplitude, N_amp, N_samp);
    std::cout<< "Generated noisy signal: "<< std::endl;
    for(int n=0; n<samples; n++){
        double t = n/static_cast<double>(sample_rate);
        NoisyFile<< t << "," << NoisySignal[n]<< std::endl;
    }
    NoisyFile.close();





    /*  The low-pass filter is applied using
    *   LowPassFilter(const std::vector<double>& input, double cutoff_freq, double sample_rate)
    *
    *   Here the noisy signal is filtered to remove high-frequency components.
    * 
    */
    std::cout<< "Enter low-pass cutoff frequency (Hz): "<< std::endl;
    std::cin>> cutoff_freq;

    auto filteredSignal = LowPassFilter(NoisySignal, cutoff_freq, sample_rate);
    std::ofstream LPFFile("data/FilteredSignal.csv");
    std::cout<< "Generated filtered signal: "<< std::endl;
    for(int n=0; n<samples; n++){
        double t = n/static_cast<double>(sample_rate);
        LPFFile<< t << "," << filteredSignal[n]<< std::endl;
    }
    LPFFile.close();

    system("python ./scripts/plot.py");

    return 0;
}