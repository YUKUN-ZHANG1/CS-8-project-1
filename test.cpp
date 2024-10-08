#include "CustomLinkedList.h"
#include <iostream>
using namespace std;

int main() {
    CustomLinkedList<int> intList;

    // 插入元素
    intList.insert(10);
    intList.insert(20);
    intList.insert(30);

    // 使用 [] 运算符访问元素的地址
    int* pElement = intList[1];
    cout << "Element at index 1 (address): " << pElement << endl;
    cout << "Value at index 1: " << *pElement << endl;

    // 修改链表中的数据通过指针
    *pElement = 50;
    cout << "After modification: ";
    intList.print();

    return 0;
}
