#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <optional>

class Student {
	static int nextId_;
	int id_;
	std::string name_;
	std::unordered_map<std::string, double> grades_;
	std::unordered_set<std::string> enrolledCourses_;

	public:
		Student(const std::string& name);
		Student(int id, const std::string& name);
		void enrollCourse(const std::string& courseCode);
		void addGrade(const std::string& courseCode, double grade);
		bool isEnrolled(const std::string& courseCode) const;
        std::optional<double> tryGetGrade(const std::string& courseCode) const;
		double getAverageGrade() const;
		int getId() const;
		std::string getName() const;
		void printTranscript() const;
		const std::unordered_map<std::string, double>& getGrades() const;
};
