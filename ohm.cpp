#include <iostream>
#include <iomanip>

extern "C" {
    double resistance();
}

int main() {
    std::cout << "Welcome to Parallel Circuits by Circuit Calculator.\n";
    std::cout << "This program will automate finding the resistance in a large circuit.\n";
    
    // Call assembly function and get result
    double the_resistance = resistance();
    
    // Display result with exactly 10 decimal places
    std::cout << "Main received this number: " << std::fixed << std::setprecision(10) << the_resistance << std::endl;
    std::cout << "Main will now return 0 to the operating system.\n";
    
    return 0;
}
