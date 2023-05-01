#pragma once
template <typename T>
class Container {

    template<typename U>
    struct Node {
        U m_value = {};
        Node* m_next = nullptr;
        Node* m_prev = nullptr;
    };

public:
    Container() { m_head = m_tail = nullptr; m_len = 0; }
    void push_back(const T & value);
    void push_front(const T & value);
    T remove_back();
    T remove_front();
    T get_first() { return m_head->m_value; }
    T get_last() { return m_tail->m_value; }
    int get_length() { return m_len; }
    void swap(Container & new_cont);
    void reverse();
    void clear();

    class iterator {
        Node<T> * ptr;
    public:
        iterator() { ptr = nullptr; }
        iterator(Node<T> * p) { ptr = p; }
        Node<T> * get_ptr() { return ptr; }
        T& operator*() { return ptr->m_value; }
        void operator=(iterator iter) { ptr = iter.get_ptr(); }
        bool operator==(iterator iter) { return ptr == iter.get_ptr(); }
        void operator++() { if (ptr != nullptr) ptr = ptr->m_next; }
        void operator--() { if (ptr != nullptr) ptr = ptr->m_prev; }
        bool operator!=(iterator iter) { return ptr != iter.get_ptr(); }
    };
    iterator begin() { return iterator(m_head); }
    iterator end() { return iterator(m_tail); }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os,  Container<U> & cunt);

private:
    int m_len;
    Node<T> * m_head, * m_tail;
};

template<typename T>
std::ostream& operator<<(std::ostream& os,  Container<T> & cunt) {
    for (typename Container<T>::iterator it = cunt.begin(); it != nullptr; ++it)
        os << *it << "\n";
    os << "\n";
    return os;
}

template<typename T>
void Container<T>::push_front(const T & a) {
    Node<T> * ptr = new Node<T>;
    ptr->m_value = a;
    ptr->m_next = nullptr;
    ptr->m_prev = m_tail;
    if (m_len == 0) {
        m_head = m_tail = ptr;
        ++m_len;
        return;
    }
    m_tail->m_next = ptr;
    m_tail = ptr;
    ++m_len;
}

template<typename T>
void Container<T>::push_back(const T & a) {
    Node<T> * ptr = new Node<T>;
    ptr->m_value = a;
    ptr->m_next = m_head;
    ptr->m_prev = nullptr;
    m_head->m_prev = ptr;
    m_head = ptr;
    ++m_len;
}

template<typename T>
T Container<T>::remove_back() {
    if (m_head == nullptr) {
        throw std::runtime_error("Empty list");
    }
    Node<T> * temp = m_head;
    if (temp->m_next == nullptr) {
        m_head = nullptr;
    }
    else {
        m_head = m_head->m_next;
    }
    T res = temp->m_value;
    delete temp;
    --m_len;
    return res;
}

template<typename T>
T Container<T>::remove_front() {
    if (m_tail == nullptr) {
        throw std::runtime_error("Empty list");
    }

    Node<T> * temp = m_tail;
    m_tail = m_tail -> m_prev;
    if (m_tail) {
        m_tail->m_next = nullptr;
    }
    else {
        m_head = nullptr;
    }
    T res = temp->m_value;
    delete temp;
    --m_len;
    return res;
}

template<typename T>
void Container<T>::clear() {
    if (m_head == nullptr) return;
    Node<T> * temp = m_head;
    Node<T>* next = nullptr;
    while (temp != nullptr) {
        delete temp;
        temp = next;
    }
    m_head = m_tail = nullptr;
    m_len = 0;
}

template<typename T>
void Container<T>::reverse() {
    Node<T> * copy_head = m_head;
    Node<T> * ptr = m_tail;
    if (ptr == nullptr) {
        return;
    }
    ptr->m_next = ptr->m_prev;
    ptr->m_prev = nullptr;
    while (ptr->m_next != nullptr) {
        Node<T> * ptr2 = ptr->m_next;
        ptr2->m_next = ptr2->m_prev;
        ptr2->m_prev = ptr;
        ptr = ptr2;
    }
    m_head = m_tail;
    m_tail = copy_head;
}

template<typename T>
void Container<T>::swap(Container & new_cont) {
    Node<T> * new_head = new_cont.m_head;
    Node<T> * new_tail = new_cont.m_tail;
    int new_len = new_cont.get_length();
    new_cont.m_head = m_head;
    new_cont.m_tail = m_tail;
    new_cont.m_len = m_len;
    m_head = new_head;
    m_tail = new_tail;
    m_len = new_len;
}