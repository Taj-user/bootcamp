#pragma once

#include <string>
#include <vector>

struct Transaction {
	std::string description;
	double amount;
	std::string category;
};

void        addTransaction(std::vector<Transaction>& transactions, bool isExpense);
void        viewTransactions(const std::vector<Transaction>& transactions);
double      calculateBalance(const std::vector<Transaction>& transactions);
void        displayBalance(const std::vector<Transaction>& transactions);
void        saveTransactions(const std::vector<Transaction>& transactions);
void        loadTransactions(std::vector<Transaction>& transactions);
