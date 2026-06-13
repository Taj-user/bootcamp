#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "SavingsAccount.h"

// Savings Account Constructor
SavingsAccount::SavingsAccount(double balance, const std::string& ownerName, double interestRate)
	: BankAccount(balance, ownerName)
	, interestRate_ (interestRate)
{
	if(interestRate < 0.0){ throw std::invalid_argument("Interest rate cannot be negative"); }
}

// Apply interest method
void SavingsAccount::applyInterest() { balance_ *= (1 + interestRate_); }

// Override print statement method
void SavingsAccount::printStatement() const {
	BankAccount::printStatement();
	std::cout << "Account interest rate: " << std::fixed << std::setprecision(4) << interestRate_ << "\n";
}

SavingsAccount::~SavingsAccount() { std::cout << "Destructor called for savings account: " << getAccountNumber() << "\n"; }
