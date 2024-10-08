#include "Course.h"
#include "Student.h"

bool Course::haveStudent(Student* student)const{
    return (haveStudentInEnroll(student)||haveStudentInWaitlist(student));
}

bool Course::haveStudentInEnroll(Student* student)const{
    return enrollList.search(student) != nullptr;
}

bool Course::haveStudentInWaitlist(Student* student)const{
    return waitlist.search(student) != nullptr;
}



void Course::enrollWithOutput(Student* student){
    if(!student){
        cout<<"there is no student"<<endl;
        return;
    } 
    
    if (student->findInWaitlisted(this) || haveStudentInWaitlist(student)) {
        cout << "Fail, you are already in the " << code << " waitlist." << endl;
        return;
    }
    if (student->findInEnrolled(this) || haveStudentInEnroll(student)) {
        cout << "Fail, you are already enrolled in the " << code << "." << endl;
        return;
    }

    if (enrollList.getSize() < MAX_ENROLL) {
        student->pushEnrolled(this);
        enrollList.insert(student);
        cout << "Success, you are enrolled in the " << code << "." << endl;
    } else {
        student->pushWaitlisted(this);
        waitlist.push(student);
        cout << "Success, you are added to the " << code << " waitlist." << endl;
    }
}
void Course::dropWithOutput(Student* student){
    if(!student){
        cout<<"there is no student"<<endl;
        return;
    }

    if (student->popWaitlisted(this)&&waitlist.deleteNode(student)) {
        cout << "Success, you are removed from the " << code << " waitlist." << endl;
        return;
    }
    if (student->popEnrolled(this)&&enrollList.deleteNode(student)) {
        cout << "Success, you droped the " << code << "." << endl;
        attend();
        return;
    }

    cout << "Fail, you are not in the " << code << "." << endl;
}


void Course::addEnroll(Student* student){
    if(!student){
        return;
    } 

    if (enrollList.getSize() < MAX_ENROLL) {
        student->pushEnrolled(this);
        enrollList.insert(student);
    } else {
    }
}
void Course::addWaitlist(Student* student){
    if(!student){
        return;
    } 
    student->pushWaitlisted(this);
    waitlist.push(student);
}

void Course::enroll(Student* student){
    if(!student){
        return;
    } 
    
    if (student->findInWaitlisted(this) || haveStudentInWaitlist(student)) {
        return;
    }
    if (student->findInEnrolled(this) || haveStudentInEnroll(student)) {
        return;
    }

    if (enrollList.getSize() < MAX_ENROLL) {
        student->pushEnrolled(this);
        enrollList.insert(student);
    } else {
        student->pushWaitlisted(this);
        waitlist.push(student);
    }
}
void Course::drop(Student* student){
    if(!student){
        return;
    }

    if (student->popWaitlisted(this)&&waitlist.deleteNode(student)) {
        return;
    }
    if (student->popEnrolled(this)&&enrollList.deleteNode(student)) {
        attend();
        return;
    }
}

void Course::attend(){
    if(!waitlist.empty()){
        node<Student>* temp= waitlist.popNode();
        if(!temp){
            Student* tempStudent = temp->object();
            enrollList.insertNode(temp);
            tempStudent->useAddCode(this);
        }
    }
}

void Course::printEnrollList()const{
    int size = enrollList.getSize();
    cout<<" [ "<<code<<' '<<title<<" ("<<size<<") ]"<<endl;
    cout<<"-----------------------------------------"<<endl;
    enrollList.print();
}
void Course::printWaitlist()const{
    int size = waitlist.getSize();
    if(size!=0){
        cout<<" < Waitlist ("<<size<<") >"<<endl;
        waitlist.print();
    }
}

void Course::print()const{
    printEnrollList();
    cout<<endl;
    printWaitlist();
}