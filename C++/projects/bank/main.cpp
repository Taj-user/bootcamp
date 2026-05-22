#include <iostream>
#include <stdexcept>
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

// TODO: Test the other classes and methods

int main() {
	// Test Account creation, deposit, withdraw, etc.
	try {
		BankAccount b1(1000, 99999, "Lebron James");
		CheckingAccount c1(1001, 200, "Ryan Renolds", 10000);
		SavingsAccount s1(1002, 1, "John", 0.055);

		c1.withdraw(900);
		s1.applyInterest();

		b1.printStatement();
		c1.printStatement();
		s1.printStatement();

		BankAccount* b = &b1;
		BankAccount* c = &c1;
		BankAccount* s = &s1;

		b->printStatement();
		c->printStatement();
		s->printStatement();

		c1.withdraw(99999);
	}
	catch(const std::invalid_argument& iae) { std::cout << "Error: " << iae.what() << "\n"; }
	
	return 0;
}

