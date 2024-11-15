#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

void draw_circuit(double* resistances, int count) {
    std::cout << "\nCircuit Visualization:\n";
    
    // Top line with first resistor
    std::cout << "┌────[+]────┬";
    std::cout << "──────╱╱╱╱──(" << std::fixed << std::setprecision(1) 
              << resistances[0] << "Ω)──┬────┐\n";
              
    // Middle lines with remaining resistors except last
    for (int i = 1; i < count - 1; i++) {
        std::cout << "│          │                    │    │\n";
        std::cout << "│          ├──────╱╱╱╱──(" 
                  << resistances[i] << "Ω)──┤    │\n";
        if (i == count/2 - 1) {
            std::cout << "[PWR]      │                    │    │\n";
        }
    }
    
    // Bottom line with last resistor
    std::cout << "│          │                    │    │\n";
    std::cout << "└────[-]────┴──────╱╱╱╱──(" 
              << resistances[count-1] << "Ω)──┴────┘\n\n";
}

extern "C" void show_resistance(double resistance, double ticks, double cpu_freq_mhz, 
                              double* resistances, int count) {
    // Draw circuit visualization
    draw_circuit(resistances, count);
    
    // Calculate elapsed time in nanoseconds
    double elapsed_ns = (ticks / (cpu_freq_mhz * 1000000.0)) * 1000000000.0;

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "The total resistance of the system is " 
              << resistance << " Ohms, which required\n"
              << static_cast<long long>(ticks) << " ticks ("
              << elapsed_ns << "ns) to complete.\n";
}
