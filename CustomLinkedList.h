#ifndef CUSTOM_LINKED_LIST_H
#define CUSTOM_LINKED_LIST_H

#include <iostream>
#include <stdexcept>  
using namespace std;

template <typename T>
class Node {
public:
    T data;       
    Node* next; 
    Node(const T& data) : data(data), next(nullptr) {}
};

template <typename T>
class CustomLinkedList {
private:
    Node<T>* head;  
    int size; 

public:
    CustomLinkedList() : head(nullptr), size(0) {}

    ~CustomLinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    int getSize() const {
        return size;
    }

    T* insert(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
        return &(newNode->data);
    }

    bool deleteNode(const T& data) {
        if (!head) return false;

        if (head->data == data) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        Node<T>* current = head;
        while (current->next && current->next->data != data) {
            current = current->next;
        }

        if (current->next) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }

        return false;
    }

    T* search(const T& data) const {
        Node<T>* current = head;
        while (current) {
            if (current->data == data) {
                return &(current->data); 
            }
            current = current->next;
        }
        return nullptr;  
    }

    T* operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return &(current->data); 
    }

    const T* operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return &(current->data); 
    }

    void print() const {
        Node<T>* current = head;
        while (current) {
            cout<<endl;
            current->data.print();
            current = current->next;
        }
        cout << endl;
    }
};

#endif 
