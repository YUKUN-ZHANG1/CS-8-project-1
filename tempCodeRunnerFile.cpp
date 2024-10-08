#include "LinkedList.h"
#include "Course.cpp"
#include "Student.cpp"
#include <fstream>
#include <iostream>

void creative_course_list(string course_file_name, LinkedList<Course>& course_list);
void creative_student_list(string student_file_name, LinkedList<Course>& course_list, LinkedList<Student>& student_list);
int printMenu();
void menu1(LinkedList<Course>& course_list, LinkedList<Student>& student_list);
//void menu2(LinkedList<Course>& course_list, LinkedList<Student>& student_list);
//void menu3(LinkedList<Course>& course_list, LinkedList<Student>& student_list);
void menu4(LinkedList<Course>& course_list);


void creative_course_list(string course_file_name, LinkedList<Course>& course_list) {
    ifstream infile(course_file_name);
    
    if (!infile.is_open()) {
        cerr << "Failure to open file: " << course_file_name << endl;
        perror("Error");  // 使用 perror 打印更多文件打开错误的详细信息
        return;
    }
    cout << "File opened successfully: " << course_file_name;  // Debug 信息
    cout <<"hi";
    // 剩下的文件读取逻辑
    string courseCode, courseName;
    int enrolledCount, waitlistCount;
    cout<<"hi";
    while (infile >> courseCode >> courseName >> enrolledCount >> waitlistCount) {
        Course* tempCourse = new Course(courseCode, courseName);
        course_list.insert(tempCourse);
    }
}

void creative_student_list(string student_file_name, LinkedList<Course>& course_list, LinkedList<Student>& student_list){
    ifstream infile(student_file_name);
    
    if (!infile.is_open()) {
        cerr << "Failure to open file: " << student_file_name << endl;
        return;
    }
    string courseCode, studentName;
    int studentId, enrolledCount = 0, waitlistCount = 0;
    Student* studentTemp;
    Course* courseTemp = new Course;
    while(infile >> studentId >> studentName){
        studentTemp = new Student(studentId, studentName);
        student_list.insert(studentTemp);
        infile >> enrolledCount;
        while(enrolledCount>0){
            infile >> courseCode;
            courseTemp->setCode(courseCode);
            course_list.search(courseTemp)->object()->enroll(studentTemp);
            enrolledCount--;
        }
        infile >> waitlistCount;
        while(waitlistCount>0){
            infile >> courseCode;
            courseTemp->setCode(courseCode);
            course_list.search(courseTemp)->object()->enroll(studentTemp);
            waitlistCount--;
        }
    }
    delete courseTemp;
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

void menu1(LinkedList<Course>& course_list, LinkedList<Student>& student_list){
    Student* studentTemp1 = new Student, *studentTemp2;
    string name;
    int id;
    cout<<endl<<"Enter your id: ";
    cin>>id;
    studentTemp1->setId(id);
    studentTemp2 = student_list.search(studentTemp1)->object();
    cout<<"Enter your name: ";
    cin>>name;
    cout<<endl;
    if(studentTemp2 && name == studentTemp2->getName()){
        cout<<"You registered "<<studentTemp2->getEnrolledSize()<<" courses and waitlisted "<<studentTemp2->getWaitlistedSize()<<" courses."<<endl;
        studentTemp2->printEnrolled();
        studentTemp2->printEnrolled();
    }else{
        cout<<"The information does not match.";
    }
    cout<<endl;
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
    course_file_name = "courses.txt";
    student_file_name = "enrollment.txt";
    LinkedList<Course> course_list(true);
    LinkedList<Student> student_list(true);
    creative_course_list(course_file_name, course_list);
    creative_student_list(student_file_name, course_list, student_list);
    int input = 0;
    while(input!=5){
        input = printMenu();
        switch(input){
            case 1:
                menu1(course_list, student_list);
            case 2:
                //menu2(course_list, student_list);
            case 3:
                //menu3(course_list, student_list);
            case 4:
                menu4(course_list);
            default:
                input = 5;
        }
    }
}