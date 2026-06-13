// main.cpp — CLI Finance Tracker | Phase 1, Session 3
// Demonstrates: structs, arrays, functions, references, const, control flow

#include <iostream>
#include "transactions.h"
#include "utils.h"

// ─── Constants ─────────────────────────────────────────────────────────────
// constexpr: evaluated at compile time — these will never change at runtime
// constexpr int    MAX_DESCRIPTION_LENGTH = 100;
// constexpr double MINIMUM_AMOUNT         = 0.01;

// ─── Main Entry Point ──────────────────────────────────────────────────────
int main() {
    std::vector<Transaction> transactions;

    loadTransactions(transactions);

	std::cout << "------------------------------------\n";
	std::cout << "|      CLI FINANCE TRACKER          |\n";
	std::cout << "------------------------------------\n";

    int choice = 0;

    while (true) {
        displayMenu();

        std::cout << "Enter choice: ";
        std::cin >> choice;

        // Clear the input buffer after reading an int.
        // empty line. ignore() discards up to 1000 chars until '\n'.
        std::cin.ignore(1000, '\n');

        switch (choice) {
        	case 1:
        		addTransaction(transactions, false);		// false = income
        		break;
            case 2:
                addTransaction(transactions, true);			// true = expense
                break;
            case 3:
                viewTransactions(transactions);
                break;
            case 4:
                displayBalance(transactions);
                break;
            case 5:
            	saveTransactions(transactions);
                std::cout << "\nGoodbye. Stay on budget.\n";
                return 0;
            default:
                std::cout << "\n[!] Invalid choice. Try again.\n";
        }
    }
}
