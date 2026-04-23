// SNHU, CS 300
// Project Two
// Grace A. Wright
// April 22, 2026

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

// Course object structure
struct Course {
    string courseCode;
    string courseTitle;
    // Inner vector to store prerequisites
    vector<string> prereqs;
};

// Vector data structure to hold courses
vector<Course> courses;

void LoadVector() {
    // File to parse
    string csvPath = "ABCU_Advising_Program_Input.txt";

    // Open file
    ifstream infile;
    infile.open(csvPath);

    // Read file
    if (infile.is_open()) {
        string line;

        while (getline(infile, line)) {
            vector<string> tokens;
            string token;
            stringstream ss(line);

            // Create tokens at commas
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            // Create course using data from file
            Course newCourse = Course();
            newCourse.courseCode = tokens[0];
            newCourse.courseTitle = tokens[1];

            // Add prereqs if they exist
            if (tokens.size() > 2) {
                for (int i = 2; i < tokens.size(); i++) {
                    newCourse.prereqs.push_back(tokens[i]);
                }
            }

            // Add course to course vector
            courses.push_back(newCourse);
        }

        cout << "Courses loaded." << endl;
    }

    // Error handling message
    else {
        cout << "Error reading file." << endl;
    }

    infile.close();
}

void PrintCourses() {
    if (courses.size() > 0) {

        // Sort courses
        for (int i = 0; i < courses.size() - 1; i++) {
            for (int j = 0; j < courses.size() - i - 1; j++) {
                if (courses[j].courseCode > courses[j + 1].courseCode) {
                    swap(courses[j + 1], courses[j]);
                }
            }
        }

        // Print courses
        cout << "ABCU program courses:" << endl;
        cout << endl;
        for (int i = 0; i < courses.size(); i++) {
            cout << courses[i].courseCode << ", ";
            cout << courses[i].courseTitle << endl;

            // Print the prereqs if they exist
            if (courses[i].prereqs.size() > 0) {
                cout << "Prerequisite courses: ";
                int prereqSize = courses[i].prereqs.size();

                for (int j = 0; j < prereqSize - 1; j++) {
                    cout << courses[i].prereqs[j] << ", ";
                }

                // Handle excess comma
                cout << courses[i].prereqs[prereqSize - 1];
                cout << endl;
            }
        }
        cout << endl;
    }

    else {
        cout << "Error finding courses." << endl;
    }
}

void SearchCourse() {
    // Validate loaded data
    if (courses.size() > 0) {
        string input;
        bool found = false;

        cout << "Enter course to search. ";
        cin >> input;

        for (int i = 0; i < courses.size(); i++) {
            if (courses[i].courseCode == input) {
                found = true;

                // Print searched item
                cout << endl;
                cout << courses[i].courseCode << ", ";
                cout << courses[i].courseTitle << endl;
                cout << "Prerequisite courses: ";
                if (courses[i].prereqs.size() > 0) {
                    int prereqSize = courses[i].prereqs.size();

                    for (int j = 0; j < prereqSize - 1; j++) {
                        cout << courses[i].prereqs[j] << ", ";
                    }

                    // Handle excess comma
                    cout << courses[i].prereqs[prereqSize - 1];
                    cout << endl;
                }
            }
        }
        if (found == false) {
            cout << "Invalid search formatting. Please re-enter search term with proper formatting." << endl;
        }
    }
    else {
        cout << "Error loading courses." << endl;
    }
}

int main()
{
    string csvPath = "ABCU_Advising_Program_Input.txt";

    bool end = false;

    cout << "ABCU Advising Assistance" << endl;

    do {
        string input;

        // Print menu
        cout << endl;
        cout << "1. Load courses" << endl;
        cout << "2. Print courses" << endl;
        cout << "3. Search for a course" << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "Input your selection: ";
        cin >> input;
        cout << endl;

        // Handle invalid input
        while ((input != "1") && (input != "2") && (input != "3") && (input != "9")) {
            cout << input << " failed to execute." << endl;

            cout << endl;
            // Print menu again
            cout << endl;
            cout << "1. Load courses" << endl;
            cout << "2. Print courses" << endl;
            cout << "3. Search for a course" << endl;
            cout << "9. Exit" << endl;
            cout << endl;
            cout << "Input your selection: ";
            cin >> input;
            cout << endl;
        }

        if (input == "1") {
            LoadVector();
        }
        if (input == "2") {
            PrintCourses();
        }
        if (input == "3") {
            SearchCourse();
        }
        if (input == "9") {
            cout << endl;
            cout << "Exiting program." << endl;
            exit(end);
        }
    } while (!end);
    return 0;
}