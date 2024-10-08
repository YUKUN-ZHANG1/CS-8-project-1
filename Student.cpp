#include "Student.h"
#include "Course.h"


void Student::pushEnrolled(Course* course){
    enrolled.insert(course);
}
void Student::pushWaitlisted(Course* course){
    waitlisted.insert(course);
}
bool Student::popEnrolled(Course* course){
    return enrolled.deleteNode(course);
}
bool Student::popWaitlisted(Course* course){
    return waitlisted.deleteNode(course);
}

void Student::useAddCode(Course* course){
    enrolled.insertNode(waitlisted.popNode(course));
}


bool Student::find(Course* course)const{
    return (findInEnrolled(course)||findInWaitlisted(course));
}
bool Student::findInEnrolled(Course* course)const{
    return (nullptr != enrolled.search(course));
}
bool Student::findInWaitlisted(Course* course)const{
    return (nullptr != waitlisted.search(course));
}

void Student::enrollWithOutput(Course* course){
    course->enrollWithOutput(this);
}

void Student::dropWithOutput(Course* course){
    course->dropWithOutput(this);
}

void Student::enroll(Course* course){
    course->enroll(this);
}
void Student::drop(Course* course){
    course->drop(this);
}

void Student::printEnrolled()const{
    enrolled.print("(R) ");
}
void Student::printWaitlisted()const{
    waitlisted.print("(W) ");
}
void Student::print()const{
    cout<<"You registered "<<enrolled.getSize()<<" courses and waitlisted "<<waitlisted.getSize()<<" courses."<<endl;
    printEnrolled();
    printWaitlisted();
}
