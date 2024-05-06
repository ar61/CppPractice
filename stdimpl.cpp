#include "stdimpl.h"

static int allocated = 0;

void* operator new(size_t size) {
    ++allocated;
    std::cout << "Allocating " << size << " bytes\n";
    return malloc(size);
}

void operator delete(void* data) {
    --allocated;
    std::cout << "De-allocating\n";
    free(data);
}

namespace stdimpl {

template <typename T>
class uniqueptr
{
public:
    uniqueptr(T* val = nullptr) : m_val(val) {
        std::cout << "In Constructor\n";
    }

    ~uniqueptr() {
        if(m_val) {
            delete m_val;
            m_val = nullptr;
        }
        std::cout << "In Destructor\n";
    }

    uniqueptr(const uniqueptr<T>& ptr) = delete;
    uniqueptr& operator=(const uniqueptr<T>& other) = delete;

    uniqueptr(uniqueptr<T>&& other) {
        std::cout << "In Move Constructor\n";
        m_val = other.m_val;
        other.m_val = nullptr;
    }

    uniqueptr& operator=(uniqueptr<T>&& other) {
        std::cout << "In Move assignment\n";
        if(this == &other) {
            std::cout << "Same Object returning\n";
            return *this;
        }
        if(m_val) {
            delete m_val;
        }
        m_val = other.m_val;
        other.m_val = nullptr;
        return *this;
    }

    T* operator->() {
        return m_val;
    }

    T& operator*() {
        return *m_val;
    }

    T* get() {
        return m_val;
    }

    void reset(T* newVal = nullptr) {
        if(m_val) {
            delete m_val;
        }
        m_val = newVal;
    }

private:
    T* m_val;
};

void uniqueptrTests() {
    {
        uniqueptr<int> ptr1(new int(2));
        
        // uniqueptr<int> ptr2(ptr1);
        // uniqueptr<int> ptr3 = ptr1;

        uniqueptr<int> ptr4(new int(500));
        ptr4 = std::move(ptr4);
        //ptr4 = ptr1;
        
        std::cout << *ptr1 << '\n';
        uniqueptr<int> ptr3 = std::move(ptr1);
        std::cout << *ptr3 << '\n';

        ptr4 = std::move(ptr3);

        // ptr1->func();
        std::cout << *ptr4 << '\n';
        if(ptr4.get()) {
            std::cout << *ptr4.get() << '\n';
        }
        
        ptr1.reset(new int(30));
        std::cout << *ptr1 << '\n';

        ptr4.reset(new int(3230));
        std::cout << *ptr4 << '\n';

        uniqueptr<std::string> ptr5(new std::string("Abhinav Rathod. "));
        std::cout << ptr5->c_str() << '\n';

        std::cout << "Total allocated in scope: " << allocated << '\n';
    }

    std::cout << "Total allocated: " << allocated << '\n';
}

template<typename T>
class sharedptr { // isn't thread-safe, also doest support custom deleter/allocator

public:
    sharedptr(T* val = nullptr): m_val(val), m_counter(new int(1)) {
        std::cout << "In Constructor" << '\n';
    }

    sharedptr(const sharedptr& other) {
        std::cout << "Copy constructor\n";
        m_val = other.m_val;
        m_counter = other.m_counter;
        incrementCounter();
    }

    sharedptr& operator=(const sharedptr& other) {
        std::cout << "Copy Assignment\n";
        if(this != &other) {
            decrementCounter();
            m_val = other.m_val;
            m_counter = other.m_counter;
            incrementCounter();
        }
        return *this;
    }

    sharedptr(sharedptr&& other) {
        std::cout << "Move Constructor\n";
        m_val = other.m_val;
        m_counter = other.m_counter;
        
        other.m_val = nullptr;
        other.m_counter = nullptr;
    }

    sharedptr& operator=(sharedptr&& other) {
        std::cout << "Copy Assignment\n";
        if(this != &other) {
            decrementCounter();
            m_val = other.m_val;
            m_counter = other.m_counter;
            other.m_val = nullptr;
            other.m_counter = nullptr;
        }
        return *this;
    }

    void reset(T* val = nullptr) {
        if(m_val) {
            decrementCounter();
        }
        m_val = val;
        m_counter = new int(1);
    }

    int get_count() {
        if(m_counter) {
            return *m_counter;
        }
        return -1; // or throw an error
    }

    T* operator->() {
        return m_val;
    }

    T* get() {
        return m_val;
    }

    T& operator*() {
        return *m_val;
    }

    ~sharedptr() {
        decrementCounter();
    }

private:
    T* m_val;
    int* m_counter;

    void incrementCounter() {
        if(m_counter) {
            ++(*m_counter);
        }
    }
    void decrementCounter() {
        if(m_counter) {
            --(*m_counter);
            if( (*m_counter) == 0) {
                if(m_val) {
                    delete m_val;
                    delete m_counter;
                    m_val = nullptr;
                    m_counter = nullptr;
                }
            }
        }
    }
};

void sharedptrTests() {

    sharedptr<int> ptr1;
    sharedptr<int> ptr2(new int(10));
    sharedptr<int> ptr3(ptr2);
    ptr3 = ptr2;
    sharedptr<int> ptr4(std::move(ptr1));
    ptr2 = std::move(ptr3);

    ptr4.reset();
    ptr1.reset(new int(6));

    std::cout << *ptr1 << '\n';

    sharedptr<std::string> ptr5(new std::string("Abhinav Rathod. "));

    std::cout << ptr5->c_str() << '\n';

    std::cout << *ptr1.get() << '\n';

    std::cout << ptr1.get_count() << '\n';
}

}