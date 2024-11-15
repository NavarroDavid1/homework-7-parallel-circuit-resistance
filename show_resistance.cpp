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

extern "C" { void show_resistance(double r, long ticks, double nanoSeconds); }

void show_resistance(double r, long ticks, double nanoSeconds) {
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "The total resistance of the system is " << r 
              << " Ohms, which required\n" << ticks << " ticks ("
              << nanoSeconds << "ns) to complete.\n";
}