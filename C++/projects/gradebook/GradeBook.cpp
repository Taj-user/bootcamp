#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <fstream>
#include "GradeBook.h"

// Add student to students unordered map
int GradeBook::addStudent(const std::string& name) {
	Student s(name);
	students_.emplace(s.getId(), s);
	return s.getId();
}

// Add course to courses set
void GradeBook::addCourse(const std::string& courseCode) { courses_.emplace(courseCode); }

// Enroll a student to a course
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

// Print all transcripts of students in student unordered map sorted
void GradeBook::printAllTranscriptsSorted() const {
	std::vector<std::pair<std::string, int>> sort_vec;

	for(const auto& pair : students_) {
		sort_vec.emplace_back(pair.second.getName(), pair.first);
	}

	std::sort(sort_vec.begin(), sort_vec.end());

	for(const auto& pair : sort_vec) {
		auto it = students_.find(pair.second);
		(it->second).printTranscript();
	}
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
	return name;
}

// Returns average grade for a course across all enrolled students
double GradeBook::getClassAverage(const std::string& courseCode) const {
	int count = 0;

	double sum = std::accumulate(
		students_.begin(),
		students_.end(),
		0.0,
		[&](double sum, const auto& pair) {
			if((pair.second).isEnrolled(courseCode)) {
				count++;
				return sum + (pair.second).getAverageGrade();
			}
			return sum;
		}
	);

	if(count == 0) { return 0.0; }
	
	return sum / count;
}

// Returns a vector of names of who passed a course
std::vector<std::string> GradeBook::getPassingStudents(const std::string& courseCode, double passMark) const {
	std::vector<std::string> vec;

	std::for_each(
		students_.begin(),
		students_.end(),
		[&](const auto& pair) {
			if(pair.second.isEnrolled(courseCode) && pair.second.getGrade(courseCode) >= passMark) {
				vec.push_back(pair.second.getName());
			}
		}
	);

	return vec;
}

// Saves all student data to a csv file (format: studentId,name,courseCode,grade)
void GradeBook::saveToFile(const std::string& filename) const {
	std::ofstream file(filename);

	if(!file) { throw std::runtime_error("Could not open file"); }

	for(const auto& [id, student] : students_) {
		for(const auto& [courseCode, grade] : student.getGrades()) {
			file << id << "," << student.getName() << "," << courseCode << "," << grade << "\n";
		}
	}
}
