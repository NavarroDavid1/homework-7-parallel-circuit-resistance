#include <stdio.h>
#include <stdlib.h>

int get_resistance(double* r1, double* r2, double* r3, double* r4) {
    char buffer[256];
    char *endptr;
    
    printf("Please enter the resistance for each of the 4 devices.\n");
    
    // Get R1
    printf("Enter the resistance for device 1 (Ohms): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    *r1 = strtod(buffer, &endptr);
    if (*endptr != '\n') return 0;
    printf("You entered: %f\n", *r1);
    
    // Get R2
    printf("Enter the resistance for device 2 (Ohms): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    *r2 = strtod(buffer, &endptr);
    if (*endptr != '\n') return 0;
    printf("You entered: %f\n", *r2);
    
    // Get R3
    printf("Enter the resistance for device 3 (Ohms): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    *r3 = strtod(buffer, &endptr);
    if (*endptr != '\n') return 0;
    printf("You entered: %f\n", *r3);
    
    // Get R4
    printf("Enter the resistance for device 4 (Ohms): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    *r4 = strtod(buffer, &endptr);
    if (*endptr != '\n') return 0;
    printf("You entered: %f\n", *r4);
    
    // Validate all inputs are positive
    if (*r1 <= 0 || *r2 <= 0 || *r3 <= 0 || *r4 <= 0) return 0;
    
    return 1;
}
