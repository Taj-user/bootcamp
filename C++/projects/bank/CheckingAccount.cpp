#include <iostream>
#include <string>
#include <stdexcept>
#include "CheckingAccount.h"

// Checking Account Constructor
CheckingAccount::CheckingAccount(int accountNumber, double balance, const std::string& ownerName, double overdraftLimit)
	: BankAccount(accountNumber, balance, ownerName)
	, overdraftLimit_ (overdraftLimit)
{
	if(overdraftLimit < 0.0) { throw std::invalid_argument("Overdraft limit cannot be negative."); }
}

// Override Withdraw method
void CheckingAccount::withdraw(double amount) override {
	if(amount < 0) { throw std::invalid_argument("Amount cannot be negative"); }
	else if(amount > balance_ + overdraftLimit_) { throw std::invalid_argument("Amount exceeds overdraft limit"); }
	else { balance_ -= amount; }
}

// Override Print Statement method
void CheckingAccount::printStatement() const override {
	std::cout << "Statements:\n";
	std::cout << "Account Name: " << ownerName_ << "\n";
	std::cout << "Account Number: " << accountNumber_ << "\n";
	std::cout << "Account balance: " << balance_ << "\n";
	std::cout << "Account overdraft limit: " << overdraftLimit_ << "\n";
}

CheckingAccount::~CheckingAccount() { std::cout << "Destructor called for checking account: " << accountNumber_ << "\n"; }
