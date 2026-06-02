#include <iostream>
#include "Student.h"
#include "GradeBook.h"

int main(void) {
	int choice;
	GradeBook gradebook;

	gradebook.loadFromFile("gradebook.csv");

	do {
		std::cout << "===== Student Grade Book =====\n";
		std::cout << "1. Add Student\n";
		std::cout << "2. Add course\n";
		std::cout << "3. Enroll student in course\n";
		std::cout << "4. Record grade\n";
		std::cout << "5. Print all transcripts\n";
		std::cout << "6. Print all transcripts sorted\n";
		std::cout << "7. Print course roster\n";
		std::cout << "8. Get top student\n";
		std::cout << "9. Get class average of a course\n";
		std::cout << "10. Get passing students of a course\n";
		std::cout << "11. Find student by name\n";
		std::cout << "0. Save and exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch(choice) {
			case 1: {
				std::string name;
				std::cout << "Enter the name of the student you would like to add: ";
				std::cin >> name;

				int id = gradebook.addStudent(name);
				std::cout << "Student " << name << " with ID "<< id << " added successfully\n";

				break;
			}

			case 2: {
				std::string courseCode;
				std::cout << "Enter the course code you would like to add: ";
				std::cin >> courseCode;

				gradebook.addCourse(courseCode);
				std::cout << "Course " << courseCode << " added successfully\n";

				break;
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
					gradebook.enrollStudent(studentId, courseCode);
					std::cout << "Student " << studentId << " is now enrolled in " << courseCode << "\n";
				}
				catch(const std::out_of_range& oore) { std::cerr << oore.what() << "\n"; }

				break;
			}

			case 4: {
				int studentId;
				std::string courseCode;
				double grade;

				std::cout << "Enter the id of the student: ";
				std::cin >> studentId;
				std::cout << "Enter the course code: ";
				std::cin >> courseCode;
				std::cout << "Enter the student's grade for the course: ";
				std::cin >> grade;

				try {
					gradebook.recordGrade(studentId, courseCode, grade);
					std::cout << "Grade recorded successfully\n";
				}
				catch(const std::out_of_range& oore) { std::cerr << oore.what() << "\n"; }

				break;
			}

			case 5: {
				gradebook.printAllTranscripts();

				break;
			}

			case 6: {
				gradebook.printAllTranscriptsSorted();

				break;
			}

			case 7: {
				std::string courseCode;
				std::cout << "Enter the course code: ";
				std::cin >> courseCode;

				gradebook.printCourseRoster(courseCode);

				break;
			}

			case 8: {
				try {
					std::string top = gradebook.getTopStudent();
					std::cout << "Top Student: " << top << "\n";
				}
				catch(const std::runtime_error& ree) { std::cerr << ree.what() << "\n"; }

				break;
			}

			case 9: {
				std::string courseCode;
				std::cout << "Enter the course code: ";
				std::cin >> courseCode;

				double avg = gradebook.getClassAverage(courseCode);

				std::cout << "Class average for " << courseCode << " is " << avg << "\n";

				break;
			}

			case 10: {
				std::string courseCode;
				double passMark;

				std::cout << "Enter the course code: ";
				std::cin >> courseCode;

				std::cout << "Enter the pass mark: ";
				std::cin >> passMark;

				std::vector<std::string> vec = gradebook.getPassingStudents(courseCode, passMark);

				int count = 0;
				std::cout << "Passing students:\n";
				for(const auto& name : vec) {
					std::cout << "Student " << ++count << ": " << name << "\n";
				}

				break;
			}

			case 11: {
				std::string name;
				std::cout << "Enter the name of the student: ";
				std::cin >> name;

				std::vector<std::string> vec = gradebook.findStudentsByName(name);

				int count = 0;
				std::cout << "Students:\n";
				for(const auto& name : vec) {
					std::cout << "Student " << ++count << ": " << name << "\n";
				}

				break;
			}
			
			case 0: {
				gradebook.saveToFile("gradebook.csv");
				std::cout << "\nExiting...\n";

				break;
			}
			
			default: {
				std::cout << "Invalid choice\n";

				break;
			}
		}
	}
	while(choice != 0);

	return 0;
}
