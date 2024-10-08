#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iomanip>
#include "LinkedList.h"
using namespace std;

class Course;

class Student{
    private:
    int id;
    string name;
    LinkedList<Course> enrolled;
    LinkedList<Course> waitlisted;

    public:
    Student(int id = 0, std::string name = "NULL")
        : id(id), name(name), enrolled(), waitlisted(){}
    string getName()const{return name;}
    int getId()const{return id;}
    int getEnrolledSize(){return enrolled.getSize();}
    int getWaitlistedSize(){return waitlisted.getSize();}
    void setName(string name){this->name=name;}
    void setId(int id){this->id=id;}

    void pushEnrolled(Course* course);//只修改自身注册课程，不改变其他类
    void pushWaitlisted(Course* course);//只修改自身注册课程，不改变其他类
    bool popEnrolled(Course* course);//只修改自身注册课程，不改变其他类
    bool popWaitlisted(Course* course);//只修改自身注册课程，不改变其他类
    void useAddCode(Course* course);

    void enrollWithOutput(Course* course);
    void dropWithOutput(Course* course);
    void enroll(Course* course);
    void drop(Course* course);

    bool find(Course* course)const;
    bool findInEnrolled(Course* course)const;
    bool findInWaitlisted(Course* course)const;

    void print()const;
    void printEnrolled()const;
    void printWaitlisted()const;

    friend bool operator< (const Student& A, const Student& B){return A.id<B.id;}
    friend bool operator> (const Student& A, const Student& B){return A.id>B.id;}
    friend bool operator==(const Student& A, const Student& B){return A.id==B.id;}
    friend bool operator<=(const Student& A, const Student& B){return A.id<=B.id;}
    friend bool operator>=(const Student& A, const Student& B){return A.id>=B.id;}
    friend bool operator!=(const Student& A, const Student& B){return A.id!=B.id;}
    friend bool operator< (const Student& A, const int& B){return A.id<B;}
    friend bool operator> (const Student& A, const int& B){return A.id>B;}
    friend bool operator==(const Student& A, const int& B){return A.id==B;}
    friend bool operator<=(const Student& A, const int& B){return A.id<=B;}
    friend bool operator>=(const Student& A, const int& B){return A.id>=B;}
    friend bool operator!=(const Student& A, const int& B){return A.id!=B;}

    friend ostream& operator<<(ostream& out, const Student& student){
        out<<setw(5)<<student.id<<"  "<<student.name;
        return out;
    }
};

#endif  