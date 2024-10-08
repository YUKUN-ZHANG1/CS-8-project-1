#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
using namespace std;

template <typename T>
class LinkedList{
    private:
    node<T>* head;
    int size;
    bool virtualPtr;

    public:
    LinkedList(bool virtualPtr = true) : head(nullptr), size(0), virtualPtr(virtualPtr){}
    ~LinkedList(){
        node<T>* temp = head;
        if(virtualPtr){
            while(head){
                head = head->link();
                delete temp;
                temp = head;
            }
        }else{
            while(head){
                head = head->link();
                temp ->freeObject();
                delete temp;
                temp = head;
            }
        }
    }

    int getSize()const{return size;}

    void insert(T* object){
        if (!object){
            return;
        }
        node<T>* temp = new node<T>(object);
        if(!head){
            head = temp;
        }else if(*object < *(head->object())){
            temp->set_link(head);
            head = temp;
        }else{
            node<T>* ptr = head;
            for(; ptr->link(); ptr = ptr->link()){
                if(*(ptr->link()->object())>*object){
                    temp->set_link(ptr->link());
                    ptr->set_link(temp);
                    break;
                }
            }
            if(!temp->link()){
                ptr ->set_link(temp);
            }
        }
        size++;
    }

    void insertNode(node<T>* temp){
        if(!temp) return;
        temp->set_link(nullptr);
        if(!head){
            head = temp;
        }else if(*temp < *(head)){
            temp->set_link(head);
            head = temp;
        }else{
            node<T>* ptr = head;
            for(; ptr->link(); ptr = ptr->link()){
                if(*(ptr->link())>*temp){
                    temp->set_link(ptr->link());
                    ptr->set_link(temp);
                    break;
                }
            }
            if(!temp->link()){
                ptr ->set_link(temp);
            }
        }
        size++;
    }

    node<T>* search(T* object)const{
        if(object){
            node<T>* temp = head;
            while (temp) {
                if (*(temp->object()) == *object) {
                    return temp;
                }
                temp = temp->link();
            }
        } 
        return nullptr;
    }

    bool deleteNode(const T* object) {
        if (!head||!object) return false;

        if (*(head->object()) == *object) {
            node<T>* temp = head;
            head = head->link();
            delete temp;
            size--;
            return true;
        }

        node<T>* current = head->link();
        node<T>* prev = head;

        while (current && (*(current->object()) != *object)) {
            prev = current;
            current = current->link();
        }

        if (!current) {
            return false;
        }

        prev->set_link(current->link());
        delete current;
        size--;
        return true; 
    }

    node<T>* popNode(const T* object) {
        if (!head||!object) return nullptr;
        if (*(head) == *object) {
            node<T>* temp = head;
            head = head->link();
            temp->set_link(nullptr);
            size--;
            return temp;
        }

        node<T>* current = head->link();
        node<T>* prev = head;

        while (current && (*(current) != *object)) {
            prev = current;
            current = current->link();
        }

        if (!current) {
            return nullptr;
        }

        prev->set_link(current->link());
        current->set_link(nullptr);
        size--;
        return current; 
    }

    void print(string link_sign = "")const{
        node<T>* temp = head;
        while (temp) {
            cout<<link_sign<<*temp<<endl;
            temp = temp->link();
        }
    }

    void print_type_printFunc(string link_sign = "")const{
        node<T>* temp = head;
        while (temp) {
            cout<<link_sign;
            temp->object()->print();
            cout<<endl;
            temp = temp->link();
        }
    }

/*
    void freeObject(){
        node<T>* temp = head;
        while (temp) {
            temp ->freeObject();
            temp = temp->link();
        }
    }
*/
};

#endif 