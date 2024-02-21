using namespace std;
#include <iostream>
#include <string>
#include <vector>



template <typename T>
class LinkedList {
public:
    struct Node {
        Node();
        T data;
        Node* next;
        Node* prev;
        Node(const T& newData) : data(newData), next(nullptr), prev(nullptr) {}
    };









    Node* head;
    Node* tail;
    int count = 0;
    void AddHead(const T& data);
    void AddTail(const T& newData);
    void AddNodesHead(const T values[], int capacity);
    void AddNodesTail(const T values[], int capacity);
    void PrintForward()const;
    void PrintReverse()const;
    int NodeCount()const;
    void Clear();
    Node* Head() const;
    ~LinkedList() { Clear(); }
    Node* Tail() const;
    Node* GetNode(int index) const;
    void FindAll(std::vector<Node*>& nodes, const T& value) const;
    Node* Find(const T& value)const;
    T& operator[](int index);
    const T& operator[](int index) const;
    LinkedList& operator=(const LinkedList& other);
    void InsertBefore(Node* node, const T& data);
    void InsertAfter(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);
    bool operator==(const LinkedList<T>& rhs) const;
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;


    //default constructor
    LinkedList(){
        head = nullptr;
        tail = nullptr;
        count = 0;
    }


    //copy constructor
    LinkedList(const LinkedList& other){
        head = nullptr;
        tail = nullptr;
        Node* current = other.head;
        while (current != nullptr) {
            AddTail(current->data);
            current = current->next;
        }
    }


};

template <typename T>
void LinkedList<T>::AddHead( const T& data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    if (head != nullptr) {
        head->prev = newNode;
        head = newNode;
        count++;
    }
    else {
        tail = newNode;
        head = newNode;
        count++;
    }
}

template <typename T>
void LinkedList<T>::AddTail(const T& newData) {
    Node* newNode = new Node(newData);

    if (tail == nullptr) {
        head = newNode;
        tail = head;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}
template <typename T>
void LinkedList<T>::AddNodesHead(const T values[], int capacity) {
    for (int i = 0; i < capacity; i++)
        AddHead(values[i]);
}
template <typename T>
void LinkedList<T>::AddNodesTail(const T values[], int capacity) {
    for (int i = 0; i < capacity; i++)
        AddTail(values[i]);
}
template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << endl;
        current = current->next;
    }
}
template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node* current = tail;
    while (current != nullptr) {
        cout << current->data << endl;
        current = current->prev;
    }
}
template <typename T>
int LinkedList<T>::NodeCount() const {
    return count;
}
template <typename T>
void LinkedList<T>::Clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}
template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& nodes, const T& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            nodes.push_back(current);
        }
        current = current->next;
    }
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& value) const {

    Node* current = head;
    while (current != nullptr) {
        if (current->data == value)
            return current;
        current = current->next;

    }
    return nullptr;
}



template <typename T>
T& LinkedList<T>::operator[](int index) {
    return GetNode(index)->data;
}
template <typename T>
const T& LinkedList<T>::operator[](int index) const {
    return GetNode(index)->data;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other){
    Clear();
    head = nullptr;
    tail = nullptr;
    Node* current = other.head;
    while (current != nullptr) {
        AddTail(current->data);
        current = current->next;
    }
    return *this;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
    if (node == head) {
        AddHead(data);
        return;
    }
    Node* newNode = new Node(data);
    newNode->next = node;
    newNode->prev = node->prev;
    node->prev->next = newNode;
    node->prev = newNode;
    count++;
}


template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
    if (node == tail) {
        AddTail(data);
        return;
    }
    Node* newNode = new Node(data);
    newNode->prev = node;
    newNode->next = node->next;
    node->next = newNode;
    count++;
}


template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
    if (index == NodeCount())
    {
        AddTail(data);
        return;
    }
    Node* current = GetNode(index);
    InsertBefore(current, data);


}
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    if (head->data == rhs.head->data and tail->data == rhs.tail->data and NodeCount() == rhs.NodeCount())
        return true;
    return false;
}

//removal functions
template <typename T>
bool LinkedList<T>::RemoveHead(){
    if (NodeCount() == 0) {
        head = nullptr;
        tail = nullptr;
        return false;
    }
    else if(NodeCount()== 1){
        delete tail;
        head = nullptr;
        tail = nullptr;
        count--;
        return true;
    }
    else {
        Node* newNode = head;
        head = newNode->next;
        head->prev = nullptr;
        delete newNode;
        count--;
        return true;
    }

}



template <typename T>
bool LinkedList<T>::RemoveTail(){
    if (NodeCount() == 0) {
        head = nullptr;
        tail = nullptr;
        return false;
    }
    else if(NodeCount()== 1){
        delete tail;
        head = nullptr;
        tail = nullptr;
        count--;
        return true;
    }
    else {
        Node* newNode = tail;
        tail = newNode->prev;
        tail->next = nullptr;
        delete newNode;
        count--;
        return true;
    }
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index){
    if (index >= NodeCount() )
        return false;
    else if (index == NodeCount() -  1) {
        return RemoveTail();
    }
    else if(index == 0) {
        return RemoveHead();
    }
    else{
        Node* newNode = GetNode(index);
        newNode->prev->next = newNode->next;
        newNode->next->prev = newNode->prev;
        newNode->prev->next = newNode->next;
        newNode->next->prev = newNode->prev;

        if (newNode->prev == nullptr)
            head = newNode->next;

        if (newNode->next == nullptr)
            tail = newNode->prev;

        delete newNode;
        count--;
        return true;
    }


}


template <typename T>
unsigned int LinkedList<T>::Remove(const T& data){
    unsigned int removed = 0;
    Node* current = head;
    Node* remove;
    while(current)
    {
        if(current->data == data)
        {
            current->next->prev = current->prev;
            current->prev->next = current->next;
            removed += 1;
            count--;
            remove = current;
            current = current->next;
            delete remove;
        }
        else
            current = current->next;
    }

    return removed;
}
template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node)const{
    Node* newNode = head;
    while (newNode != node)
        newNode = newNode->next;
    while(newNode)
    {
        cout << newNode->data << endl;
        newNode = newNode->next;
    }
}


template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node)const{
    Node* newNode = tail;
    while (newNode != node)
        newNode = newNode->prev;
    while (newNode)
    {
        cout << newNode->data << endl;
        newNode = newNode->prev;
    }

}






















