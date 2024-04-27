//============================================================================
// Name        : Project 2.cpp
// Author      : Alan Chumsawang
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Advising Assistance Program in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include<sstream>

using namespace std;

void loadDataStructure(unordered_map<string, pair<string, vector<string>>>& courseInfo, const string& fileName) {
	ifstream inputFile(fileName);
	if (inputFile.is_open()) {
		string line;
		while (getline(inputFile, line)) {
			stringstream ss(line);
			string courseCode, courseName, prereq;
			getline(ss, courseCode, ',');
			getline(ss, courseName, ',');
			vector<string> prerequisites;
			while (getline(ss, prereq, ',')) {
				prerequisites.push_back(prereq);
			}
			courseInfo[courseCode] = make_pair(courseName, prerequisites);
		}
		inputFile.close();
		cout << "Data sucessfully loaded. \n";
	}
	else {
		cout << " Error, check file name";
	}
}
void printCourseList(const unordered_map<string, pair<string, vector<string>>>& courseInfo) {
	cout << "AlphaNumeric Course List:\n";
	for (const auto& entry : courseInfo) {
		cout << entry.first << ", " <<entry.second.first << endl;
	}
}
void printCourseInfo(const unordered_map<string, pair<string, vector<string>>>& courseInfo, const string& courseCode) {
	auto it = courseInfo.find(courseCode);
	if (it != courseInfo.end()) {
		cout << it->first << ","<<it->second.first << endl;
		if (!it->second.second.empty()) {
			cout << "Prerequisites: ";
			for (const auto& prereq : it->second.second) {
				cout << prereq << " ";
			}
			cout << endl;
		}
		else {
			cout << "No prerequisites.\n";
		}
	}
	else {
		cout << "No course match.\n";
	}
 }

int main() {
	cout << "Welcome to Course Planner\n";

	unordered_map<string, pair<string, vector<string>>> courseInfo;

		string fileName = "ABCU_Advising_Program_Input1.csv";
		
		while (true) {
			int choice;
			cout << "\nMenu:\n";
			cout << "1. Load Data Structure\n";
			cout << "2. Print Course List\n";
			cout << "3. Print Course Info\n";
			cout << "9. Exit\n";
			cout << "Enter Your Choice: ";
			cin >> choice;

			cin.ignore();

			switch (choice) {
				case 1:
					loadDataStructure(courseInfo, fileName);
					break;
				case 2:
					printCourseList(courseInfo);
					break;

				case 3:
					{
						string courseCode;
						cout << "Enter Course Code: ";
						cin >> courseCode;
						transform(courseCode.begin(), courseCode.end(), courseCode.begin(), ::toupper);
						printCourseInfo(courseInfo, courseCode);
					}
					break;
				case 9:
					cout << "Exiting\n";
					return 0;

				default:
					cout << "Choice Invalid, Try Again\n";
			}
		}
		return 0;
}