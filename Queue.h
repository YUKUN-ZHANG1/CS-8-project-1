#include "node.h"
using namespace std;

template <typename T>
class Queue{
    private:
    node<T>* front;
    node<T>* back;
    int size;
    bool virtualPtr;

    public:
    Queue(bool virtualPtr = true){
        front = nullptr;
        back = nullptr;
        size = 0;
        this->virtualPtr = virtualPtr;
    }

    ~Queue(){
        node<T>* temp;
        if(virtualPtr){
            while(front){
                temp = front;
                front = front->link();
                delete temp;
            }
        }else{
            while(front){
                temp = front;
                front = front->link();
                temp->freeObject();
                delete temp;
            } 
        }
    }

    int getSize()const{return size;}

    bool empty()const{
        return !front;
    }

    void push(T* object){
        node<T>* temp = new node<T>(object);
        if(!back){
            back = temp;
            front = temp;
        }else{
            back->set_link(temp);
            back=temp;
        }
        size++;
    }

    void pushNode(node<T>* temp){
        temp->set_link(nullptr);
        if(!back){
            back = temp;
            front = temp;
        }else{
            back->set_link(temp);
            back=temp;
        }
        size++;
    }

    T* pop(){
        if(!front){
            return nullptr;
        }
        node<T>* temp = front;
        T* temp_object = front->object();
        if(front == back){
            front = nullptr;
            back = nullptr;
        }else{
            front = front->link();
        }
        delete temp;
        size--;
        return temp_object;
    }

    node<T>* popNode(){
        if(!front){
            return nullptr;
        }
        node<T>* temp = front;
        if(front == back){
            front = nullptr;
            back = nullptr;
        }else{
            front = front->link();
        }
        temp->set_link(nullptr);
        size--;
        return temp;
    }

    node<T>* search(T* object)const{
        node<T>* temp;
        for( temp = front; temp; temp = temp->link()){
            if(*(temp->object())==*(object))
                break;
        }
        return temp;
    }

    template <typename U>
    T* search(U object)const{
        node<T>* temp = front;
        while (temp) {
            if (*(temp->object()) == object) {
                return temp->object();
            }
            temp = temp->link();
        }
        return nullptr;
    }

    //需要一个删除：删除指定原元素
    bool deleteNode(T* object) {
        if (!front) {
            return false;  // 队列为空
        }

        // 如果要删除的是头节点
        if(*(front->object()) == *object) {
            node<T>* temp = front;
            front = front->link();
            if(!front){  // 如果只有一个节点，更新 back
                back = nullptr;
            }
            delete temp;
            size--;
            return true;
        }

        // 遍历队列，查找要删除的元素
        node<T>* current = front->link();
        node<T>* previous = front;

        while (current) {
            if (*(current->object()) == *object) {
                previous->set_link(current->link());
                if (current == back) {  // 如果删除的是尾节点，更新 back
                    back = previous;
                }
                delete current;
                size--;
                return true;  // 成功删除
            }
            previous = current;
            current = current->link();
        }

        return false;  // 未找到要删除的元素
    }

    void print(string link_sign = "")const{
        node<T>* temp = front;
        while (temp) {
            cout<<link_sign<<*temp<<endl;
            temp = temp->link();
        }
    }
/*
    void freeObject(){
        node<T>* temp = front;
        while (temp) {
            temp ->freeObject();
            temp = temp->link();
        }
    }
*/
};