#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class Course {
private:
    string name;
    string grade;
    double credits;
    double gradePoint;

public:
    Course(string n, string g, double c) {
        name = n;
        grade = g;
        credits = c;
        gradePoint = calculateGradePoint(g);
    }

    double calculateGradePoint(string g) {
        if (g == "O") return 10;
        if (g == "A+") return 9;
        if (g == "A") return 8;
        if (g == "B+") return 7;
        if (g == "B") return 6;
        if (g == "C") return 5;
        if (g == "D") return 4;
        return 0;
    }

    string getName() const {
        return name;
    }

    string getGrade() const {
        return grade;
    }

    double getCredits() const {
        return credits;
    }

    double getGradePoint() const {
        return gradePoint;
    }

    double getWeightedPoints() const {
        return credits * gradePoint;
    }
};

class Semester {
private:
    int semesterNumber;
    vector<Course> courses;

public:
    Semester(int number) {
        semesterNumber = number;
    }

    void addCourse(const Course& course) {
        courses.push_back(course);
    }

    double getTotalCredits() const {
        double total = 0;

        for (const auto& course : courses)
            total += course.getCredits();

        return total;
    }

    double getTotalGradePoints() const {
        double total = 0;

        for (const auto& course : courses)
            total += course.getWeightedPoints();

        return total;
    }

    double getGPA() const {
        if (getTotalCredits() == 0)
            return 0;

        return getTotalGradePoints() / getTotalCredits();
    }

    int getSemesterNumber() const {
        return semesterNumber;
    }

    const vector<Course>& getCourses() const {
        return courses;
    }
};

class Student {
private:
    string name;
    string studentID;
    vector<Semester> semesters;

public:
    Student(string n, string id) {
        name = n;
        studentID = id;
    }

    void addSemester(const Semester& semester) {
        semesters.push_back(semester);
    }

    double getTotalCredits() const {
        double total = 0;

        for (const auto& semester : semesters)
            total += semester.getTotalCredits();

        return total;
    }

    double getTotalGradePoints() const {
        double total = 0;

        for (const auto& semester : semesters)
            total += semester.getTotalGradePoints();

        return total;
    }

    double getCGPA() const {
        if (getTotalCredits() == 0)
            return 0;

        return getTotalGradePoints() / getTotalCredits();
    }

    string getPerformance() const {
        double cgpa = getCGPA();

        if (cgpa >= 9)
            return "Outstanding";
        if (cgpa >= 8)
            return "Excellent";
        if (cgpa >= 7)
            return "Very Good";
        if (cgpa >= 6)
            return "Good";
        if (cgpa >= 5)
            return "Satisfactory";

        return "Needs Improvement";
    }

    const vector<Semester>& getSemesters() const {
        return semesters;
    }

    string getName() const {
        return name;
    }

    string getStudentID() const {
        return studentID;
    }

    const Course* getHighestCourse() const {
        const Course* best = nullptr;

        for (const auto& semester : semesters) {
            for (const auto& course : semester.getCourses()) {
                if (best == nullptr ||
                    course.getGradePoint() > best->getGradePoint()) {
                    best = &course;
                }
            }
        }

        return best;
    }

    const Course* getLowestCourse() const {
        const Course* lowest = nullptr;

        for (const auto& semester : semesters) {
            for (const auto& course : semester.getCourses()) {
                if (lowest == nullptr ||
                    course.getGradePoint() < lowest->getGradePoint()) {
                    lowest = &course;
                }
            }
        }

        return lowest;
    }
};

string getValidGrade() {
    string grade;

    while (true) {
        cout << "Grade (O/A+/A/B+/B/C/D/F): ";
        cin >> grade;

        if (grade == "O" || grade == "A+" || grade == "A" ||
            grade == "B+" || grade == "B" || grade == "C" ||
            grade == "D" || grade == "F") {
            return grade;
        }

        cout << "Invalid grade. Please try again.\n";
    }
}

double getValidCredits() {
    double credits;

    while (true) {
        cout << "Credit Hours: ";
        cin >> credits;

        if (!cin.fail() && credits > 0 && credits <= 10)
            return credits;

        cout << "Enter valid credit hours between 1 and 10.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getValidNumber(string message, int minimum, int maximum) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        if (!cin.fail() && value >= minimum && value <= maximum)
            return value;

        cout << "Invalid input. Please try again.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void displayReport(const Student& student) {
    cout << "\n";
    cout << "============================================================\n";
    cout << "              ACADEMIC PERFORMANCE REPORT\n";
    cout << "============================================================\n";

    cout << "Student Name : " << student.getName() << "\n";
    cout << "Student ID   : " << student.getStudentID() << "\n";

    cout << "\n------------------------------------------------------------\n";

    for (const auto& semester : student.getSemesters()) {
        cout << "SEMESTER " << semester.getSemesterNumber() << "\n";
        cout << "------------------------------------------------------------\n";

        cout << left
             << setw(25) << "Course"
             << setw(10) << "Grade"
             << setw(12) << "Credits"
             << setw(15) << "Grade Point"
             << setw(15) << "Weighted"
             << "\n";

        cout << "------------------------------------------------------------\n";

        for (const auto& course : semester.getCourses()) {
            cout << left
                 << setw(25) << course.getName()
                 << setw(10) << course.getGrade()
                 << setw(12) << course.getCredits()
                 << setw(15) << course.getGradePoint()
                 << setw(15) << course.getWeightedPoints()
                 << "\n";
        }

        cout << "------------------------------------------------------------\n";
        cout << fixed << setprecision(2);
        cout << "Total Credits : " << semester.getTotalCredits() << "\n";
        cout << "Semester GPA  : " << semester.getGPA() << "\n\n";
    }

    const Course* highest = student.getHighestCourse();
    const Course* lowest = student.getLowestCourse();

    cout << "============================================================\n";
    cout << "                    FINAL SUMMARY\n";
    cout << "============================================================\n";

    cout << fixed << setprecision(2);

    cout << "Total Credits : " << student.getTotalCredits() << "\n";
    cout << "Overall CGPA  : " << student.getCGPA() << " / 10.00\n";
    cout << "Performance   : " << student.getPerformance() << "\n";

    if (highest != nullptr) {
        cout << "Top Course    : "
             << highest->getName()
             << " (" << highest->getGrade() << ")\n";
    }

    if (lowest != nullptr) {
        cout << "Focus Course  : "
             << lowest->getName()
             << " (" << lowest->getGrade() << ")\n";
    }

    cout << "============================================================\n";
}

int main() {
    cout << "\n";
    cout << "============================================================\n";
    cout << "        STUDENT ACADEMIC PERFORMANCE TRACKER\n";
    cout << "============================================================\n";

    string name;
    string studentID;

    cout << "Enter Student Name: ";
    getline(cin, name);

    cout << "Enter Student ID: ";
    getline(cin, studentID);

    Student student(name, studentID);

    int semesterCount = getValidNumber(
        "Number of semesters completed: ", 1, 12
    );

    for (int i = 1; i <= semesterCount; i++) {
        cout << "\n========== Semester " << i << " ==========\n";

        int courseCount = getValidNumber(
            "Number of courses: ", 1, 15
        );

        Semester semester(i);

        for (int j = 1; j <= courseCount; j++) {
            cout << "\nCourse " << j << "\n";

            string courseName;

            cout << "Course Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, courseName);

            string grade = getValidGrade();
            double credits = getValidCredits();

            semester.addCourse(
                Course(courseName, grade, credits)
            );
        }

        student.addSemester(semester);
    }

    displayReport(student);

    return 0;
}
