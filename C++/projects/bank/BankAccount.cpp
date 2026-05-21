#include <iostream>
#include <stdexcept>
#include "BankAccount.h"

// Bank Account Constructor
BankAccount::BankAccount(int accountNumber, double balance, const std::string& ownerName)
	: accountNumber_ (accountNumber)
	, balance_ (balance)
	, ownerName_ (ownerName)
{
	if(balance < 0.0) { throw std::invalid_argument("Initial balance cannot be negative"); }
}

// Bank Account Copy Constructor
BankAccount::BankAccount(const BankAccount& other)
	: accountNumber_ (other.accountNumber_)
	, balance_ (other.balance_)
	, ownerName_ (other.ownerName_)
{}

// Bank Account Copy Assignment Operator method
BankAccount& BankAccount::operator=(const BankAccount& other) {
	// Check for self assignment
	if(this == &other){ return *this; }

	// Copy from other
	accountNumber_ = other.accountNumber_;
	balance_ = other.balance_;
	ownerName_ = other.ownerName_;
	
	return *this;
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
	os << "Account Balance: " << account.balance_ << "\n";

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

// Getter methods
double BankAccount::getBalance() const { return balance_; }
int BankAccount::getAccountNumber() const { return accountNumber_; }
std::string BankAccount::getOwnerName() const { return ownerName_; }

// Deconstructor
BankAccount::~BankAccount() { std::cout << "Destructor called for account: " << accountNumber_ << "\n"; }
