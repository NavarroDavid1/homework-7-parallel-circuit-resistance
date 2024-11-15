#include <stdio.h>

long get_resistance(double* r1, double* r2, double* r3, double* r4) {
    char buffer[256];
    double input;
    
    printf("Please enter the resistance for each of the 4 devices.\n");
    
    // Get first resistance
    printf("Enter the resistance for device 1 (Ohms): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    if (sscanf(buffer, "%lf", &input) != 1 || input <= 0) return 0;
    *r1 = input;
    printf("You entered: %f\n", *r1);
    
    // Get second resistance
    printf("Enter the resistance for device 2 (Ohms): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    if (sscanf(buffer, "%lf", &input) != 1 || input <= 0) return 0;
    *r2 = input;
    printf("You entered: %f\n", *r2);
    
    // Get third resistance
    printf("Enter the resistance for device 3 (Ohms): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    if (sscanf(buffer, "%lf", &input) != 1 || input <= 0) return 0;
    *r3 = input;
    printf("You entered: %f\n", *r3);
    
    // Get fourth resistance
    printf("Enter the resistance for device 4 (Ohms): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    if (sscanf(buffer, "%lf", &input) != 1 || input <= 0) return 0;
    *r4 = input;
    printf("You entered: %f\n", *r4);
    
    return 1;
}
