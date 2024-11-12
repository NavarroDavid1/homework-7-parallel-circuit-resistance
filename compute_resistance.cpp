extern "C" double compute_resistance(double r1, double r2, double r3, double r4) {
    // Check for invalid inputs
    if (r1 <= 0 || r2 <= 0 || r3 <= 0 || r4 <= 0) {
        return 0.0;
    }

    // Calculate parallel resistance: 1/R = 1/R1 + 1/R2 + 1/R3 + 1/R4
    double sum = (1.0/r1) + (1.0/r2) + (1.0/r3) + (1.0/r4);
    
    // Return total resistance
    return 1.0/sum;
}
