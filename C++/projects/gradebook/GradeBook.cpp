#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "GradeBook.h"

// Add student to students unordered map
int GradeBook::addStudent(const std::string& name) {
	Student s(name);
	students_.emplace(s.getId(), s);
	return s.getId();
}

// Add course to courses set
void GradeBook::addCourse(const std::string& courseCode) { courses_.emplace(courseCode); }

// Enroll a studnet to a course
void GradeBook::enrollStudent(int studentId, const std::string& courseCode) {
	auto s_it = students_.find(studentId);
	auto c_it = courses_.find(courseCode);
	if(s_it != students_.end() && c_it != courses_.end()) {
		(s_it->second).enrollCourse(courseCode);
	}
	else if(s_it == students_.end()) { throw std::out_of_range("Student not found"); }
	else if(c_it == courses_.end()) { throw std::out_of_range("Course not found"); }
}

// Record the grade of a course for a student
void GradeBook::recordGrade(int studentId, const std::string& courseCode, double grade) {
	auto it = students_.find(studentId);
	if(it != students_.end()) {
		(it->second).addGrade(courseCode, grade);
	}
	else { throw std::out_of_range("Student not found"); }
}

// Print all transcripts of students in student unordered map
void GradeBook::printAllTranscripts() const {
	for(const auto& pair : students_) { (pair.second).printTranscript(); }
}

// Print students enrolled in specific course
void GradeBook::printCourseRoster(const std::string& courseCode) const {
	int count = 0;
	std::cout << "Course Roster:\n";
	for(const auto& pair : students_) {
		if((pair.second).isEnrolled(courseCode)) {
			std::cout << ++count << ": " << (pair.second).getName() << "\n";
		}
	}
}

// Prints the student with the highest grade average]
std::string GradeBook::getTopStudent() const {
	if(students_.empty()) { throw std::runtime_error("No students in gradebook"); }
	double highest = -1;
	std::string name;
	for(const auto& pair : students_) {
		try {
			double avg = (pair.second).getAverageGrade();
			if(avg > highest) {
				highest = avg;
				name = (pair.second).getName();
			}
		}
		catch(const std::runtime_error& ree) { continue; }
	}
	std::cout << "Top student\n";
	return name;
}
