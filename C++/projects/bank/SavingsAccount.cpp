#include <iostream>
#include <string>
#include <stdexcept>
#include "SavingsAccount.h"

// Savings Account Constructor
SavingsAccount::SavingsAccount(int accountNumber, double balance, const std::string& ownerName, double interestRate)
	: BankAccount(accountNumber, balance, ownerName)
	, interestRate_ (interestRate)
{
	if(interestRate < 0.0){ throw std::invalid_argument("Interest rate cannot be negative"); }
}

// Apply interest method
void SavingsAccount::applyInterest() { balance_ *= (1 + interestRate_); }

// Override print statement method
void SavingsAccount::printStatement() const override {
	std::cout << "Statements:\n";
	std::cout << "Account Name: " << ownerName_ << "\n";
	std::cout << "Account Number: " << accountNumber_ << "\n";
	std::cout << "Account balance: " << balance_ << "\n";
	std::cout << "Account interest rate: " << interestRate_ << "\n";
}

SavingsAccount::~SavingsAccount() { std::cout << "Destructor called for savings account: " << accountNumber_ << "\n"; }
