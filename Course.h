#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "LinkedList.h"
using namespace std;
class Student;

class Course{
    private:    
    const int MAX_ENROLL = 10;
    string code;
    string title;
    LinkedList<Student> enrollList;
    Queue<Student> waitlist;

    public:
    Course(string code = "NULL", string title = "NULL")
        : code(code),title(title),enrollList(),waitlist(){}
    void setCode(string code){this->code = code;}
    void setTitle(string title){this->title = title;}
    string getCode()const{return code;}
    string getTitle()const{return title;}


    bool haveStudent(Student* student)const;
    bool haveStudentInEnroll(Student* student)const;
    bool haveStudentInWaitlist(Student* student)const;

    void enrollWithOutput(Student* student);
    void dropWithOutput(Student* student);
    void addEnroll(Student* student);
    void addWaitlist(Student* student);

    //无输出版本：
    void enroll(Student* student);
    void drop(Student* student);
    void attend();//邀请其他学生进入注册课程

    void printEnrollList()const;
    void printWaitlist()const;
    void print()const;

    friend bool operator< (const Course& A, const Course& B){return A.code<B.code;}
    friend bool operator> (const Course& A, const Course& B){return A.code>B.code;}
    friend bool operator==(const Course& A, const Course& B){return A.code==B.code;}
    friend bool operator<=(const Course& A, const Course& B){return A.code<=B.code;}
    friend bool operator>=(const Course& A, const Course& B){return A.code>=B.code;}
    friend bool operator!=(const Course& A, const Course& B){return A.code!=B.code;}
    friend bool operator< (const Course& A, const string& B){return A.code<B;}
    friend bool operator> (const Course& A, const string& B){return A.code>B;}
    friend bool operator==(const Course& A, const string& B){return A.code==B;}
    friend bool operator<=(const Course& A, const string& B){return A.code<=B;}
    friend bool operator>=(const Course& A, const string& B){return A.code>=B;}
    friend bool operator!=(const Course& A, const string& B){return A.code!=B;}

    friend ostream& operator<<(ostream& out, const Course& course){
        out<<std::left<<setw(10)<<course.code<<course.title<<std::right;
        return out;
    }
};

#endif  