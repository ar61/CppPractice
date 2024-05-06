
#include <iostream>

namespace designpatterns {

// Used vastly:

// Singleton
// Factory
// Abstract Factory
// Observer

// Good to know:
// Builder
// Decorator
// Adaptor
// Strategy
// Facade

class Singleton
{
public:
    static Singleton& getInstance() {
        if(m_Instance == nullptr) {
            m_Instance = new Singleton;
        }
        return *m_Instance;
    }
    void hey() {
        std::cout << "Hello\n";
    }
private:
    Singleton() = default;
    static Singleton* m_Instance;
};

void callSingleton();

class Factory
{
};



}
