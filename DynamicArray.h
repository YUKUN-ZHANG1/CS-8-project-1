template <typename T>
class DynamicArray {
private:
    T** array;        // 指向对象的指针数组
    int size;         // 当前数组中的元素个数
    int capacity;     // 数组的容量（实际分配的内存大小）

    // 动态调整数组容量
    void resize(int new_capacity) {
        T** new_array = new T*[new_capacity];
        for (int i = 0; i < size; i++) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
        capacity = new_capacity;
    }

public:
    DynamicArray(int init_capacity = 10) : size(0), capacity(init_capacity) {
        array = new T*[capacity];
    }

    ~DynamicArray() {
        for (int i = 0; i < size; i++) {
            delete array[i];  // 删除每个对象
        }
        delete[] array;  // 删除指针数组
    }

    int getSize() const {
        return size;
    }

    // 插入元素
    void insert(T* object) {
        if (size == capacity) {
            resize(capacity * 2);  // 扩容
        }
        array[size++] = object;
    }

    // 删除元素
    bool deleteNode(T* object) {
        for (int i = 0; i < size; i++) {
            if (*array[i] == *object) {  // 比较对象
                delete array[i];  // 删除对象
                // 移动后面的元素
                for (int j = i; j < size - 1; j++) {
                    array[j] = array[j + 1];
                }
                size--;
                return true;
            }
        }
        return false;
    }

    // 查找元素
    T* search(T* object) const {
        for (int i = 0; i < size; i++) {
            if (*array[i] == *object) {  // 比较对象
                return array[i];
            }
        }
        return nullptr;
    }

    // 打印数组元素
    void print(const std::string& prefix = "") const {
        for (int i = 0; i < size; i++) {
            std::cout << prefix << *array[i] << std::endl;
        }
    }
};
