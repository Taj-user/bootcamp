#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "Student.h"

int Student::nextId_ = 123000000;

// Student Constructor
Student::Student(const std::string& name)
	: id_ (++nextId_)
	, name_ (name)
{}

// Add course to the courses unordered set
void Student::enrollCourse(const std::string& courseCode) { enrolledCourses_.insert(courseCode); }

// Add grade to grades unordered_map
void Student::addGrade(const std::string& courseCode, double grade) {
	if(enrolledCourses_.find(courseCode) != enrolledCourses_.end()) { grades_.emplace(courseCode, grade); }
	else { throw std::out_of_range("Student not enrolled in course"); }
}

// Checks if student is enrolled in a course
bool Student::isEnrolled(const std::string& courseCode) const { return enrolledCourses_.find(courseCode) != enrolledCourses_.end(); }

// Get grade from grades unordered map
double Student::getGrade(const std::string& courseCode) const {
	if(grades_.find(courseCode) != grades_.end()) { return grades_.at(courseCode); }
	else { throw std::out_of_range("No grade recorded for course"); }
}

// Get average grade in grades unordered map
double Student::getAverageGrade() const {
	if(grades_.empty()) { throw std::runtime_error("No grades in unordered map"); }
	double sum = 0;
	for(const auto& pair : grades_) { sum += pair.second; }
	return sum / grades_.size();
}

// Get the id of a student
int Student::getId() const { return id_; }

// Get the name of a student
std::string Student::getName() const { return name_; }

// Print the trascript of a student
void Student::printTranscript() const {
	std::cout << "\nStudent Transcript\n";
	std::cout << "Student ID: " << id_ << "\n";
	std::cout << "Student Name: " << name_ << "\n";
	if(grades_.empty()) { std::cerr << "No grades to print\n"; }
	else {
		for(const auto& pair : grades_) { std::cout << pair.first << ": " << std::fixed << std::setprecision(2) << pair.second << "\n"; }
		std::cout << "Student Average: " << std::fixed << std::setprecision(2) << getAverageGrade() << "\n";
	}
}
