#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

void draw_circuit(double r1, double r2, double r3, double r4) {
    std::cout << "\nCircuit Visualization:\n";
    std::cout << "┌────[+]────┬──────╱╱╱╱──(" << std::fixed << std::setprecision(1) << r1 << "Ω)──┬────┐\n";
    std::cout << "│          │                    │    │\n";
    std::cout << "│          ├──────╱╱╱╱──(" << r2 << "Ω)──┤    │\n";
    std::cout << "[PWR]      │                    │    │\n";
    std::cout << "│          ├──────╱╱╱╱──(" << r3 << "Ω)──┤    │\n";
    std::cout << "│          │                    │    │\n";
    std::cout << "└────[-]────┴──────╱╱╱╱──(" << r4 << "Ω)──┴────┘\n\n";
}

extern "C" void show_resistance(double resistance, double ticks, double cpu_freq_mhz, 
                              double r1, double r2, double r3, double r4) {
    // Draw circuit visualization
    draw_circuit(r1, r2, r3, r4);
    
    // Calculate elapsed time in nanoseconds
    // nanoseconds = (ticks / (freq_mhz * 1,000,000)) * 1,000,000,000
    double elapsed_ns = (ticks / (cpu_freq_mhz * 1000000.0)) * 1000000000.0;

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "The total resistance of the system is " 
              << resistance << " Ohms, which required\n"
              << static_cast<long long>(ticks) << " ticks ("
              << elapsed_ns << "ns) to complete.\n";
}
