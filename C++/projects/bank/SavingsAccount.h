#pragma once

#include <iostream>
#include <string>
#include "BankAccount.h"

class SavingsAccount : public BankAccount {
	double interestRate_;

	public:
		SavingsAccount(int accountNumber, double balance, const std::string& ownerName, double interestRate);
		void applyInterest();
		void printStatement() const override;
		~SavingsAccount() override;
};
