#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>

struct Student {
	std::string name;
	std::string surname;
	float average_mark = 0;
	int attended_lessons = 0;
};

int main() {
	std::ifstream fin;
	fin.open("Test.txt");
	if (!fin.is_open()) {
		std::cout << "Can't find Test.txt" << std::endl;
	}
	else {
		std::vector<Student>students;
		std::size_t max_name_length = 4;
		std::size_t max_surname_length = 6;
		while (!fin.eof()) {
			Student new_student;
			std::getline(fin, new_student.name, ',');
			if (new_student.name.size() > max_name_length) max_name_length = new_student.name.size();
			std::getline(fin, new_student.surname, ',');
			if (new_student.surname.size() > max_surname_length) max_surname_length = new_student.surname.size();
			fin >> new_student.average_mark;
			fin.ignore();
			fin >> new_student.attended_lessons;
			fin.ignore();
			students.emplace_back(std::move(new_student));
		}
		std::cout << "Succeeded Name" << std::string(max_name_length + 1 - 4, ' ') << "Surname" <<
			std::string(max_surname_length + 1 - 6, ' ') << "Avg mark Attended" << std::endl;
		for (const auto& student : students) {
			if (student.average_mark > 4 && student.attended_lessons > 5) {
				std::cout << "    +     ";
			}
			else {
				std::cout << "          ";
			}
			std::cout << std::left << std::setw(max_name_length + 1) << student.name <<
				std::setw(max_surname_length + 1) << student.surname <<
				std::right << std::setw(8) << std::setprecision(3) << student.average_mark <<
				"      " << student.attended_lessons << std::endl;
		}
		fin.close();
	}
	return 0;
}