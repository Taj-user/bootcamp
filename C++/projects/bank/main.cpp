#include <iostream>
#include <vector>
#include <stdexcept>
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

int main() {
	static int ACC_NUM = 100000;
	static BankAccount* selected_acc_ptr = nullptr;
	int choice;
	std::vector<BankAccount*> accounts;

	// Menu
	do {
		std::cout << "========== Bank Account Management System ==========\n";
		std::cout << "1. Create a checking account.\n";
		std::cout << "2. Create a savings account.\n";
		std::cout << "3. Select an account. (By account number)\n";
		std::cout << "4. Deposit to selected account.\n";
		std::cout << "5. Withdraw from selected account.\n";
		std::cout << "6. Apply interest. (Savings account only).\n";
		std::cout << "7. Print statement for selected account.\n";
		std::cout << "8. Print all accounts.\n";
		std::cout << "9. Exit\n";
		std::cout << "Enter you choice: ";
		std::cin >> choice;

		switch(choice) {
			case 1:
				std::string name;
				double overdraftLimit;

				std::cout << "Enter the name of the owner for the account: ";
				std::getline(std::cin, name);
				std::cout << "Enter the overdraft limit for the account: ";
				std::cin >> overdraftLimit;
				
				try {
					BankAccount* ba = new CheckingAccount(ACC_NUM++, 0, name, overdraftLimit);
					accounts.push_back(ba);
					std::cout << "Checking account created successfully\n";
				}
				catch(const std::invalid_argument& iae) { std::cerr << iae.what(); }

				break;

			case 2:
				std::string name;
				double interestRate;

				std::cout << "Enter the name of the owner for the account: ";
				std::getline(std::cin, name);
				std::cout << "Enter the interest rate for the account: ";
				std::cin >> interestRate;

				try {
					BankAccount* ba = new SavingsAccount(ACC_NUM++, 0, name, interestRate);
					accounts.push_back(ba);
					std::cout << "Savings account created successfully\n";
				}
				catch(const std::invalid_argument& iae) { std::cerr << iae.what(); }

				break;

			case 3:
				int acc_num;
				std::cout << "Enter the account number: ";
				std::cin >> acc_num;

				for(BankAccount* ba : accounts) {
					if(ba->getAccountNumber() == acc_num) {
						selected_acc_ptr = ba;
						std::cout << "Successfully selected account: " << acc_num;
						break;
					}
					else { std::cerr << "Account not found\n"; }
				}

				break;

			case 4:
				int amt;
				std::cout << "Enter the amount you would like to deposit: ";
				std::cin >> amt;

				try {
					if(selected_acc_ptr) { selected_acc_ptr->deposit(amt); }
					else { std::cerr << "No account selected\n"; }
				}
				catch(const std::invalid_argument& iae) { std::cerr << iae.what(); }

				break;

			case 5:
				int amt;
				std::cout << "Enter the amount you would like to withdraw: ";
				std::cin >> amt;
			
				try {
					if(selected_acc_ptr) { selected_acc_ptr->deposit(amt); }
					else { std::cerr << "No account selected\n"; }
				}
				catch(const std::invalid_argument& iae) { std::cerr << iae.what(); }

				break;

			case 6:
				if(dynamic_cast<SavingsAccount*>(selected_acc_ptr)) { selected_acc_ptr->applyInterest(); }
				else { std::cerr << "Selected account is not savings\n"; }

				break;

			case 7:
				if(selected_acc_ptr) { selected_acc_ptr->printStatement(); }
				else { std::cerr << "No account selected\n"; }

				break;

			case 8:
				if(accounts.size() > 0) {
					for(BankAccount* ba : accounts) {
						ba->printStatement();
					}
				}
				else { std::cerr << "No accounts to print\n"; }
				
				break;

			case 9:
				std::cout << "\nExiting...\n";

				break;

			default:
				std::cerr << "\nInvalid choice!\n";
				break;
		}
	}
	while(choice != 9);
	
	// Cleanup
	for(BankAccount* ba : accounts) { delete ba; }
	accounts.clear();
	
	return 0;
}

