#ifndef NODE_H
#define NODE_H

#include <iostream>//已完成测试
using namespace std;

template <typename T>
class node{
    public:
    node(T* object_ = nullptr, node<T>* link_ = nullptr){
        this->object_ = object_;
        this->link_ = link_;
    }

    T* object()const{return object_;}
    node<T>* link()const{return link_;}
    void set_object(const T* object_){
        this->object_ = object_;
    }
    void set_link(node<T>* link_){
        this->link_ = link_;
    }

    void freeObject(){
        if(object_) {
            delete object_;
            object_ = nullptr;
        }
    }

    void print(){
        object_->print();
    }

    friend bool operator< (const node<T>& A, const node<T>& B){return *A.object_<*B.object_;}
    friend bool operator> (const node<T>& A, const node<T>& B){return *A.object_>*B.object_;}
    friend bool operator==(const node<T>& A, const node<T>& B){return *A.object_==*B.object_;}
    friend bool operator<=(const node<T>& A, const node<T>& B){return *A.object_<=*B.object_;}
    friend bool operator>=(const node<T>& A, const node<T>& B){return *A.object_>=*B.object_;}
    friend bool operator!=(const node<T>& A, const node<T>& B){return *A.object_!=*B.object_;}


    friend bool operator< (const node<T>& A, const T& B){return *A.object_<B;}
    friend bool operator> (const node<T>& A, const T& B){return *A.object_>B;}
    friend bool operator==(const node<T>& A, const T& B){return *A.object_==B;}
    friend bool operator<=(const node<T>& A, const T& B){return *A.object_<=B;}
    friend bool operator>=(const node<T>& A, const T& B){return *A.object_>=B;}
    friend bool operator!=(const node<T>& A, const T& B){return *A.object_!=B;}

    template <typename U>
    friend bool operator< (const node<T>& A, const U& B){return *A.object_<B;}
    template <typename U>
    friend bool operator> (const node<T>& A, const U& B){return *A.object_>B;}
    template <typename U>
    friend bool operator==(const node<T>& A, const U& B){return *A.object_==B;}
    template <typename U>
    friend bool operator<=(const node<T>& A, const U& B){return *A.object_<=B;}
    template <typename U>
    friend bool operator>=(const node<T>& A, const U& B){return *A.object_>=B;}
    template <typename U>
    friend bool operator!=(const node<T>& A, const U& B){return *A.object_!=B;}

    friend ostream& operator<<(ostream& out, const node& A){
        out<< *(A.object());
        return out;
    }

    private:
    T* object_;
    node<T>* link_;
};

#endif
