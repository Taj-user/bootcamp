#include <iostream>
#include "Student.h"
#include "GradeBook.h"

int main(void) {
	int choice;

	do {
		std::cout << "===== Student Grade Book =====\n";
		std::cout << "1. Add Student\n";
		std::cout << "2. Add course\n";
		std::cout << "3. Enroll student in course\n";
		std::cout << "4. Record grade\n";
		std::cout << "5. Print all transcripts\n";
		std::cout << "6. Print course roster\n";
		std::cout << "7. Get top student\n";
		std::cout << "8. Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch(choice) {
			case 1: {
				std::string name;
				std::cout << "Enter the name of the student you would like to add: ";
				std::cin >> name;
				addStudent(name);
				std::cout << "Student " << name << " added successfully\n";
			}

			case 2: {
				std::string courseCode;
				std::cout << "Enter the course code you would like to add: ";
				std::cin >> courseCode;
				addCourse(courseCode);
				std::cout << "Course " << courseCode << " added successfully\n";
			}

			case 3: {
				int studentId;
				std::string courseCode;
				std::cout << "Enter the id of the student: ";
				std::cin >> studentId;
				std::cout << "Enter the course code: ";
				std::cin >> courseCode;
				// Could check if student is alr enrolled before the try
				try {
					enrollStudent(studentId, courseCode);
					std::cout << "Student " << studentId << " is now enrolled in " << courseCode << "\n";
				}
				catch(const std::out_of_range& oore) { oore.what(); }
			}

			case 4: {
				// TODO
			}
		}


	}
	while(choice != 8);
}
