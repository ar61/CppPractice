#include <stdint.h>
#include <chrono>
#include <iostream>

// This is to document some basics in c++ wiht the help of TheCherno Youtube C++ tutorials
// Some of the code here is courtesy of The Cherno C++ Videos from Youtube

namespace basics {

class String
{
public:
    String() = default;
    String(const char* data);
    String(const String& string);
    String(String&& other) noexcept;
    String& operator=(String&& other) noexcept;
    ~String();
    void print();
    friend String operator+(String&& other, String&& another) noexcept;

private:
    char* m_Data;
    uint32_t m_len;
};

class Entity {
public:
    Entity(const String& name);
    Entity(String&& name);
    void printName();

private:
    String m_Name;
};

class Timer 
{
public:    
    Timer() {
        m_startTime = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto endTime = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTime).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

        auto diff = end - start;
        double diffus = diff * 0.001;

        std::cout << diffus << "us (" << diff << "ms )\n";
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
};

class Vector
{
public:
    Vector() = default;
    Vector(int a, int b, int c) : x(a),y(b),z(c) {
        //std::cout << "Created " << x << y << z << '\n';
    }
    Vector(const Vector& other) :
        x(other.x), y(other.y), z(other.z) {
        std::cout << "Copied " << x << y << z << '\n';
    }
private:
    int x,y,z;
};


struct Vector2
{
    float a,b;
};

struct Vector4
{
    union 
    {
        struct
        {
            float x,y,z,w;
        };
        struct
        {
            Vector2 a,b;
        };
    };
};

void printVector2(const Vector2&);

void unionizeVectors();

void optionals();

enum class ErrorCode
{
    None = 0,
    FileNotFound = 1,
    NoAccess = 2
};

void variants();

void anyUsage();

void runAsync();

}
