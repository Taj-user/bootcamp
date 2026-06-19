#include <iostream>

int main(){
	int balance = 1000;
	int* p_balance = &balance;
	int& ref_balance = balance;

	std::cout << "Balance: " << balance << "\nPointer balance: " << *p_balance << "\nReference balance: " << ref_balance << "\n";

	*p_balance += 500;

	std::cout << "\nBalance: " << balance << "\nPointer balance: " << *p_balance << "\nReference balance: " << ref_balance << "\n";
	
	ref_balance -= 200;

	std::cout << "\nBalance: " << balance << "\nPointer balance: " << *p_balance << "\nReference balance: " << ref_balance << "\n";

	std::cout << "\nBalance address: " << &balance << "\nPointer balance address: " << p_balance << "\nReference balance address: " << &ref_balance << "\n";

	return 0;
}
