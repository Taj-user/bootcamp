#include <iostream>
#include <stdexcept>
#include "CheckingAccount.h"

// Checking Account Constructor
CheckingAccount::CheckingAccount(double balance, const std::string& ownerName, double overdraftLimit)
	: BankAccount(balance, ownerName)
	, overdraftLimit_ (overdraftLimit)
{
	if(overdraftLimit < 0.0) { throw std::invalid_argument("Overdraft limit cannot be negative."); }
}

// Override Withdraw method
void CheckingAccount::withdraw(double amount) {
	if(amount < 0) { throw std::invalid_argument("Amount cannot be negative"); }
	else if(amount > balance_ + overdraftLimit_) { throw std::invalid_argument("Amount exceeds overdraft limit"); }
	else { balance_ -= amount; }
}

// Override Print Statement method
void CheckingAccount::printStatement() const {
	BankAccount::printStatement();
	std::cout << "Account overdraft limit: " << overdraftLimit_ << "\n";
}

CheckingAccount::~CheckingAccount() { std::cout << "Destructor called for checking account: " << getAccountNumber() << "\n"; }
