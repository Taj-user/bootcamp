#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

int main() {
	BankAccount* selected_acc_ptr = nullptr;
	int choice;
	std::vector<std::unique_ptr<BankAccount>> accounts;

	// Menu
	do {
		std::cout << "========== Bank Account Management System ==========\n";
		std::cout << "1. Create a checking account\n";
		std::cout << "2. Create a savings account\n";
		std::cout << "3. Select an account (By account number)\n";
		std::cout << "4. Deposit to selected account\n";
		std::cout << "5. Withdraw from selected account\n";
		std::cout << "6. Apply interest to selected account (Savings account only)\n";
		std::cout << "7. Print statement for selected account\n";
		std::cout << "8. Print all accounts\n";
		std::cout << "9. Exit\n";
		std::cout << "Enter you choice: ";
		std::cin >> choice;
		std::cin.ignore(1000, '\n');

		switch(choice) {
			case 1: {
				std::string name;
				double overdraftLimit;

				std::cout << "Enter the name of the owner for the account: ";
				std::getline(std::cin, name);
				std::cout << "Enter the overdraft limit for the account: ";
				std::cin >> overdraftLimit;
				
				try {
					accounts.emplace_back(std::make_unique<CheckingAccount>(0, name, overdraftLimit));
					std::cout << "Checking account created successfully\n";
				}
				catch(const std::invalid_argument& iae) { std::cerr << iae.what(); }

				break;
			}

			case 2: {
				std::string name;
				double interestRate;

				std::cout << "Enter the name of the owner for the account: ";
				std::getline(std::cin, name);
				std::cout << "Enter the interest rate for the account: ";
				std::cin >> interestRate;

				try {
					accounts.emplace_back(std::make_unique<SavingsAccount>(0, name, interestRate));
					std::cout << "Savings account created successfully\n";
				}
				catch(const std::invalid_argument& iae) { std::cerr << iae.what(); }

				break;
			}

			case 3: {
				int acc_num;
				bool found = false;
				std::cout << "Enter the account number: ";
				std::cin >> acc_num;

				for(const auto& ba : accounts) {
					if(ba->getAccountNumber() == acc_num) {
						selected_acc_ptr = ba.get();
						std::cout << "Successfully selected account: " << acc_num << "\n";
						found = true;
						break;
					}
				}
				if(!found) { std::cerr << "Account not found\n"; }

				break;
			}

			case 4: {
				double amt;

				try {
					if(selected_acc_ptr) {
						std::cout << "Enter the amount you would like to deposit: ";
						std::cin >> amt;

						selected_acc_ptr->deposit(amt);
					}
					else { std::cerr << "No account selected\n"; }
				}
				catch(const std::invalid_argument& iae) { std::cerr << iae.what(); }

				break;
			}

			case 5: {
				double amt;
			
				try {
					if(selected_acc_ptr) {
						std::cout << "Enter the amount you would like to withdraw: ";
						std::cin >> amt;
						selected_acc_ptr->withdraw(amt);
					}
					else { std::cerr << "No account selected\n"; }
				}
				catch(const std::invalid_argument& iae) { std::cerr << iae.what(); }

				break;
			}

			case 6: {
				if(SavingsAccount* sa = dynamic_cast<SavingsAccount*>(selected_acc_ptr)) {
					sa->applyInterest(); 
					std::cout << "Interest successfully applied to account: " << selected_acc_ptr->getAccountNumber() << "\n";
				}
				else if(!selected_acc_ptr) { std::cerr << "No account selected\n"; }
				else { std::cerr << "Selected account is not savings\n"; }

				break;
			}

			case 7: {
				if(selected_acc_ptr) { selected_acc_ptr->printStatement(); }
				else { std::cerr << "No account selected\n"; }

				break;
			}

			case 8: {
				if(accounts.size() > 0) {
					for(const auto& ba : accounts) {
						ba->printStatement();
					}
				}
				else { std::cerr << "No accounts to print\n"; }
				
				break;
			}

			case 9: {
				std::cout << "\nExiting...\n";

				break;
			}

			default: {
				std::cerr << "\nInvalid choice!\n";
				break;
			}
		}
	}
	while(choice != 9);
	
	return 0;
}

