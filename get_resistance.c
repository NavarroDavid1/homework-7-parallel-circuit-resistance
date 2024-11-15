#include <stdio.h>
#include <stdlib.h>

int get_resistance(double** resistances, int* count) {
    char buffer[256];
    char *endptr;
    
    printf("How many resistors are in the circuit? ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    *count = (int)strtol(buffer, &endptr, 10);
    if (*endptr != '\n' || *count <= 0) return 0;
    
    *resistances = (double*)malloc(*count * sizeof(double));
    if (!*resistances) return 0;
    
    printf("Please enter the resistance for each of the %d devices.\n", *count);
    
    for (int i = 0; i < *count; i++) {
        printf("Enter the resistance for device %d (Ohms): ", i + 1);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            free(*resistances);
            return 0;
        }
        (*resistances)[i] = strtod(buffer, &endptr);
        if (*endptr != '\n') {
            free(*resistances);
            return 0;
        }
        printf("You entered: %f\n", (*resistances)[i]);
        
        // Validate input is positive
        if ((*resistances)[i] <= 0) {
            free(*resistances);
            return 0;
        }
    }
    
    return 1;
}
