#include <iostream>
#include <iomanip>

extern "C" void show_resistance(double resistance, double ticks, double cpu_freq_mhz) {
    // Calculate elapsed time in nanoseconds
    // nanoseconds = (ticks / (freq_mhz * 1,000,000)) * 1,000,000,000
    double elapsed_ns = (ticks / (cpu_freq_mhz * 1000000.0)) * 1000000000.0;

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "The total resistance of the system is " 
              << resistance << " Ohms, which required\n"
              << static_cast<long long>(ticks) << " ticks ("
              << elapsed_ns << "ns) to complete.\n";
}
