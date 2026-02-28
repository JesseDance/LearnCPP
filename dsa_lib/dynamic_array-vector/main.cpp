#include <iostream>
#include <utility>      // for std::move, std::swap
#include <new>          // for placement new
#include <stdexcept>    // for std::out_of_range
#include <string>

// --- PART 1: The Vector Implementation (from previous steps) ---
template <typename T>
class Vector {
private:
    T* data;
    size_t m_size;
    size_t m_capacity;

    void reallocate(size_t new_capacity) {
        // 1. Allocate raw memory
        T* new_block = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        // 2. Move elements (efficiently transfer ownership)
        for (size_t i = 0; i < m_size; i++) {
            new (&new_block[i]) T(std::move(data[i]));
        }

        // 3. Destroy old shells and free old memory
        for (size_t i = 0; i < m_size; i++) {
            data[i].~T();
        }
        ::operator delete(data);

        data = new_block;
        m_capacity = new_capacity;
    }

public:
    Vector() : data(nullptr), m_size(0), m_capacity(0) {}

    // Destructor
    ~Vector() {
        for (size_t i = 0; i < m_size; i++) data[i].~T();
        ::operator delete(data);
    }

    // Copy Constructor (Deep Copy)
    Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
        for (size_t i = 0; i < m_size; i++) {
            new (&data[i]) T(other.data[i]);
        }
        std::cout << ">> [Vector] Deep Copy performed.\n";
    }

    // Move Constructor (The "Thief")
    Vector(Vector&& other) noexcept 
        : data(other.data), m_size(other.m_size), m_capacity(other.m_capacity) {
        other.data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        std::cout << ">> [Vector] Move Constructor performed.\n";
    }

    // Push Back
    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            size_t new_cap = (m_capacity == 0) ? 1 : m_capacity * 2;
            reallocate(new_cap);
        }
        new (&data[m_size]) T(value);
        m_size++;
    }

    // Push Back (Move version)
    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            size_t new_cap = (m_capacity == 0) ? 1 : m_capacity * 2;
            reallocate(new_cap);
        }
        new (&data[m_size]) T(std::move(value));
        m_size++;
    }

    // Iterators (required for range-based for loops)
    T* begin() { return data; }
    T* end() { return data + m_size; }
};

// --- PART 2: A Noisy Class to visualize memory ops ---
struct DebugObj {
    int id;
    
    DebugObj(int i) : id(i) { 
        std::cout << "  Constructed Obj " << id << "\n"; 
    }
    
    ~DebugObj() { 
        std::cout << "  Destroyed Obj " << id << "\n"; 
    }
    
    DebugObj(const DebugObj& other) : id(other.id) { 
        std::cout << "  Copied Obj " << id << "\n"; 
    }
    
    DebugObj(DebugObj&& other) noexcept : id(other.id) { 
        std::cout << "  Moved Obj " << id << "\n"; 
        other.id = -1; // Mark "stolen" object
    }
};

// --- PART 3: Driver Code ---
int main() {
    std::cout << "=== TEST 1: Basic Push & Reallocation ===\n";
    {
        Vector<DebugObj> v;
        // Watch the console: You will see "Moved" calls when the vector resizes!
        // This proves reallocate() is moving data, not copying it.
        std::cout << "Adding 1...\n";
        v.push_back(DebugObj(1)); 
        
        std::cout << "Adding 2 (Will trigger resize/move)...\n";
        v.push_back(DebugObj(2)); 
        
        std::cout << "Adding 3 (Will trigger resize/move)...\n";
        v.push_back(DebugObj(3));
    } // End of scope: Destructors run here

    std::cout << "\n=== TEST 2: Copy Semantics ===\n";
    {
        Vector<DebugObj> v1;
        v1.push_back(DebugObj(10));
        
        std::cout << "Creating v2 as a copy of v1...\n";
        Vector<DebugObj> v2 = v1; // Invokes Copy Constructor
    }

    std::cout << "\n=== TEST 3: Move Semantics ===\n";
    {
        Vector<DebugObj> vSource;
        vSource.push_back(DebugObj(99));

        std::cout << "Moving vSource to vDest...\n";
        Vector<DebugObj> vDest = std::move(vSource); // Invokes Move Constructor
        
        // vSource is now empty. vDest owns the data.
        // No "Copied Obj" messages should appear here!
    }
    
    std::cout << "\n=== End of Program ===\n";
    return 0;
}