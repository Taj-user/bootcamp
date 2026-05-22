#pragma once

#include <string>
#include "BankAccount.h"

class CheckingAccount : public BankAccount {
	double overdraftLimit_;

	public:
		CheckingAccount(int accountNumber, double balance, const std::string& ownerName, double overdraftLimit);
		void withdraw(double amount) override;
		void printStatement() const override;
		~CheckingAccount() override;
};
