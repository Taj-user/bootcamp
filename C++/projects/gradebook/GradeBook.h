#pragma once

#include <string>
#include <unordered_map>
#include <set>
#include "Student.h"

class GradeBook {
	std::unordered_map<int, Student> students_;
	std::set<std::string> courses_;

	public:
		int addStudent(const std::string& name);
		void addCourse(const std::string& courseCode);
		void enrollStudent(int studentId, const std::string& courseCode);
		void recordGrade(int studentId, const std::string& courseCode, double grade);
		void printAllTranscripts() const;
		void printAllTranscriptsSorted() const;
		void printCourseRoster(const std::string& courseCode) const;
		std::string getTopStudent() const;
		double getClassAverage(const std::string& courseCode) const;
		std::vector<std::string> getPassingStudents(const std::string& courseCode, double passMark) const;
		void saveToFile(const std::string& filename) const;
