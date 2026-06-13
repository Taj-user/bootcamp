#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "transactions.h"
#include "utils.h"

void addTransaction(std::vector<Transaction>& transactions, bool isExpense) {
    Transaction t;  // A new Transaction, allocated on the stack

    std::cout << "\nDescription: ";
    std::getline(std::cin, t.description);  // getline reads a full line including spaces

    std::cout << "Amount: ";
    std::cin >> t.amount;
    std::cin.ignore(1000, '\n');

    // Input validation — reject amounts that don't make sense
    // We use std::abs because an expense of -0.001 is also invalid
    t.amount = std::abs(t.amount);

    if(isExpense) { t.amount = -t.amount; }

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
