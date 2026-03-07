#ifndef SOFTACADEMY_LIST_HPP
#define SOFTACADEMY_LIST_HPP

#include <cstddef>
#include <utility>

namespace softacademy {

template <typename T>
class LinkedList {
private:
    struct Node {
        T m_value;
        Node* m_prev;
        Node* m_next;

        Node(const T& v, Node* p = nullptr, Node* n = nullptr)
            :m_value(v)
            ,m_prev(p)
            ,m_next(n){}
        Node(T&& v, Node* p = nullptr, Node* n = nullptr)
            :m_value(std::move(v))
            ,m_prev(p)
            ,m_next(n){}
    };

public:
    using value_type = T;
    using size_type  = std::size_t;

    LinkedList() noexcept
        :m_head(nullptr)
        ,m_tail(nullptr)
        ,m_size(0){}
    LinkedList(const LinkedList& other)
        :m_head(nullptr)
        , m_tail(nullptr)
        , m_size(0) {
        copy_from(other);
    }
    LinkedList(LinkedList&& other) noexcept
        :m_head(nullptr)
        , m_tail(nullptr)
        , m_size(0) {
        move_from(std::move(other));
    }
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            destroy_all();
            copy_from(other);
        }
        return *this;
    }
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != other) {
            destroy_all();
            move_from(std::move(other));
        }
        return *this;
    }
    ~LinkedList() {
        destroy_all;
    }

    size_type size() const noexcept {
        return m_size;
    }
    bool empty() const noexcept {
        return m_size == 0;
    }

    T& front() {
        return m_head->m_value;
    }
    const T& front() const {
        return m_head->m_value;
    }
    T& back() {
        return m_tail->m_value;
    }
    const T& back() const {
        return m_tail->m_value;
    }

    void clear() noexcept {
        destroy_all();
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value, nullptr, m_head);
        if (m_head) {
            m_head->m_prev = newNode;
        }
        else {
            m_tail = newNode;
        }
        m_head = newNode;
        m_size++;
    }
    void push_front(T&& value) {
        Node* newNode = new Node(std::move(value), nullptr, m_head);
        if (m_head) {
            m_head->m_prev = newNode;
        }
        else {
            m_tail = newNode;
        }
        m_head = newNode;
        m_size++;
    }
    void push_back(const T& value) {
        Node newNode = new Node(value, nullptr, m_tail);
        if (m_tail) {
            m_tail->m_next = newNode;
        }
        else {
            m_head = newNode;
        }
        m_head = newNode;
        m_size++;
    }
    void push_back(T&& value) {
        Node* newNode = new Node(std::move(value), nullptr, m_tail);
        if (m_tail) {
            m_tail->m_next = newNode;
        }
        else {
            m_head = nullptr;
        }
        m_head = newNode;
        m_size++;
    }
    void pop_front() {
        if (!m_head) {
            return;
        }
        Node* tmp = m_head;
        m_head = m_head->m_next;
        if (m_heda) {
            m_head->m_prev = nullptr;
        }
        else {
            m_tail = nullptr;
        }
        delete tmp;
        m_size--;
    }
    void pop_back() {
        if (!m_tail) {
            return;
        }
        Node* tmp = m_tail;
        m_tail = m_tail->m_prev;
        if (m_tail) {
            m_tail->m_next = nullptr;
        }
        else {
            m_head = nullptr;
        }
        delete tmp;
        m_size--;
    }

    void swap(LinkedList& other) noexcept {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
        std::swap(m_size, other.m_size);
    }

private:
    Node* m_head;
    Node* m_tail;
    size_type m_size;

    void copy_from(const LinkedList& other) {
        Node* curr = other.m_head;
        while (curr) {
            push_back(curr->m_value);
            curr = curr->m_next;
        }
    }
    void move_from(LinkedList&& other) noexcept {
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }
    void destroy_all() noexcept {
        Node* curr = m_head;
        while (curr) {
            Node* next = curr->m_next;
            delete curr;
            curr = next;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }
};

} // namespace softacademy

#endif
