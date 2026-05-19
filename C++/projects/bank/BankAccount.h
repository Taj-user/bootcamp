#pragma once

#include <string>

class BankAccount {
	int accountNumber_;
	double balance_;
	std::string ownerName_;

	public:
		BankAccount(int accountNumber, double balance, const std::string& ownerName);
		void deposit(double amount);
		void withdraw(double amount);
		double getBalance() const;
		int getAccountNumber() const;
		std::string getOwnerName() const;
		void printStatement() const;
		~BankAccount();
};
