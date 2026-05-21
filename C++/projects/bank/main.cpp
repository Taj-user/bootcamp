#include <iostream>
#include <stdexcept>
#include "BankAccount.h"

int main() {
	// Test Account creation, deposit, withdraw, etc.
	try {
		BankAccount a(1000, 1234567, "John");
		BankAccount b(a);
		BankAccount c(1002, 1111, "Bread");

		b.deposit(3300);
		std::cout << a;
		std::cout << "\n";
		std::cout << b;
		std::cout << "\n";

		a = b;
		std::cout << a;
		std::cout << "\n";

		bool sameAccount = a == b;
		bool diffAccount = a == c;
		std::cout << sameAccount << "\n";
		std::cout << diffAccount << "\n";

		std::cout << a;
		std::cout << "\n";
		std::cout << b;
		std::cout << "\n";
		std::cout << c;
		std::cout << "\n";
	}
	catch(const std::invalid_argument& iae) { std::cout << "Error: " << iae.what() << "\n"; }
	
	return 0;
}

