#pragma once

#include <iostream>
#include <string>

class BankAccount {
	int accountNumber_;
	std::string ownerName_;

	protected:
		double balance_;

	public:
		BankAccount(int accountNumber, double balance, const std::string& ownerName);
		BankAccount(const BankAccount& other);
		BankAccount& operator=(const BankAccount& other);
		bool operator==(const BankAccount& other) const;
		friend std::ostream& operator<<(std::ostream& os, const BankAccount& account);
		void deposit(double amount);
		virtual void withdraw(double amount);
		virtual void printStatement() const;
		double getBalance() const;
		int getAccountNumber() const;
		std::string getOwnerName() const;
		virtual ~BankAccount();
};
