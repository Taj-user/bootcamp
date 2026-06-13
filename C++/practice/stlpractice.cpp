#include <iostream>
#include <stack>
#include <queue>
#include <vector>

int main(){
	// 1
	std::vector<std::string> students = {"Bread", "John", "Cococolastic", "Fantastic"};
	std::vector<std::string> students_reversed;
	std::stack<std::string> vec;

	for(const auto& name : students) {
		vec.push(name);
	}

	while(!vec.empty()) {
		students_reversed.push_back(vec.top());
		vec.pop();
	}

	for(const auto& name : students_reversed) {
		std::cout << name << "\n";
	}

	// 2
	std::vector<double> grades = {22.4, 100, 1.63, 63.8, 12.59, 76.0, 91.99, 80.3};
	std::vector<double> top_grades;
	std::priority_queue<double> queue;

	for(const auto& name : grades) {
		queue.push(name);
	}

	for(int i = 0; i < 3; i++) {
		top_grades.push_back(queue.top());
		queue.pop();
	}

	std::cout << "\n";
	for(const auto& grade : top_grades) {
		std::cout << grade << "\n";
	}
	
	// 3
	std::vector<std::string> tasks = {"task1", "task2", "task3", "task4", "task5"};
	std::queue<std::string> task_queue;
	
	for(const auto& task : tasks) {
		task_queue.push(task);
	}

	std::cout << "\n";
	while(!task_queue.empty()) {
		std::cout << task_queue.front() << " processed\n";
		task_queue.pop();
	}


	return 0;
}
