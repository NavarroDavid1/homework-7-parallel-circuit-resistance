#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

// Include the CircuitResults structure definition
struct CircuitResults {
    double total_resistance;
    double* currents;
    double* powers;
    double total_power;
    double total_current;
};

void draw_circuit(double* resistances, int count, double* currents) {
    std::cout << "\nCircuit Visualization:\n";
    
    // Top line with first resistor
    std::cout << "┌────[+]────┬";
    std::cout << "──────╱╱╱╱──(" << std::fixed << std::setprecision(1) 
              << resistances[0] << "Ω, " << std::setprecision(2) 
              << currents[0] << "A)──┬────┐\n";
              
    // Middle lines with remaining resistors except last
    for (int i = 1; i < count - 1; i++) {
        std::cout << "│          │                           │    │\n";
        std::cout << "│          ├──────╱╱╱╱──(" 
                  << resistances[i] << "Ω, "
                  << currents[i] << "A)──┤    │\n";
        if (i == count/2 - 1) {
            std::cout << "[PWR]      │                           │    │\n";
        }
    }
    
    // Bottom line with last resistor
    std::cout << "│          │                           │    │\n";
    std::cout << "└────[-]────┴──────╱╱╱╱──(" 
              << resistances[count-1] << "Ω, "
              << currents[count-1] << "A)──┴────┘\n\n";
}

extern "C" void show_resistance(CircuitResults* results, double ticks, double cpu_freq_mhz, 
                             double* resistances, int count) {
    if (!results) {
        std::cout << "Invalid circuit configuration!\n";
        return;
    }

    // Draw circuit visualization with currents
    draw_circuit(resistances, count, results->currents);
    
    // Calculate elapsed time in nanoseconds
    double elapsed_ns = (ticks / (cpu_freq_mhz * 1000000.0)) * 1000000000.0;

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Circuit Analysis Results:\n";
    std::cout << "-------------------------\n";
    std::cout << "Total Resistance: " << results->total_resistance << " Ohms\n";
    std::cout << "Total Current: " << results->total_current << " Amperes\n";
    std::cout << "Total Power: " << results->total_power << " Watts\n\n";
    
    std::cout << "Individual Component Analysis:\n";
    for (int i = 0; i < count; i++) {
        std::cout << "Resistor " << (i + 1) << ":\n";
        std::cout << "  - Current: " << results->currents[i] << " A\n";
        std::cout << "  - Power: " << results->powers[i] << " W\n";
    }
    
    std::cout << "\nCalculation Performance:\n";
    std::cout << "Required " << static_cast<long long>(ticks) << " ticks ("
              << elapsed_ns << "ns) to complete.\n";
}
