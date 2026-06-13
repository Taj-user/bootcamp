#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "BankAccount.h"

int BankAccount::nextAccountNumber_ = 100000;

// Bank Account Constructor
BankAccount::BankAccount(double balance, const std::string& ownerName)
	: accountNumber_ (++nextAccountNumber_)
	, ownerName_ (ownerName)
	, balance_ (balance)
{
	if(balance < 0.0) { throw std::invalid_argument("Initial balance cannot be negative"); }
}

// Bank Account Equality Operator method
bool BankAccount::operator==(const BankAccount& other) const {
	return accountNumber_ == other.accountNumber_;
}

// Bank Account Print Statement Operator method
std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
	os << "Statements:\n";
	os << "Account Name: " << account.ownerName_ << "\n";
	os << "Account Number: " << account.accountNumber_ << "\n";
	os << "Account Balance: " << std::fixed << std::setprecision(2) << account.balance_ << "\n";

	return os;
}

// Deposit method
void BankAccount::deposit(double amount) {
	if(amount < 0) { throw std::invalid_argument("Amount cannot be negative"); }
	else { balance_ += amount; }
}

// Withdraw method
void BankAccount::withdraw(double amount) {
	if(amount < 0) { throw std::invalid_argument("Amount cannot be negative."); }
	else if(amount > balance_) { throw std::invalid_argument("Insufficient funds in balance."); }
	else { balance_ -= amount; }
}

// Print statement method
void BankAccount::printStatement() const {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "\nStatements:\n";
	std::cout << "Account Name: " << ownerName_ << "\n";
	std::cout << "Account Number: " << accountNumber_ << "\n";
	std::cout << "Account balance: " << balance_ << "\n";
}

// Getter methods
double BankAccount::getBalance() const { return balance_; }
int BankAccount::getAccountNumber() const { return accountNumber_; }
std::string BankAccount::getOwnerName() const { return ownerName_; }
