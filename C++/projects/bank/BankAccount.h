#pragma once

#include <iostream>
#include <string>

class BankAccount {
	int accountNumber_;
	double balance_;
	std::string ownerName_;

	public:
		BankAccount(int accountNumber, double balance, const std::string& ownerName);
		BankAccount(const BankAccount& other);
		BankAccount& operator=(const BankAccount& other);
		bool operator==(const BankAccount& other) const;
		friend std::ostream& operator<<(std::ostream& os, const BankAccount& account);
		void deposit(double amount);
		void withdraw(double amount);
		double getBalance() const;
		int getAccountNumber() const;
		std::string getOwnerName() const;
		~BankAccount();
};
