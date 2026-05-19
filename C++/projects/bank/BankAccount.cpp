#include <iostream>
#include <stdexcept>
#include "BankAccount.h"

BankAccount::BankAccount(int accountNumber, double balance, const std::string& ownerName)
	: accountNumber_ (accountNumber)
	, balance_ (balance)
	, ownerName_ (ownerName)
{
	if(balance < 0.0) { throw std::invalid_argument("Initial balance cannot be negative"); }
}

void BankAccount::deposit(double amount) {
	if(amount < 0) { throw std::invalid_argument("Amount cannot be negative"); }
	else { balance_ += amount; }
}

void BankAccount::withdraw(double amount) {
	if(amount < 0) { throw std::invalid_argument("Amount cannot be nagative."); }
	else if(amount > balance_) { throw std::invalid_argument("Insufficient funds in balance."); }
	else { balance_ -= amount; }
}

double BankAccount::getBalance() const { return balance_; }
int BankAccount::getAccountNumber() const { return accountNumber_; }
std::string BankAccount::getOwnerName() const { return ownerName_; }

void BankAccount::printStatement() const {
	std::cout << "Statements:\n";
	std::cout << "Account Name: " << ownerName_ << "\n";
	std::cout << "Account Number: " << accountNumber_ << "\n";
	std::cout << "Account Balance: " << balance_ << "\n";
}

BankAccount::~BankAccount() { std::cout << "Destructor called.\n"; }
