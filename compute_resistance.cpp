extern "C" double compute_resistance(double* resistances, int count) {
    // Check for invalid inputs
    if (!resistances || count <= 0) {
        return 0.0;
    }

    // Calculate parallel resistance: 1/R = sum(1/Ri)
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        if (resistances[i] <= 0) {
            return 0.0;
        }
        sum += 1.0/resistances[i];
    }
    
    // Return total resistance
    return 1.0/sum;
}
