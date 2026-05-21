#include <iostream>
#include <stdexcept>
#include "BankAccount.h"

int main() {
	// Test Account creation, deposit, withdraw, etc.
	try {
		BankAccount b1(100000, 14000, "John");
		BankAccount b2(100001, 9999999, "Taj");
		BankAccount b3(100002, 1, "Bread");

		b1.deposit(339.23);
		b2.deposit(-23);
		b3.deposit(1);

		b1.withdraw(1);
		b2.withdraw(40000);
		b3.withdraw(100);

		b1.printStatement();
		b2.printStatement();
		b3.printStatement();
	}
	catch(const std::invalid_argument& iae) { std::cout << "Error: " << iae.what() << "\n"; }
	
	return 0;
}

