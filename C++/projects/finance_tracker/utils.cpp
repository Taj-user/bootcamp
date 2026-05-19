#include <iostream>
#include "utils.h"

void displayMenu() {
    std::cout << "\n";
    printDivider();
    std::cout << "  1. Add Income\n";
    std::cout << "  2. Add Expense\n";
    std::cout << "  3. View Transactions\n";
    std::cout << "  4. View Balance\n";
    std::cout << "  5. Save and quit\n";
    printDivider();
}

void printDivider() {
	std::cout << "----------------------------------\n";
}
