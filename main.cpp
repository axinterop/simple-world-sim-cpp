#include <iostream>
#include "Simulation.h"

int main() {
    int a;
    int b;
    std::cout << "Enter size of the world: ";
    std::cin >> a;
    std::cin >> b;
    Simulation s = Simulation(a, b);
    s.RunSimulation();
    return 0;
}