
#include "basics.h"
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <variant>
#include <any>
#include <future> // conatins std::async
#include <mutex>
#include <functional> // std::ref
#include <type_traits>

namespace basics {

String::String(const char* data) {
    std::cout << "Created!\n";
    m_len = strlen(data);
    m_Data = new char[m_len];
    memcpy(m_Data, data, m_len);
}

String::String(const String& string) {
    std::cout << "Copied!\n";
    m_len = string.m_len;
    m_Data = new char[m_len];
    memcpy(m_Data, string.m_Data, m_len);
}

String::String(String&& other) noexcept {
    std::cout << "Moved!\n";
    m_Data = other.m_Data;
    m_len = other.m_len;

    other.m_len = 0;
    other.m_Data = nullptr;
}

String& String::operator=(String&& other) noexcept {
    std::cout << "Move Assignment!\n";

    if(this != &other) {
        delete[] m_Data;

        m_len = other.m_len;
        m_Data = other.m_Data;

        other.m_len = 0;
        other.m_Data = nullptr;
    }
    return *this;
}

// String& operator+(String&& other) noexcept {
//     cout << "Add!\n";

//     uint32_t totalLen = m_len + other.m_len;
//     char* newData = new char[totalLen];
//     uint32_t cur = 0;
//     for(uint32_t thisIdx = 0; thisIdx < m_len; ++cur, ++thisIdx) {
//         newData[cur] = m_Data[thisIdx];
//     }
//     for(int otherIdx = 0; otherIdx < other.m_len; ++otherIdx, ++cur) {
//         newData[cur] = other.m_Data[otherIdx];
//     }

//     delete[] other.m_Data;

//     m_len = totalLen;
//     m_Data = newData;

//     other.m_Data = nullptr;
//     other.m_len = 0;

//     return *this;
// }

// String& operator+(const String& other) noexcept {
//     cout << "Add!\n";

//     uint32_t totalLen = m_len + other.m_len;
//     char* newData = new char[totalLen];
//     uint32_t cur = 0;
//     for(uint32_t thisIdx = 0; thisIdx < m_len; ++cur, ++thisIdx) {
//         newData[cur] = m_Data[thisIdx];
//     }
//     for(int otherIdx = 0; otherIdx < other.m_len; ++otherIdx, ++cur) {
//         newData[cur] = other.m_Data[otherIdx];
//     }

//     m_len = totalLen;
//     m_Data = newData;

//     return *this;
// }

String::~String() {
    std::cout << "Destroyed!\n";
    delete[] m_Data;
}

void String::print() {
    for(int i = 0; i < m_len; ++i) {
        std::cout << m_Data[i];
    }
    std::cout << '\n';
}

Entity::Entity(const String& name) :
            m_Name(name) {}

Entity::Entity(String&& name) :
            m_Name(std::move(name)) {}

void Entity::printName() {
    m_Name.print();
}

String operator+(String&& other, String&& another) noexcept {
    std::cout << "Friend Add!\n";

    uint32_t totalLen = other.m_len + another.m_len;
    char* newData = new char[totalLen];
    uint32_t cur = 0;
    for(uint32_t thisIdx = 0; thisIdx < other.m_len; ++cur, ++thisIdx) {
        newData[cur] = other.m_Data[thisIdx];
    }
    for(int otherIdx = 0; otherIdx < another.m_len; ++otherIdx, ++cur) {
        newData[cur] = another.m_Data[otherIdx];
    }

    delete[] other.m_Data;
    delete[] another.m_Data;

    other.m_len = totalLen;
    other.m_Data = newData;

    another.m_Data = nullptr;
    another.m_len = 0;

    return String(newData);
}

void printVector2(const Vector2& vec)
{
    std::cout << vec.a << "," << vec.b << '\n';
}

void unionizeVectors()
{
    Vector4 vector{1.0f, 2.0f, 3.0f, 4.0f};
    printVector2(vector.a);
    printVector2(vector.b);
    std::cout << "----------------\n";
    vector.z = 400.0f;
    printVector2(vector.a);
    printVector2(vector.b);
}

std::optional<std::string> readFile(const std::string& filename)
{
    std::ifstream file = std::ifstream(filename);
    if(file)
    {
        std::string data;
        file.close();
        return data;
    }
    return {};
}

void optionals() {
    std::optional<std::string> data = readFile("data.txt");
    if(data.has_value()) {
        std::cout << "File Opened Successfully";
    } else {
        std::cout << "File Open Failed";
    }
}


std::variant<std::string, ErrorCode> ReadFileAsString() {
    return {};
}

void variants() {
    std::variant<std::string, int> data;

    std::cout << sizeof(int) << '\n';
    std::cout << sizeof(std::string) << '\n';
    std::cout << sizeof(data) << '\n';
    data = "Abhinav";

    // if(data.index() == 0)
    if(auto* value = std::get_if<std::string>(&data)) {
        std::cout << *value << '\n';
    }
    data = 2;
    std::cout << std::get<int>(data) << '\n';
    if(auto* value = std::get_if<std::string>(&data)) {
        std::cout << *value << '\n';
    } else {
        std::cout << std::get<int>(data) << '\n';
    }
}

// overloading this can help you debug how the allocation is being done
// void* operator new(size_t size) {
//     return malloc(size); <- set breakpoint here
// }

struct CustomClass
{
    std::string s0, s1;
};

void anyUsage() {
    
    std::any data;// = std::make_any

    data = CustomClass();
    data = std::string("Abhi");
    std::cout << std::any_cast<std::string>(data); //- high cost
    std::string& s = std::any_cast<std::string&>(data); // take ref -low cost
    //std::cout << sizeof(data) << '\n';
    data = 2;
    data = "Abhinav";

    // variant is a type safe union
    // any allocates memory based on what you set it to, small vs big storage, look at source code of <any>
}


class Mesh
{
public:
    Mesh(const std::string& fileName) {
        load(fileName);
    }

private:
    static void load(const std::string& fileName) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
};

static std::vector<std::reference_wrapper<Mesh>> meshes;
static std::mutex meshMutex;

static void LoadMeshesConcurrently(std::vector<std::reference_wrapper<Mesh>>* meshes, std::string fileName)
{
    Mesh m(fileName);

    std::lock_guard<std::mutex> lock(meshMutex);
    meshes->push_back(m);
}

std::vector<std::future<void>> futures;


static void loadMeshes()
{
    // load model name from text file
    // push it into vector of strings 
    // then load the meshes in MeshVector
    std::ifstream stream("meshFiles.txt");
    std::string line;
    static std::vector<std::string> fileNames;
    while(std::getline(stream, line)) {
        fileNames.emplace_back(line);
    }

#define NONASYNC 0
#if NONASYNC
    for(const auto& fileName : fileNames) {
        Mesh m(fileName);
        meshes.push_back(std::ref<Mesh>(m));
    }
#else
    for(const auto& fileName : fileNames) {
        futures.push_back(std::async(std::launch::async, LoadMeshesConcurrently, &meshes, (std::string)fileName));
    }
#endif
}

void runAsync() {
    // multi-threading
    // worker thread
    Timer t;
    loadMeshes();
}

}
