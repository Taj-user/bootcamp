// main.cpp — CLI Finance Tracker | Phase 1, Session 1
// Demonstrates: structs, arrays, functions, references, const, control flow

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

// ─── Constants ─────────────────────────────────────────────────────────────
// constexpr: evaluated at compile time — these will never change at runtime
// constexpr int    MAX_DESCRIPTION_LENGTH = 100;
// constexpr double MINIMUM_AMOUNT         = 0.01;

// ─── Data Model ────────────────────────────────────────────────────────────
struct Transaction {
    std::string description;  // What this transaction is for
    double      amount;       // Positive = income, negative = expense
    std::string category;     // e.g., "Food", "Salary", "Rent"
};

// ─── Function Declarations (Forward Declarations) ──────────────────────────
void        displayMenu();
void        addTransaction(std::vector<Transaction>& transactions, bool isExpence);
void        viewTransactions(const std::vector<Transaction>& transactions);
double      calculateBalance(const std::vector<Transaction>& transactions);
void        displayBalance(const std::vector<Transaction>& transactions);
void        printDivider();
void		saveTransactions(const std::vector<Transaction>& transactions);
void		loadTransactions(std::vector<Transaction>& transactions);

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
                addTransaction(transactions, true);			// true = expence
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

// ─── Function Implementations ───────────────────────────────────────────────

void printDivider() {
	std::cout << "----------------------------------\n";
}

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

// Takes the transaction list BY REFERENCE — we need to modify it (add to it)
// If we passed by value, we'd be modifying a copy and the original would be unchanged
void addTransaction(std::vector<Transaction>& transactions, bool isExpence) {
    Transaction t;  // A new Transaction, allocated on the stack

    std::cout << "\nDescription: ";
    std::getline(std::cin, t.description);  // getline reads a full line including spaces

    std::cout << "Amount: ";
    std::cin >> t.amount;
    std::cin.ignore(1000, '\n');

    // Input validation — reject amounts that don't make sense
    // We use std::abs because an expense of -0.001 is also invalid
    t.amount = std::abs(t.amount);

    if(isExpence) { t.amount = -t.amount; }

    if (t.amount == 0.0) {
        std::cout << "[!] Amount cannot be zero. Transaction cancelled.\n";
        return;  // Early return — exits this function without adding anything
    }

    std::cout << "Category (e.g. Food, Rent, Salary): ";
    std::getline(std::cin, t.category);

    // push_back adds a copy of t to the end of the vector
    transactions.push_back(t);

    std::cout << "  Transaction added.\n";
}

// Takes the transaction list by CONST reference — we only read it, never modify it.
// const& is the correct choice: no copy made (efficient), and we're protected
// from accidentally modifying the vector.
void viewTransactions(const std::vector<Transaction>& transactions) {
    std::cout << "\n";
    printDivider();
    std::cout << "  TRANSACTION HISTORY\n";
    printDivider();

    if (transactions.empty()) {
        std::cout << "  No transactions yet.\n";
        printDivider();
        return;
    }

    // std::fixed + std::setprecision(2) formats doubles as "1234.56"
    // Without this, doubles print with arbitrary precision: "1234.5600000001"
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& t : transactions) {
        std::string type = (t.amount >= 0) ? "INC" : "EXP";

        std::cout << "  [" << type << "] "
                  << std::setw(25) << std::left << t.description  // left-align, 25 chars wide
                  << " | " << std::setw(8) << std::right << t.amount  // right-align, 8 chars wide
                  << " | " << t.category << "\n";
    }

    printDivider();
}

// Computes the balance by summing all transaction amounts.
// Returns a double — a copy of the computed value.
double calculateBalance(const std::vector<Transaction>& transactions) {
    double balance = 0.0;

    for (const auto& t : transactions) {
        balance += t.amount;  // Positive amounts increase balance, negative decrease it
    }

    return balance;
}

void displayBalance(const std::vector<Transaction>& transactions) {
    double balance = calculateBalance(transactions);

    std::cout << "\n";
    printDivider();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Current Balance: $" << balance << "\n";

    if (balance < 0) {
        std::cout << "  You are in the red.\n";
    } else if (balance == 0.0) {
        std::cout << "  You are at break-even.\n";
    } else {
        std::cout << "  You are in the black.\n";
    }

    printDivider();
}

void saveTransactions(const std::vector<Transaction>& transactions) {
	std::ofstream file("transactions.csv");

	if(!file.is_open()) {
		std::cerr << "Error opening file.\n";
		printDivider();
		return;
	}

	if(transactions.empty()) {
		std::cerr << "No transactions to save.\n";
		printDivider();
		return;
	}

	for(const auto& t : transactions) {
		file << t.description << "," << std::fixed << std::setprecision(2) << t.amount << "," << t.category << "\n";
	}

	file.close();
	std::cout << "  Successfully saved transactions to [transactions.csv]\n";
	printDivider();
}

void loadTransactions(std::vector<Transaction>& transactions) {
	std::ifstream file("transactions.csv");

	if(!file.is_open()) {
		return;
	}

	std::string line;

	while(std::getline(file, line)) {
		Transaction t;
		std::stringstream ss(line);
		std::string field;

		std::getline(ss, field, ',');
		t.description = field;

		std::getline(ss, field, ',');
		try {
			t.amount = std::stod(field);
		}
		catch(const std::invalid_argument& iae) {
			std::cerr << "Error reading field from file. " << iae.what() << "\n";
			continue;
		}

		std::getline(ss, field, ',');
		t.category = field;

		transactions.push_back(t);
	}
	file.close();
}
