
#include "designpatterns.h"

namespace designpatterns {

Singleton *Singleton::m_Instance = nullptr;

void callSingleton() {
    Singleton::getInstance().hey();
}

}
