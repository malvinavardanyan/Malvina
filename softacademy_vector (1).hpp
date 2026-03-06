#ifndef SOFTACADEMY_VECTOR_HPP
#define SOFTACADEMY_VECTOR_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>

namespace softacademy {

template <typename T>
class Vector {
public:
    using value_type = T;
    using size_type  = std::size_t;

    Vector() noexcept
        :m_data(nullptr)
        , m_size()
        , m_capacity(0) {};
    explicit Vector(size_type count)
        :m_size(count)
        , m_capacity(count) {
        m_data = new T[count];
    }
    Vector(const Vector& other)
        :m_size(other.m_size)
        , m_capacity(other.m_capacity) {
        m_data = new T[other.m_capacity];
        for (size_type i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
    }
    Vector(Vector&& other) noexcept
        :m_data(other.m_data)
        , m_size(other.m_size)
        , m_capacity(other.m_capacity) {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[]m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = new T[m_capacity];
            for (size_type i = 0; i < m_size; i++) {
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] m_data;
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }
    ~Vector() {
        delete[]m_data;
        m_data = nullptr;
    }

    size_type size() const noexcept {
        return m_size;
    }
    size_type capacity() const noexcept {
        return m_capacity;
    }
    bool empty() const noexcept {
        return m_size == 0;
    }
    void reserve(size_type new_cap) {
        if (new_cap > m_capacity) {
            reallocate(new_cap);
        }
    }
    void shrink_to_fit() {
        if (m_size < m_capacity) {
            reallocate(m_size);
        }
    }

    T& operator[](size_type index) noexcept {
        return m_data[index];
    }
    const T& operator[](size_type index) const noexcept {
        return m_data[index];
    }
    T& at(size_type index) {
        if (index >= m_size) {
            throw std::out_of_range("out of range");
        }
        return m_data[index];
    }
    const T& at(size_type index) const {
        if (index >= m_size)
            throw std::out_of_range("INDEX IS INVALID");
        return m_data[index];
    }

    T& front() {
        return m_data[0];
    }
    const T& front() const {
        return m_data[0];
    }
    T& back() {
        return m_data[m_size - 1];
    }
    const T& back() const {
        return m_data[m_size - 1];
    }

    T* data() noexcept {
        return m_data;
    }
    const T* data() const noexcept {
        return m_data;
    }

    void clear() noexcept {
        destroy_range(0, m_size);
        m_size = 0;
    }
    void push_back(const T& value) {
        grow_if_needed();
        m_data[m_size] = value;
        m_size++;
    }
    void push_back(T&& value) {
        grow_if_needed();
        m_data[m_size] = std::move(value);
        m_size++;
    }

    void pop_back() {
        if (m_size) {
            m_size--;
            m_data[m_size].~T();
        }
    }
    void resize(size_type new_size) {
        if (new_size < m_size) {
            destroy_range(new_size, m_size);
        }
        else if (new_size > m_size) {
            reserve(new_size);
            for (size_type i = m_size; i < new_size; ++i)
                new (m_data + i) T(value);
        }
        m_size = new_size;
    }
    void resize(size_type new_size, const T& value) {
        if (new_size < m_size) {
            destroy_range(new_size, m_size);
        }
        else if (new_size > m_size) {
            reserve(new_size);
            for (size_type i = m_size; i < new_size; ++i)
                new (m_data + i) T(value);
        }
        m_size = new_size;
    }

    void swap(Vector& other) noexcept {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

private:
    T* m_data;
    size_type m_size;
    size_type m_capacity;

    void grow_if_needed() {
        size_type newCap;
        if (m_size == m_capacity) {
            if (m_capacity != 0) {
                newCap=m_capacity * 2;
            }
            else {
                newCap = 1;
            }
        }
        reallocate(newCap);
    }
    void reallocate(size_type new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_type i = 0; i < m_size; ++i) {
            new_data[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }
    void destroy_range(size_type from, size_type to) noexcept {
        for (size_type i = from; i < to; i++) {
            m_data[i].~T();
        }
    }
};

} // namespace softacademy

#endif
