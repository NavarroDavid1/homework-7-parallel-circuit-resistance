#include <cmath>

struct CircuitResults {
    double total_resistance;
    double* currents;
    double* powers;
    double total_power;
    double total_current;
};

extern "C" { double compute_resistance(double r1, double r2, double r3, double r4, long delay_seconds); }

double compute_resistance(double r1, double r2, double r3, double r4, long delay_seconds) {
    // Check for invalid inputs
    if (r1 <= 0 || r2 <= 0 || r3 <= 0 || r4 <= 0) {
        return 0.0;
    }

    // Calculate parallel resistance: 1/R = sum(1/Ri)
    double sum = (1.0/r1) + (1.0/r2) + (1.0/r3) + (1.0/r4);
    
    // Add artificial delay if requested
    for (long i = 0; i < delay_seconds * 1000000; i++) {
        asm volatile("nop");
    }
    
    // Return total resistance
    return 1.0/sum;
}

extern "C" CircuitResults* compute_resistance(double* resistances, int count, double voltage = 120.0) {
    // Check for invalid inputs
    if (!resistances || count <= 0) {
        return nullptr;
    }

    CircuitResults* results = new CircuitResults;
    results->currents = new double[count];
    results->powers = new double[count];

    // Calculate parallel resistance: 1/R = sum(1/Ri)
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        if (resistances[i] <= 0) {
            delete[] results->currents;
            delete[] results->powers;
            delete results;
            return nullptr;
        }
        sum += 1.0/resistances[i];
    }
    
    // Calculate total resistance
    results->total_resistance = 1.0/sum;
    
    // Calculate individual currents and powers
    results->total_current = 0.0;
    results->total_power = 0.0;
    
    for (int i = 0; i < count; i++) {
        // Current through each resistor (I = V/R)
        results->currents[i] = voltage/resistances[i];
        results->total_current += results->currents[i];
        
        // Power dissipated by each resistor (P = V²/R)
        results->powers[i] = (voltage * voltage)/resistances[i];
        results->total_power += results->powers[i];
    }

    return results;
}