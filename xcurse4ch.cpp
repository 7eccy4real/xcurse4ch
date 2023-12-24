#include <iostream>


class Node {
public:
    int key;
    Node* p;

    Node() : key(0), p(nullptr) {}

    Node(int k, Node* next) : key(k), p(next) {}

    ~Node() {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack();

    bool isEmpty() const;

    bool isFull() const;

    Stack copyStack() const;

    void push(int key);

    void pop();

    void remove();

    int length() const;

    void print() const;

    void invert();

    static Stack mergeStacks(const Stack& stack1, const Stack& stack2);

    void removeDuplicates();

    bool contains(int key) const;
};

Stack::~Stack() {
    remove();
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

bool Stack::isFull() const {
    return false;
}

Stack Stack::copyStack() const {
    Stack newStack;
    Node* temp = top;

    while (temp != nullptr) {
        newStack.push(temp->key);
        temp = temp->p;
    }

    return newStack;
}

void Stack::push(int key) {
    Node* newNode = new Node(key, top);
    top = newNode;
}

void Stack::pop() {
    if (isEmpty()) {
        std::cout << "Stack is empty" << std::endl;
        return;
    }

    Node* temp = top;
    top = top->p;

    std::cout << "Добавленный элемент: " << temp->key << std::endl;
    delete temp;
}

void Stack::remove() {
    while (!isEmpty()) {
        pop();
    }
}

int Stack::length() const {
    int count = 0;
    Node* temp = top;

    while (temp != nullptr) {
        count++;
        temp = temp->p;
    }

    return count;
}

void Stack::print() const {
    if (isEmpty()) {
        std::cout << "Stack is empty" << std::endl;
        return;
    }

    Node* temp = top;

    while (temp != nullptr) {
        std::cout << temp->key << " ";
        temp = temp->p;
    }

    std::cout << std::endl;
}

void Stack::invert() {
    Stack reversedStack;
    Node* temp = top;

    while (temp != nullptr) {
        reversedStack.push(temp->key);
        temp = temp->p;
    }

    *this = reversedStack.copyStack();
}

Stack Stack::mergeStacks(const Stack& stack1, const Stack& stack2) {
    Stack mergedStack = stack1.copyStack();

    Node* temp = stack2.top;

    while (temp != nullptr) {
        mergedStack.push(temp->key);
        temp = temp->p;
    }

    return mergedStack;
}

void Stack::removeDuplicates() {
    Stack uniqueStack;
    Node* temp = top;

    while (temp != nullptr) {
        // Если элемент еще не встречался, добавляем его в уникальный стек
        if (!uniqueStack.contains(temp->key)) {
            uniqueStack.push(temp->key);
        }
        temp = temp->p;
    }

    *this = uniqueStack.copyStack();
}

bool Stack::contains(int key) const {
    Node* temp = top;

    while (temp != nullptr) {
        if (temp->key == key) {
            return true;
        }
        temp = temp->p;
    }

    return false;
}

int main() {
    setlocale(LC_ALL, "Russian");
    Stack stack1, stack2;
    int choice;

    do {
        std::cout << "\nВыберите операцию:\n";
        std::cout << "1. Добавить новый элемент в Стек1\n";
        std::cout << "2. Добавить новый элемент в Стек2\n";
        std::cout << "3. Удалить элемент из Стек1 и вывести на экран\n";
        std::cout << "4. Удалить элемент из Стек2 и вывести на экран\n";
        std::cout << "5. Инвертировать Стек1\n";
        std::cout << "6. Сложить стеки\n";
        std::cout << "7. Удаление \"двойников\" из Стека1\n";
        std::cout << "8. Вывести стек1 в терминал\n";
        std::cout << "0. Выход\n";

        std::cout << "Жду вашего приказа: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            std::cout << "Введите значение для Стека1: ";
            std::cin >> value;
            stack1.push(value);
            break;
        }
        case 2: {
            int value;
            std::cout << "Введите значение для Стека2: ";
            std::cin >> value;
            stack2.push(value);
            break;
        }
        case 3:
            stack1.pop();
            break;
        case 4:
            stack2.pop();
            break;
        case 5:
            stack1.invert();
            std::cout << "Инвертированный Стек1.\n";
            break;
        case 6: {
            Stack mergedStack = Stack::mergeStacks(stack1, stack2);
            std::cout << "Объединенный Стек: ";
            mergedStack.print();
            break;
        }
        case 7:
            stack1.removeDuplicates();
            std::cout << "\"Двойники\" удалены из Стека1.\n";
            break;
        case 8:
            std::cout << "Стек1: ";
            stack1.print();
            break;
        case 0:
            std::cout << "Завершение программы.\n";
            break;
        default:
            std::cout << "Неправильный приказ. Повторите еще раз.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}

