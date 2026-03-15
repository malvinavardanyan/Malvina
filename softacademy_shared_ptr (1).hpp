#ifndef SOFTACADEMY_SHARED_PTR_HPP
#define SOFTACADEMY_SHARED_PTR_HPP

#include <cstddef>
#include <utility>

namespace softacademy {

template <typename T> class WeakPtr;

namespace detail {

struct ControlBlock {
    std::size_t strong_count;
    std::size_t weak_count;
    void* ptr;
    void (*deleter)(void*);

    ControlBlock(void* p, void (*d)(void*))
        :strong_count(1)
        ,weak_count(0)
        ,ptr(p)
        ,deleter(d){}
};

template <typename U>
void default_delete(void* p) {
    delete static_cast<U*>(p);
}

} // namespace detail

template <typename T>
class SharedPtr {
public:
    using element_type = T;

    SharedPtr() noexcept
        :m_ptr(nullptr)
        ,m_control(nullptr){}

    explicit SharedPtr(T* ptr)
        :m_ptr(ptr)
        ,m_control(nullptr) {}

    SharedPtr(const SharedPtr& other) noexcept
        :m_ptr(other.m_ptr)
        ,m_control(other.m_control){
        inc_strong();
    }

    SharedPtr(SharedPtr&& other) noexcept
        :m_ptr(other.m_ptr)
        ,m_control(other.m_control) {
        other.m_ptr = nullptr;
        other.m_control = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) noexcept {
        if (this != &other) {
            dec_strong();
            m_ptr = other.m_ptr;
            m_control = other.m_control;
            inc_strong();
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept{
        if (this != &other) {
            dec_strong();
            m_ptr = other.m_ptr;
            m_control = other.m_control;
            other.m_ptr = nullptr;
            other.m_control = nullptr;
        }
        return *this
    }

    ~SharedPtr() {
        reset();
    }

    T* get() const noexcept {
        return m_ptr;
    }
    T& operator*() const {
        return *m_ptr;
    }
    T* operator->() const noexcept {
        return m_ptr;
    }

    std::size_t use_count() const noexcept {
        if (m_control) {
            return m_control->strong_count;
        }
        return 0;
    }
    explicit operator bool() const noexcept {
        return m_ptr != nullptr;
    }

    void reset() noexcept {
        dec_strong();
        m_ptr = nullptr;
        m_control = nullptr;
    }
    void reset(T* ptr) {
        dec_strong();
        if (ptr) {
            m_ptr = ptr;
            m_control = new ControlBlock<T>(ptr);
            m_control->strong_count = 1;
            m_control->weak_count = 0;
        }
        else {
            m_ptr = nullptr;
            m_control = nullptr;
        }
    }

    void swap(SharedPtr& other) noexcept {
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_control, other.m_control);
    }

private:
    T* m_ptr;
    detail::ControlBlock* m_control;

    void inc_strong() noexcept {
        if (m_control) {
            m_control->strong_count++;
        }
    }
    void dec_strong() noexcept {
        if (m_control) {
            m_control->strong_count--;
            if (m_control->strong_count == 0 && m_control->weak_count == 0) {
                delete m_control;
                m_control = nullptr;
            }
        }
    }

    friend class WeakPtr<T>;
};

} // namespace softacademy

#endif
