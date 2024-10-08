#include "Course.cpp"
#include "Student.cpp"
#include "CustomLinkedList.h"
#include <fstream>
#include <iostream>
#include <sstream> 
#include <string>
using namespace std;

bool creative_course_list(string course_file_name, LinkedList<Course>& course_list){
    ifstream infile(course_file_name);
    if(!infile.is_open()){
        cerr<<"Error: Unable to open file: "<<course_file_name<<endl;
        return false;
    }
    string courseCode, courseName;
    int dummy1, dummy2;
    while(infile>>courseCode>>courseName>>dummy1>>dummy2){
        Course* tempCourse = new Course(courseCode, courseName);
        course_list.insert(tempCourse);
    }

    infile.close();
    return true;
}


bool creative_student_list(string student_file_name, LinkedList<Course>& course_list, LinkedList<Student>& student_list) {
    ifstream infile(student_file_name);
    if(!infile.is_open()){
        cerr<<"Error: Unable to open file: "<<student_file_name<<endl;
        return false;
    }

    string line, studentName, courseCode;
    int studentId, enrolledCount, waitlistCount;

    while(getline(infile, line)){
        istringstream iss(line);
        iss >> studentId >> studentName >> enrolledCount;

        Student* studentTemp = new Student(studentId, studentName);
        student_list.insert(studentTemp);

        for(int i = 0; i < enrolledCount; ++i){
            if(!(iss >> courseCode)){
                cerr<<"Error: Missing enrolled course code for student "<<studentName<<endl;
                continue;
            }
            Course* coursePtr = course_list.search(courseCode);
            if(coursePtr != nullptr){
                coursePtr->addEnroll(studentTemp);
            }
        }

        if(iss >> waitlistCount){
            for(int i = 0; i < waitlistCount; ++i){
                if(!(iss >> courseCode)){
                    cerr<<"Error: Missing waitlist course code for student "<<studentName<<endl;
                    continue;
                }
                Course* coursePtr = course_list.search(courseCode);
                if(coursePtr != nullptr){
                    coursePtr->addWaitlist(studentTemp);
                }
            }
        }
    }

    infile.close();
    return true;
}

int printMenu(){
    int input = 5;
    cout<<endl<<endl<<"==================== Menu ==================="<<endl;
    cout<<" 1. View your registration"<<endl;
    cout<<" 2. Course registration"<<endl;
    cout<<" 3. Course cancellation"<<endl;
    cout<<" 4. Print enrollment list including waitlist"<<endl;
    cout<<" 5. Exit"<<endl;
    cout<<" ----> Select :";
    cin>>input;
    return input;
}

Student* findStudent(LinkedList<Student>& student_list){
    int id;
    string name;
    cout<<endl<<"Enter your id: ";
    cin>>id;
    Student* studentPtr = student_list.search(id);
    if(studentPtr != nullptr){
        cout<<"Enter your name: ";
        cin>>name;
        if(name == studentPtr->getName()){
            return studentPtr;
        }
    } 
    cout<<"Error: Student not found!"<<endl;
    return nullptr;
}
Course* findCourse(LinkedList<Course>& course_list){
    string code, title;
    cout<<endl<<"Enter course code: ";
    cin>>code;
    Course* coursePtr = course_list.search(code);
    if(coursePtr != nullptr){
        cout<<"Enter course title: ";
        cin>>title;
        if(title == coursePtr->getTitle()){
            return coursePtr;
        }
    } 
    cout<<"Error: Course not found!"<<endl;
    return nullptr;
}

void menu1(LinkedList<Student>& student_list){
    Student* studentPtr = findStudent(student_list);
    if(studentPtr){
        studentPtr->print();
    } 
}

void menu2(LinkedList<Student>& student_list, LinkedList<Course>& course_list){
    Student* studentPtr = findStudent(student_list);
    if(studentPtr){
        Course* coursePtr = findCourse(course_list);
        if(coursePtr){
            coursePtr->enrollWithOutput(studentPtr);
        }
    }
}

void menu3(LinkedList<Student>& student_list, LinkedList<Course>& course_list){
    Student* studentPtr = findStudent(student_list);
    if(studentPtr){
        Course* coursePtr = findCourse(course_list);
        if(coursePtr){
            coursePtr->dropWithOutput(studentPtr);
        }
    }
}

void menu4(LinkedList<Course>& course_list){
    course_list.print_type_printFunc();
    cout<<endl;
}

int main(){
    string course_file_name, student_file_name;
    cout<<"Enter the course file name: ";
    cin>>course_file_name;
    cout<<"Enter the student file name: ";
    cin>>student_file_name;

    LinkedList<Course> course_list(false);
    LinkedList<Student> student_list(false);

    if(!creative_course_list(course_file_name, course_list)) return 0;
    if(!creative_student_list(student_file_name, course_list, student_list)) return 0;
    int input = 0;
    while(input != 5){
        input = printMenu();
        switch(input){
            case 1:
                menu1(student_list);
                break;
            case 2:
                menu2(student_list, course_list);
                break;
            case 3:
                menu3(student_list, course_list);
                break;
            case 4:
                menu4(course_list);
                break;
            default:
                input = 5;
        }
    }

    return 0;
}

